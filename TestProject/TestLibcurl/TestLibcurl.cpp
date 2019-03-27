// TestLibcurl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <sys/stat.h>
#include <string>
#include "curl.h"
#include "URLWrapBase.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	const char *pWriteFileName = (const char*)userdata;
	FILE *fp = fopen(pWriteFileName, "ab+");
	fwrite(ptr, 1, size * nmemb, fp);
	fclose(fp);
	return size * nmemb;
}

size_t process_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}

void test()
{
	const char *pFileName = "d:/1.png";

	struct stat s = { 0 };
	stat(pFileName, &s);
	CURLcode ret = CURLE_OK;
	CURL *curl = curl_easy_init();
	ret = curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com/img/bd_logo1.png");
	ret = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_callback);
	ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, pFileName);

	ret = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	ret = curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, &process_callback);
	ret = curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, pFileName);
	ret = curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	std::string strRange = std::to_string(s.st_size);
	strRange += "-";
	ret = curl_easy_setopt(curl, CURLOPT_RANGE, strRange.c_str());

	ret = curl_easy_perform(curl);

	curl_easy_cleanup(curl);
}

int main()
{
	CURLcode ret = CURLE_OK;
	ret = curl_global_init(CURL_GLOBAL_ALL);
	CURLWrapBase base;
	base.init();

	int a = 0;

	do
	{
		printf("0:exit 1:destroy 2:download 3:query\n");
		scanf("%d", &a);
		switch (a)
		{
		case 0:
			break;
		case 1:
			base.destroy();
			break;
		case 2:
			base.downloadFile("https://cn.bing.com/th?id=OHR.TaoiseachDept_ZH-CN0902989482_1920x1080.jpg&rf=NorthMale_1920x1080.jpg&pid=hp", 
				"d:/1.png", &base);
			break;
		case 3:
			base.getData("https://cn.bing.com/th?id=OHR.TaoiseachDept_ZH-CN0902989482_1920x1080.jpg&rf=NorthMale_1920x1080.jpg&pid=hp",
				&base);
			break;
		}
	} while (0 != a);

	

	getchar();
	curl_global_cleanup();
    return 0;
}