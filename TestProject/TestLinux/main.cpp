#include <cstdio>
#include <assert.h>
#include <type_traits>
#include <string.h>
#include <string>
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

int main()
{
    printf("hello from TestLinux!\n");
	testWriteFile();
	testReadFile();
	testFileStat();
	testMapFile();
	testFileFun();
	testioctl();
	testioctl();
    return 0;
}