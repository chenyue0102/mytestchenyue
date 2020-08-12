// testffmpeg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PlayManager.h"

int main()
{
	PlayManager playManager;
	playManager.openFile("D:/test.mp4");
	getchar();
    return 0;
}

