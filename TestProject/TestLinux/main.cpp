#include <cstdio>
#include <assert.h>
#include <type_traits>
#include <errno.h>
#include <fcntl.h>//open
#include <unistd.h>//read

template < typename T, size_t N >
size_t _countof(T(&arr)[N])
{
	return std::extent< T[N] >::value;
}

extern int errno;
void testFile()
{
	int fd = -1;
	do
	{
		if (-1 == (fd = open("/home/test/1.txt", O_RDONLY)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		char szText[512] = { 0 };
		if (-1 == read(fd, szText, _countof(szText)))
		{
			printf("errno=%d\n", errno);
			assert(false);
			break;
		}
		printf("%s\n", szText);
	} while (false);
	if (-1 != fd)
	{
		close(fd);
		fd = -1;
	}
}
int main()
{
    printf("hello from TestLinux!\n");
	testFile();
    return 0;
}