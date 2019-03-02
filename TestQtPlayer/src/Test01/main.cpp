#include <iostream>
extern "C"
{
#include <libavcodec/avcodec.h>
}

#pragma comment(lib, "avcodec.lib")

int main(int argc, char *argv[])
{
	std::cout << avcodec_configuration() << std::endl;

//64位
#ifdef _WIN64
	std::cout << "x64" << std::endl;
#endif

//32位
#ifdef WIN32
	std::cout << "x32" << std::endl;
#endif

//32位和64位，用于区分linux和windows
#ifdef _WIN32
	std::cout << "windows" << std::endl;
#else
	std::cout << "not windows" << std::endl;
#endif
	getchar();
	return 0;
}
