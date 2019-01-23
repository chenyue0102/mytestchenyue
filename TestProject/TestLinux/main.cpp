#include <cstdio>
#include <assert.h>
#include <type_traits>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <errno.h>
#include <fcntl.h>//open
#include <sys/stat.h>  // mode访问权限所需头文件
#include <unistd.h>//read,close
#include <sys/mman.h>//mmap
#include <sys/ioctl.h>
#include <linux/cdrom.h>

#define TEST_FILE_NAME "/home/test/1.txt"
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
		if ((void*)-1 == pstr)
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

void testPart1()
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
}
int main()
{
    printf("hello from TestLinux!\n");
	//test_fork();
	//test_system();
	//test_exec();
	//test_unmaed_pipe();
	test_named_pipe();
    return 0;
}