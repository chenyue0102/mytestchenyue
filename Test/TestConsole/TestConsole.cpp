// TestConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include "RingQueue.h"

int main()
{
	uint32_t s = 0;
	uint32_t s2 = 0;
	s -= 6;
	s2 += 2;
	uint32_t s3 = s2 - s;
	RingQueue ringQueue(8);
	size_t dataSize = ringQueue.getDataSize();
	size_t freeSize = ringQueue.getFreeSize();
	char  str[] = "123456789";
	size_t putSize = ringQueue.put(str, 2);
	char out[12] = { 0 };
	size_t getSize = ringQueue.get(out, 12);
	putSize = ringQueue.put(str, sizeof(str));
	getSize = ringQueue.get(out, 12);
    return 0;
}

