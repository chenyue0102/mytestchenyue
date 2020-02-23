#include <cstdio>
#include <assert.h>
#include <codecvt>
#include <locale>
#include <iconv.h>
#include <memory.h>
#include <thread>
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <signal.h>

template<class Facet>
struct deletable_facet : Facet
{
	using Facet::Facet; // inherit constructors
	~deletable_facet() {}
};
int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
		return -1;
	iconv_close(cd);
	return 0;
}
int fd[2] = { 0 };
void test_epoll() 
{
	int result = pipe(fd);
	int* read_pipe = &fd[0];
	int* write_pipe = &fd[1];
	assert(*write_pipe == fd[1]);
	int id = epoll_create(1024);
	const int MaxEvents = 32;
	epoll_event events[MaxEvents];

	epoll_event ev = { 0 };
	ev.data.fd = *read_pipe;
	ev.events = EPOLLIN | EPOLLET;
	int ret = epoll_ctl(id, EPOLL_CTL_ADD, *read_pipe, &ev);
	printf("epoll_ctl%d", ret);
	loop:
	ret = epoll_wait(id, events, MaxEvents, -1);
	printf("epoll_wait end %d\r\n", ret);
	goto loop;
	close(id);
}

int main()
{
	//int result = pipe(fd);
	std::thread t = std::thread(&test_epoll);
	int a = 0;
	//scanf("%d", &a);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	ssize_t ret = write(fd[1], "1", 1);
	t.join();
	unsigned char gb2312[] = { 0xc4, 0xe3, 0xba, 0xc3, 0x00 };
	char *pp = (char*)gb2312;
	//char gb2312[] = "ABC";
	//char utf8[16] = { 0 };
	//code_convert("zh_CN.GB18030", "utf-8", (char*)gb2312, 4, utf8, 16);

	//return 0;
	
	try {
		typedef deletable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>> F;
		std::wstring_convert <F> char_wchar_cvt(new F("zh_CN.GB2312"));
		std::wstring strW = char_wchar_cvt.from_bytes((const char*)gb2312);
		std::wstring_convert<std::codecvt_utf8 <wchar_t >, wchar_t> utf8_wstr_cvt;
		auto stru8 = utf8_wstr_cvt.to_bytes(strW);
		std::cout << stru8;
		//std::wcout << strW;
		//strW = L"你好";
		//std::wcout << strW;
		//auto str = char_wchar_cvt.to_bytes(strW);
		//printf("%s", str.c_str());
		printf("ok\r\n");
	}
	catch (const std::exception& ex) {
		std::cout << "Error: " << ex.what() << std::endl;
	}
	
	//new cvt_byname("Chinese_China.936")
	
    printf("hello from testlinuxsample!\n");
    return 0;
}