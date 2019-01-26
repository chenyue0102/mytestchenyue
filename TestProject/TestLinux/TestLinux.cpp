#include "TestLinux.h"
#include <cstdio>
#include <stdlib.h>
#include <assert.h>
#include <type_traits>
#include <string.h>
#include <string>
#include <chrono>
#include <errno.h>
#include <fcntl.h>//open
#include <sys/stat.h>  // mode访问权限所需头文件
#include <unistd.h>//read,close
#include <sys/mman.h>//mmap
#include <sys/ioctl.h>
#include <linux/cdrom.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>//ftok
#include <sys/sem.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/shm.h>
#include <signal.h>

#define TEST_FILE_NAME "/home/test/1.txt"
#define MSG_QUIT 100
#define MSG_PRINT 101

struct mymsgbuf
{
	long mtype;
	char buf[256];
};

template < typename T, size_t N >
size_t _countof(T(&arr)[N])
{
	return std::extent< T[N] >::value;
}

extern int errno;

void testWriteFile()
{
	int fd = -1;

	do
	{
		if (-1 == (fd = open(TEST_FILE_NAME, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		const char *pText = "hello,world";
		if (-1 == write(fd, pText, strlen(pText)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		if (-1 == lseek(fd, 5, SEEK_END))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		const char *pText2 = "hello,linux";
		if (-1 == write(fd, pText2, strlen(pText2)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		off_t fileLen = lseek(fd, 0, SEEK_CUR);
		if (-1 == fileLen)
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		printf("write file size=%lld\n", fileLen);
	} while (false);

	if (-1 != fd)
	{
		close(fd);
		fd = -1;
	}
}

void testReadFile()
{
	int fd = -1;
	do
	{
		if (-1 == (fd = open(TEST_FILE_NAME, O_RDONLY)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		off_t fileLen = lseek(fd, 0, SEEK_END);
		printf("file size=%lld\n", fileLen);
		if (0 == fileLen)
		{
			break;
		}
		if (-1 == lseek(fd, 0, SEEK_SET))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		std::string buf;
		buf.resize(fileLen);
		if (-1 == read(fd, &*buf.begin(), buf.size()))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		printf("%s\n", buf.c_str());
	} while (false);
	if (-1 != fd)
	{
		close(fd);
		fd = -1;
	}
}

void testFileStat()
{
	do
	{
		struct stat st = { 0 };
		if (-1 == stat(TEST_FILE_NAME, &st))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		printf("包含此文件的设备ID：%d\n", (int)st.st_dev);		/*文件的ID号*/
		printf("此文件的节点：%d\n", (int)st.st_ino);				/*文件的节点*/
		printf("此文件的保护模式：%d\n", (int)st.st_mode);		/*文件的模式*/
		printf("此文件的硬链接数：%d\n", (int)st.st_nlink);		/*文件的硬链接数*/
		printf("此文件的所有者ID：%d\n", (int)st.st_uid);			/*文件的所有者ID*/
		printf("此文件的所有者的组ID：%d\n", (int)st.st_gid);		/*文件的组ID*/
		printf("设备ID（如果此文件为特殊设备）：%d\n", (int)st.st_rdev); /*文件的设备ID*/
		printf("此文件的大小：%d\n", (int)st.st_size);				/*文件的大小*/
		printf("此文件的所在文件系统块大小：%d\n", (int)st.st_blksize);	/*文件的系统块大小*/
		printf("此文件的占用块数量：%d\n", (int)st.st_blocks);			/*文件的块大小*/
		printf("此文件的最后访问时间：%d\n", (int)st.st_atime);	/*文件的最后访问时间*/
		printf("此文件的最后修改时间：%d\n", (int)st.st_mtime);	/*文件的最后修改时间*/
		printf("此文件的最后状态改变时间：%d\n", (int)st.st_ctime);/*文件的最后状态改变时间*/
	} while (false);
}

void* createAnonymousMapFile(size_t size)
{
	void *pAddress = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (MAP_FAILED != pAddress)
	{
		return pAddress;
	}
	else
	{
		printf("createAnonymousMapFile mmap failed\n");
		return nullptr;
	}
}

int freeAnonymousMapFile(void *pAddress, size_t size)
{
	int ret = munmap(pAddress, size);
	if (-1 == ret)
	{
		printf("freeAnonymousMapFile errno=%d\n", errno);
	}
	return ret;
}

void testMapFile()
{
	int fd = -1;
	do
	{
		if (-1 == (fd = open(TEST_FILE_NAME, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		int nFileLen = 40;
		if (-1 == lseek(fd, nFileLen - 1, SEEK_SET))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		if (-1 == write(fd, "\0", 1))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		void *pstr = mmap(nullptr, nFileLen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (MAP_FAILED == pstr)
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		const char *pText = "hello,map";
		memcpy(pstr, pText, strlen(pText));
		munmap(pstr, nFileLen);
	} while (false);
	if (-1 != fd)
	{
		close(fd);
		fd = -1;
	}
	testReadFile();
}

void testFileFun()
{
	int fd = -1;

	do
	{
		if (-1 == (fd = open(TEST_FILE_NAME, O_RDWR)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		int flags = fcntl(fd, F_GETFL, 0);
		flags |= O_APPEND;
		if (-1 == (flags = fcntl(fd, F_SETFL, &flags)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		int uid = fcntl(fd, F_GETOWN);
		printf("own %d\n", uid);
		if (-1 == fcntl(fd, F_SETOWN, getpid()))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
	} while (false);
	if (-1 != fd)
	{
		close(fd);
		fd = -1;
	}
}

void testioctl()
{
	int fd = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);
	if (-1 == fd)
	{
		printf("errno=%d\n", errno);
		return;
	}
	if (-1 == ioctl(fd, CDROMEJECT, nullptr))
	{
		printf("errno=%d\n", errno);
		assert(false);
	}
	close(fd);
	fd = -1;
}

void test_part1()
{
	testWriteFile();
	testReadFile();
	testFileStat();
	testMapFile();
	testFileFun();
	testioctl();
}

void test_fork()
{
	pid_t pid = fork();
	if (-1 == pid)
	{
		printf("errno=%d\n", errno);
		assert(false);
	}
	else if (0 == pid)
	{
		printf("child process mypid=%d parentpid=%d\n", getpid(), getppid());
	}
	else
	{
		printf("fork child pid=%d mypid=%d parentpid=%d\n", pid, getpid(), getppid());
	}
}

void test_system()
{
	int ret = system("ping 127.0.0.1 -c 2");
	printf("system result %d\n", ret);
}

void test_exec()
{
	char *args[] = { "/bin/ls", nullptr };
	int ret = -1;
	if ((ret = execve("/bin/ls", args, nullptr)) < 0)
	{
		printf("execuve failed result=%d\n", ret);
	}
	printf("error");
}

void test_unmaed_pipe()
{
	pid_t pid = 0;
	int fd[2] = { 0 };
	int result = pipe(fd);
	int *read_pipe = &fd[0];
	int *write_pipe = &fd[1];
	if (-1 == result)
	{
		printf("test_unmaed_pipe pipe failed error=%d\n", errno);
		return;
	}
	pid = fork();
	if (-1 == pid)
	{
		printf("test_unmaed_pipe fork failed error=%d\n", errno);
	}
	else if (0 == pid)
	{
		if (-1 == close(*read_pipe))
		{
			printf("test_unmaed_pipe close read failed error=%d\n", errno);
		}
		const char *pstrText = "hello,world";
		ssize_t nBytes = write(*write_pipe, pstrText, strlen(pstrText));
		if (-1 == close(*write_pipe))
		{
			printf("test_unmaed_pipe close write failed error=%d\n", errno);
		}
	}
	else
	{
		if (-1 == close(*write_pipe))
		{
			printf("test_unmaed_pipe close write failed error=%d\n", errno);
		}
		char szBuf[256] = { 0 };
		ssize_t nBytes = read(*read_pipe, szBuf, sizeof(szBuf));
		printf("recv len=%lld, %s\n", nBytes, szBuf);
		nBytes = read(*read_pipe, szBuf, sizeof(szBuf));
		printf("recv len=%lld, %s\n", nBytes, szBuf);
		if (-1 == close(*read_pipe))
		{
			printf("test_unmaed_pipe close read failed error=%d\n", errno);
		}
	}
}

void test_named_pipe()
{
	const char *pfifo_name = "/tmp/my_fifo";
	int res = 0;
	int write_fd = -1;
	int read_fd = -1;
	int pid = 0;
	ssize_t readlen = -1;

	do
	{
		if (-1 == access(pfifo_name, F_OK))
		{
			if (-1 == (res = mkfifo(pfifo_name, 0666)))
			{
				printf("test_named_pipe mkfifo errno=%d\n", errno);
				break;
			}
		}
		pid = fork();
		if (-1 == pid)
		{
			printf("test_named_pipe fork errno=%d\n", errno);
			break;
		}
		else if (0 == pid)
		{
			if (-1 == (write_fd = open(pfifo_name, O_WRONLY)))
			{
				printf("test_named_pipe open errno=%d\n", errno);
				break;
			}
			const char *pstrText = "hello,world";
			if (-1 == write(write_fd, pstrText, strlen(pstrText)))
			{
				printf("test_named_pipe write_fd open errno=%d\n", errno);
				break;
			}
		}
		else
		{
			if (-1 == (read_fd = open(pfifo_name, O_RDONLY)))
			{
				printf("test_named_pipe read_fd open errno=%d\n", errno);
				break;
			}
			char buf[256] = { 0 };
			if (-1 == (readlen = read(read_fd, buf, sizeof(buf))))
			{
				printf("test_named_pipe open errno=%d\n", errno);
				break;
			}
			printf("test_named_pipe %lld read=%s\n", readlen, buf);
		}
	} while (false);
	if (-1 != write_fd)
	{
		if (-1 == close(write_fd))
		{
			printf("test_named_pipe write_fd close errno=%d\n", errno);
		}
		write_fd = -1;
	}
	if (-1 != read_fd)
	{
		if (-1 == close(read_fd))
		{
			printf("test_named_pipe read_fd close errno=%d\n", errno);
		}
		read_fd = -1;
	}
}

void*  send_msg_thread(void *arg)
{
	int msg_id = *(int*)arg;
	mymsgbuf buf;

	do
	{
		memset(&buf, 0, sizeof(buf));
		buf.mtype = MSG_PRINT;
		strcpy(buf.buf, "hello,world");
		if (-1 == msgsnd(msg_id, &buf, strlen(buf.buf) + 1, IPC_NOWAIT))
		{
			printf("send_msg_thread msgsnd errno=%d\n", errno);
			break;
		}
		memset(&buf, 0, sizeof(buf));
		buf.mtype = MSG_QUIT;
		if (-1 == msgsnd(msg_id, &buf, 0, 0))
		{
			printf("send_msg_thread msgsnd errno=%d\n", errno);
			break;
		}
	} while (false);
	return nullptr;
}

void read_message(int msg_id)
{
	int ret = -1;
	bool bContinue = true;
	mymsgbuf buf;
	while (bContinue)
	{
		memset(&buf, 0, sizeof(buf));
		if (-1 == (ret = msgrcv(msg_id, &buf, sizeof(buf) - sizeof(long), 0, MSG_NOERROR)))
		{
			printf("read_message msgrcv errno=%d\n", errno);
			break;
		}
		switch (buf.mtype)
		{
		case MSG_QUIT:
			printf("read_message quit\n");
			bContinue = false;
			break;
		case MSG_PRINT:
			printf("read_message print=%s\n", buf.buf);
			break;
		default:
			printf("read_message unknown \n");
			bContinue = false;
			break;
		}
	}
}

void test_msg()
{
	const char *pstrMsgPath = "/tmp/msg";
	key_t key = ftok(pstrMsgPath, 'a');
	int msg_id = -1;
	pthread_t pt;
	msqid_ds msg_info;
	int mode = 0666;

	do
	{
		if (-1 == key)
		{
			printf("test_msg ftok errno=%d\n", errno);
			break;
		}
		if (-1 == (msg_id = msgget(key, IPC_CREAT | IPC_EXCL | mode)))
		{
			if (-1 == (msg_id = msgget(key, IPC_CREAT)))
			{
				printf("test_msg msgget errno=%d\n", errno);
				break;
			}
		}
		if (-1 == msgctl(msg_id, IPC_STAT, &msg_info))
		{
			printf("test_msg msgctl IPC_STAT errno=%d\n", errno);
			break;
		}
		memset(&msg_info, 0, sizeof(msg_info));
		msg_info.msg_qbytes = 123456;
		if (-1 == msgctl(msg_id, IPC_SET, &msg_info))
		{
			printf("test_msg msgctl IPC_SET errno=%d\n", errno);
			//break;
		}
		if (0 != pthread_create(&pt, nullptr, &send_msg_thread, &msg_id))
		{
			printf("test_msg pthread_create errno=%d\n", errno);
			break;
		}
		read_message(msg_id);
		if (0 != pthread_join(pt, nullptr))
		{
			printf("test_msg pthread_join errno=%d\n", errno);
			break;
		}
	} while (false);

	if (-1 != msg_id)
	{
		if (-1 == msgctl(msg_id, IPC_RMID, nullptr))
		{
			printf("send_msg_thread msgctl IPC_RMID errno=%d\n", errno);
		}
		msg_id = -1;
	}
}

#define MAX_RESOUCR_COUNT 4
#define PRODUCER_COUNT 3
#define CONSUMER_COUNT 2

char g_szBuf[MAX_RESOUCR_COUNT][64] = { 0 };
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int  g_producer = 0;
volatile int  g_consumer = 0;
sem_t sem_empty = { 0 };
sem_t sem_full = { 0 };
const int g_loopcount = 100;


void add_count(volatile int *pcount)
{
	if (++(*pcount) >= MAX_RESOUCR_COUNT)
	{
		*pcount = 0;
	}
}

void*  producer_proc(void *arg)
{
	int index = 0;
	do
	{
		if (-1 == sem_wait(&sem_empty))
		{
			printf("producer_proc sem_wait errno=%d\n", errno);
			break;
		}
		std::string strNum = std::to_string(random());
		sleep(PRODUCER_COUNT);
		if (0 != pthread_mutex_lock(&mutex))
		{
			printf("producer_proc pthread_mutex_lock errno=%d\n", errno);
			break;
		}
		strcpy(g_szBuf[g_producer], strNum.c_str());
		printf("producer_proc text=%s\n", g_szBuf[g_producer]);
		add_count(&g_producer);
		if (0 != pthread_mutex_unlock(&mutex))
		{
			printf("producer_proc pthread_mutex_unlock errno=%d\n", errno);
			break;
		}
		if (-1 == sem_post(&sem_full))
		{
			printf("producer_proc sem_post errno=%d\n", errno);
			break;
		}
	} while (++index < g_loopcount);
	return nullptr;
}

void*  consumer_proc(void *arg)
{
	int index = 0;
	do
	{
		if (-1 == sem_wait(&sem_full))
		{
			printf("consumer_proc sem_wait errno=%d\n", errno);
			break;
		}
		if (0 != pthread_mutex_lock(&mutex))
		{
			printf("consumer_proc pthread_mutex_lock errno=%d\n", errno);
			break;
		}
		printf("consumer_proc text=%s\n", g_szBuf[g_consumer]);
		add_count(&g_consumer);
		if (0 != pthread_mutex_unlock(&mutex))
		{
			printf("consumer_proc pthread_mutex_unlock errno=%d\n", errno);
			break;
		}
		sleep(CONSUMER_COUNT);
		if (-1 == sem_post(&sem_empty))
		{
			printf("consumer_proc sem_post errno=%d\n", errno);
			break;
		}
	} while (++index < g_loopcount);
	return nullptr;
}

void test_sem()
{
	srand(time(nullptr));

	do
	{
		if (-1 == sem_init(&sem_empty, 0, PRODUCER_COUNT))
		{
			printf("test_sem sem_init errno=%d\n", errno);
			break;
		}
		if (-1 == sem_init(&sem_full, 0, 0))
		{
			printf("test_sem sem_init errno=%d\n", errno);
			break;
		}
		if (0 != pthread_mutex_init(&mutex, nullptr))
		{
			printf("test_sem pthread_mutexattr_init errno=%d\n", errno);
			break;
		}
		pthread_t ptProducer[PRODUCER_COUNT];
		pthread_t ptConsumer[CONSUMER_COUNT];

		for (auto &oneThread : ptProducer)
		{
			if (0 != pthread_create(&oneThread, nullptr, &producer_proc, nullptr))
			{
				printf("test_sem pthread_create errno=%d\n", errno);
				break;
			}
		}

		for (auto &&oneThread : ptConsumer)
		{
			if (0 != pthread_create(&oneThread, nullptr, &consumer_proc, nullptr))
			{
				printf("test_sem pthread_create errno=%d\n", errno);
				break;
			}
		}

		for (auto &oneThread : ptProducer)
		{
			if (0 != pthread_join(oneThread, nullptr))
			{
				printf("test_sem pthread_join errno=%d\n", errno);
				break;
			}
		}

		for (auto &&oneThread : ptConsumer)
		{
			if (0 != pthread_join(oneThread, nullptr))
			{
				printf("test_sem pthread_join errno=%d\n", errno);
				break;
			}
		}
	} while (false);

	if (0 != pthread_mutex_destroy(&mutex))
	{
		printf("test_sem pthread_mutexattr_destroy errno=%d\n", errno);
	}
	if (-1 == sem_destroy(&sem_empty))
	{
		printf("test_sem sem_destroy errno=%d\n", errno);
	}
	if (-1 == sem_destroy(&sem_full))
	{
		printf("test_sem sem_destroy errno=%d\n", errno);
	}
}

void test_shm()
{
	const char *pstrMsgPath = "/ipc/shm";
	key_t key = ftok(pstrMsgPath, 'a');
	int mode = 0666;
	int shmid = -1;
	sem_t *semid = nullptr;
	char *pshm = nullptr;
	pid_t pid = -1;

	do
	{
		if (nullptr == (semid = (sem_t*)createAnonymousMapFile(sizeof(sem_t))))
		{
			printf("test_shm createAnonymousMapFile errno=%d\n", errno);
			break;
		}
		memset(semid, 0, sizeof(sem_t));
		if (-1 == key)
		{
			printf("test_shm ftok errno=%d\n", errno);
			break;
		}
		if (-1 == (shmid = shmget(key, 1024, IPC_CREAT | mode)))
		{
			printf("test_shm shmget errno=%d\n", errno);
			break;
		}
		if (nullptr == (pshm = (char*)shmat(shmid, nullptr, 0)))
		{
			printf("test_shm shmat errno=%d\n", errno);
			break;
		}
		if (-1 == sem_init(semid, 1, 0))
		{
			printf("test_shm sem_init errno=%d\n", errno);
			break;
		}
		pid = fork();
		if (-1 == pid)
		{
			printf("test_shm fork errno=%d\n", errno);
			break;
		}
		else if (0 == pid)
		{
			//sleep(1);
			strcpy(pshm, "hello,world,shm");
			if (-1 == shmctl(shmid, IPC_RMID, nullptr))
			{
				printf("test_shm shmctl errno=%d\n", errno);
				break;
			}
			if (-1 == sem_post(semid))
			{
				printf("test_shm sem_post errno=%d\n", errno);
				break;
			}
		}
		else
		{
			if (-1 == sem_wait(semid))
			{
				printf("test_shm sem_wait errno=%d\n", errno);
				break;
			}
			//sleep(1);
			printf("test_shm shm=%s\n", pshm);
			if (-1 == shmctl(shmid, IPC_RMID, nullptr))
			{
				printf("test_shm shmctl errno=%d\n", errno);
				break;
			}
		}
	} while (false);
	if (-1 == sem_destroy(semid))
	{
		printf("test_shm sem_destroy errno=%d\n", errno);
	}
	if (nullptr != semid)
	{
		freeAnonymousMapFile(semid, sizeof(sem_t));
		semid = nullptr;
	}
	if (nullptr != pshm)
	{
		if (-1 == shmdt(pshm))
		{
			printf("test_shm shmdt errno=%d\n", errno);
		}
		pshm = nullptr;
	}
}

sighandler_t g_sigintold = nullptr;
sighandler_t g_sigstop = nullptr;
void sig_handle(int signo)
{
	if (SIGINT == signo)
	{
		printf("sig_int recv SIGINT pid=%d\n", getpid());
		if (nullptr != g_sigintold)
		{
			g_sigintold(signo);
		}
	}
	else if (SIGABRT == signo)
	{
		printf("sig_int recv SIGABRT pid=%d\n", getpid());
		if (nullptr != g_sigstop)
		{
			g_sigstop(signo);
		}
	}
	else
	{
		printf("sig_int error signo=%d\n", signo);
	}
}

void test_signal()
{
	g_sigintold = signal(SIGINT, &sig_handle);
	g_sigstop = signal(SIGABRT, &sig_handle);
	pid_t pid = fork();
	if (-1 == pid)
	{
		printf("errno=%d\n", errno);
		assert(false);
	}
	else if (0 == pid)
	{
		sleep(60);
	}
	else
	{
		printf("parent pid=%d child pid=%d\n", getpid(), pid);
		sleep(1);
		if (-1 == kill(pid, SIGABRT))
		{
			printf("test_signal kill errno=%d\n", errno);
		}
		if (-1 == raise(SIGINT))
		{
			printf("test_signal raise errno=%d\n", errno);
		}
	}
}

void* thread_proc(void *arg)
{
	int *p = (int*)arg;
	int *result = new int(0);
	if (nullptr != p)
	{
		*result = *p + 1;
	}
	pthread_exit(result);
}

void test_thread()
{
	pthread_t pt = 0;
	int arg = 9;
	if (0 != pthread_create(&pt, nullptr, &thread_proc, &arg))
	{
		printf("test_thread pthread_create errno=%d\n", errno);
	}
	int *presult = nullptr;
	if (0 != pthread_join(pt, (void**)&presult))
	{
		printf("test_thread pthread_join errno=%d\n", errno);
	}
	if (nullptr != presult)
	{
		printf("test_thread result=%d\n", *presult);
		delete presult;
	}
	else
	{
		printf("test_thread nullptr != presult\n");
	}
}

void test_part2()
{
	test_fork();
	test_system();
	test_exec();
	test_unmaed_pipe();
	test_named_pipe();
	test_msg();
	test_sem();
	test_shm();
	test_signal();
	test_thread();
}
