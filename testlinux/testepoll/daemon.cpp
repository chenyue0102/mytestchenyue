#include "daemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>//error
#include <sys/resource.h>  
#include <sys/types.h> 
#include <sys/stat.h> 
#include <signal.h>
#include <syslog.h>
#include <unistd.h> 
#include <fcntl.h>

extern int errno;

namespace testepoll
{
	void init_daemon(const char *name)
	{
		unsigned int i;
		int fd0, fd1, fd2;
		pid_t pid;
		rlimit rl;
		struct sigaction sa;
		/*
		* Clear file creation mask.
		*/
		umask(0);

		/*
		* Get maximum number of file descriptors.
		*/
		if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		{
			printf("init_daemon getrlimit errno=%d\n", errno);
		}
		/*
		* Become a session leader to lose controlling TTY.
		*/
		if ((pid = fork()) < 0)
		{
			printf("init_daemon fork errno=%d\n", errno);
		}
		else if (0 != pid)
		{
			exit(0);/*exit parent*/
		}
		setsid();
		/*
		* Ensure future opens won't allocate controlling TTYs.
		*/
		signal(SIGPIPE, SIG_IGN);
		signal(SIGHUP, SIG_IGN);

		/*sa.sa_handler = SIG_IGN;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGHUP, &sa, nullptr) < 0)
		{
			printf("init_daemon sigaction errno=%d\n", errno);
		}*/

		if ((pid = fork()) < 0)
		{
			printf("init_daemon fork errno=%d\n", errno);
		}
		else if (0 != pid)
		{
			exit(0);
		}

		/*
		* Change the current working directory to the root so
		* we won't prevent file systems from being unmounted.
		*/
		if (chdir("/") < 0)
		{
			printf("init_daemon chdir errno=%d\n", errno);
		}

		/*
		* Close all open file descriptors.
		*/
		if (rl.rlim_max == RLIM_INFINITY)
		{
			rl.rlim_max = 1024;
		}
		for (i = 0; i < rl.rlim_max; i++)
		{
			close(i);
		}
		/*
		* Attach file descriptors 0, 1, and 2 to /dev/null.
		*/
		fd0 = open("/dev/null", O_RDWR);
		fd1 = dup(0);
		fd2 = dup(0);

		/*
		* Initialize the log file.
		*/
		openlog(name, LOG_CONS | LOG_PID, LOG_DAEMON);
		if (0 != fd0
			|| 1 != fd1
			|| 2 != fd2)
		{
			syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
			exit(1);
		}
		syslog(LOG_DEBUG, "daemon ok");
	}
};
