#include <iostream>
extern "C"
{
#include <libavcodec/avcodec.h>
}

#pragma comment(lib, "avcodec.lib")

int main(int argc, char *argv[])
{
	std::cout << avcodec_configuration() << std::endl;

//64λ
#ifdef _WIN64
	std::cout << "x64" << std::endl;
#endif

//32λ
#ifdef WIN32
	std::cout << "x32" << std::endl;
#endif

//32λ��64λ����������linux��windows
#ifdef _WIN32
	std::cout << "windows" << std::endl;
#else
	std::cout << "not windows" << std::endl;
#endif
	getchar();
	return 0;
}
