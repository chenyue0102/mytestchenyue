// TestLibcurl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <sys/stat.h>
#include <string>
#include <assert.h>
#include <algorithm>
#include "curl.h"
#include "URLWrapBase.h"
#include "FileWrite.h"
#include "URLWrap.h"
#include "FileDownload.h"

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

class MyURLWrap : public CURLWrap, public ICURLDownloadCallback
{
public:
	MyURLWrap()
	{
		setCallback(this, this);
		m_f = fopen("d:/1.exe", "wb");
	}
	~MyURLWrap()
	{
		fclose(m_f);
	}
	virtual size_t writeCallBack(char * ptr, size_t size, size_t nmemb, void *userdata)
	{
		fwrite(ptr, size, nmemb, m_f);
		fflush(m_f);
		if (0 == size || 0 == nmemb)
		{
			return 0;
		}
		return size * nmemb;
	}
	virtual int progressCallback(curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow, void *userdata)
	{
		return 0;
	}
private:
	FILE *m_f;
};

int main()
{
	const char *purl = "http://211.136.65.164/cache/dl.static.iqiyi.com/hz/IQIYIsetup_z43.exe?ich_args2=65-09161409026241_197f7f59bf1ee8895de144fe3237d400_10010301_9c896329dfc4f8d3933a518939a83798_5e26eb34460c090336c1a2a00c5b362f";
	//const char *purl = "http://yesky.51down.org.cn/2019/08/23/Postman_v7.5.0.zip";
	CURLcode ret = CURLE_OK;
	ret = curl_global_init(CURL_GLOBAL_ALL);

	int download = 1024 * 1024 * 30;
	FileRange range;
	range.offset = 38960304 - download;
	range.size = download;
	FileRangeArray ranges = { range };
	FileDownload d;
	d.setUrl(purl);
	d.setFilePathName("d:/1.exe");
	d.setRanges(ranges);
	d.perform();
	std::this_thread::sleep_for(std::chrono::seconds(99999));

	CURLM *urlm = curl_multi_init();
	//long long fileSize = MyURLWrap::getDownloadFileLength(purl);
	/*MyURLWrap *myurl = new MyURLWrap;
	
	myurl->request(purl);
	curl_multi_add_handle(urlm, myurl->getCURL());
	int still_running = 0;
	int numfds = 0;
	CURLMcode mc = curl_multi_perform(urlm, &still_running);

	while (still_running)
	{
		mc = curl_multi_wait(urlm, nullptr, 0, 1000, &numfds);
		if (CURLM_OK != mc)
		{
			break;
		}
		if (!numfds)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		mc = curl_multi_perform(urlm, &still_running);
	}
	long code = 0;
	CURLcode coderet = curl_easy_getinfo(myurl->getCURL(), CURLINFO_RESPONSE_CODE, &code);
	coderet = curl_easy_getinfo(myurl->getCURL(), CURLINFO_RESPONSE_CODE, &code);
	curl_multi_remove_handle(urlm, myurl->getCURL());
	delete myurl;*/

	FileWrite fileWrite;
	std::vector<unsigned char> writeC = { 0,1,2,3,4,5,6,7,8,9 };
	std::random_shuffle(writeC.begin(), writeC.end());
	fileWrite.open("d:/1.tmp", "rb+");
	FileRange fileRange;
	fileRange.offset = 0;
	fileRange.size = writeC.size();
	std::vector<FileRange> fileRanges = { fileRange };
	fileWrite.setNotGetFileRange(fileRanges);
	for (auto c : writeC)
	{
		fileWrite.write(&c, c, 1);
	}
	fileWrite.close();

	
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
				"d:/1.png", 1);
			break;
		case 3:
			base.getData("https://cn.bing.com/th?id=OHR.TaoiseachDept_ZH-CN0902989482_1920x1080.jpg&rf=NorthMale_1920x1080.jpg&pid=hp",
				1);
			break;
		}
	} while (0 != a);

	

	getchar();
	curl_global_cleanup();
    return 0;
}