// testmp3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <stdint.h>
#include "byteswap.h"

#define	LITTLE_ENDIAN	1234
#define	BIG_ENDIAN		4321
#define BYTE_ORDER LITTLE_ENDIAN


struct Mp3DataFrameHeader {
	unsigned char frameSyncFlag1;//固定为0xff
#if BYTE_ORDER == BIG_ENDIAN
	unsigned char frameSyncFlag2 : 3;//为0b111
	unsigned char mpegVersion : 2;//00-MPEG 2.5   01-未定义     10-MPEG 2     11-MPEG 1
	unsigned char layerVersion : 2;//00-未定义      01-Layer 3     10-Layer 2      11-Layer 1
	unsigned char crc : 1;	//0-校验        1-不校验
#else
	unsigned char crc : 1;	//0-校验        1-不校验
	unsigned char layerVersion : 2;//00-未定义      01-Layer 3     10-Layer 2      11-Layer 1
	unsigned char mpegVersion : 2;//00-MPEG 2.5   01-未定义     10-MPEG 2     11-MPEG 1
	unsigned char frameSyncFlag2 : 3;//为0b111
#endif
#if BYTE_ORDER == BIG_ENDIAN
	unsigned char bitRateIndex : 4;//比特率索引
	unsigned char sampleRateIndex : 2;//采样率索引
	unsigned char paddingBit : 1;//是否填充，1 填充，0 不填充
	unsigned char privateBit : 1;//私有
#else
	unsigned char privateBit : 1;//私有
	unsigned char paddingBit : 1;//是否填充，1 填充，0 不填充
	unsigned char sampleRateIndex : 2;//采样率索引
	unsigned char bitRateIndex : 4;//比特率索引
#endif
#if BYTE_ORDER == BIG_ENDIAN
	unsigned char channelMode : 2;//通道00 - Stereo 01 - Joint Stereo 10 - Dual   11 - Single
	unsigned char externBits : 2;//
	unsigned char copyRightBit : 1;//0-不合法   1-合法
	unsigned char originalBit : 1;//0-非原版   1-原版
	unsigned char emphasize : 2;//用于声音经降噪压缩后再补偿的分类，很少用到，今后也可能不会用。	00 - 未定义     01 - 50 / 15ms     10 - 保留       11 - CCITT J.17
#else
	unsigned char emphasize : 2;
	unsigned char originalBit : 1;
	unsigned char copyRightBit : 1;
	unsigned char externBits : 2;//
	unsigned char channelMode : 2;//通道00 - Stereo 01 - Joint Stereo 10 - Dual   11 - Single
#endif
};

void printHeader(const Mp3DataFrameHeader &header) {
	switch (header.mpegVersion) {
	case 0b00:
		printf("mpegVersion: MPEG 2.5\n");
		break;
	case 0b01:
		printf("mpegVersion: Unknown\n");
		break;
	case 0b10:
		printf("mpegVersion: MPEG 2\n");
		break;
	case 0b11:
		printf("mpegVersion: MPEG 1\n");
		break;
	}
	switch (header.layerVersion) {
	case 0b00:
		printf("layerVersion: Unknown\n");
		break;
	case 0b01:
		printf("layerVersion: Layer 3\n");
		break;
	case 0b10:
		printf("layerVersion: Layer 2\n");
		break;
	case 0b11:
		printf("layerVersion: Layer 1\n");
		break;
	}
	if (0 == header.crc) {
		printf("crc: no\n");
	}
	else {
		printf("crc: yes\n");
	}
	int bitRate = 0;
	if (header.mpegVersion == 0b00 && header.layerVersion == 0b11) {

	}
	if (header.mpegVersion == 0b11 && header.layerVersion == 0b01) {
		const unsigned int bitRates[] = {
			0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0xffffffff };
		bitRate = bitRates[header.bitRateIndex];
	}
	std::string strBitRate;
	if (0 == bitRate) {
		strBitRate = "free";
	}
	else if (0xfffffffff == bitRate) {
		strBitRate = "bad";
	}
	else {
		strBitRate = std::to_string(bitRate);
	}
	printf("bitRate: %s\n", strBitRate.c_str());
	if (header.mpegVersion == 0b11) {
		switch (header.sampleRateIndex) {
		case 0b00:
			printf("sampleRate: 44.1kHz\n");
			break;
		case 0b01:
			printf("sampleRate: 48kHz\n");
			break;
		case 0b10:
			printf("sampleRate: 32kHz\n");
			break;
		case 0b11:
			printf("sampleRate: unknown\n");
			break;
		}
	}
}

#define TOTAL_FRAME_EXIST_FLAG 0x01
#define FILE_LENGTH_EXIST_FLAG 0x02
#define TOC_EXIST_FLAG 0x04
#define QUALITY_EXIST_FLAG 0x08
struct Mp3VBRHeader {
	char type[4];//Xing or Info 
	unsigned char reserved[3];
	unsigned char flags;
	//unsigned int frameCount;	//总帧数，big endian
	//unsigned int fileSize;	//文件长度big endian
	//unsigned char toc[100];	//TOC表，文件内快速寻址的位置索引，用于seek
	//unsigned int quaility;	//质量，0最好，100最差，big endian
};

int getVBROffset(const Mp3DataFrameHeader &header) {
	if (header.mpegVersion == 0b11) {//MPEG 1
		if (header.channelMode == 0b11) {//单声道
			return 18;
		}
		else {
			return 32;
		}
	}
	else if (header.mpegVersion == 0b00 || header.mpegVersion == 0b10) {//MPEG 2.5 MPEG 2
		if (header.channelMode == 0b11) {//单声道
			return 9;
		}
		else {
			return 18;
		}
	}
	else {
		assert(false);
		return 0;
	}
}

//一个mp3帧的采样数
int getSampleCountPerFrame(const Mp3DataFrameHeader &header) {
	if (header.mpegVersion == 0b11) {//MPEG 1
		switch (header.layerVersion) {
		case 0b01://Layer 3
			return 1152;
		case 0b10://Layer 2
			return 1152;
		case 0b11://Layer 1
			return 384;
		default:
			assert(false);
			return 0;
		}
	}
	else if (header.mpegVersion == 0b00 || header.mpegVersion == 0b10) {//MPEG 2.5 MPEG 2
		switch (header.layerVersion) {
		case 0b01://Layer 3
			return 576;
		case 0b10://Layer 2
			return 1152;
		case 0b11://Layer 1
			return 384;
		default:
			assert(false);
			return 0;
		}
	}
	else {
		assert(false);
		return 0;
	}
}

//采样率
int getSampleRate(const Mp3DataFrameHeader &header) {
	if (header.mpegVersion == 0b11) {//11-MPEG 1
		switch (header.sampleRateIndex) {
		case 0b00:
			return 44100;
		case 0b01:
			return 48000;
		case 0b10:
			return 32000;
		default:
			assert(false);
			return 0;
		}
	}
	else {
		assert(false);
		return 0;
	}
}

int getBitRate(const Mp3DataFrameHeader &header) {
	int bitRate = 0;
	if (header.mpegVersion == 0b11 && header.layerVersion == 0b01) {
		const unsigned int bitRates[] = {
			0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 0xffffffff };
		bitRate = bitRates[header.bitRateIndex];
	}
	else {
		assert(false);
	}
	if (bitRate == 0xffffffff) {
		bitRate = 0;
	}
	return bitRate * 1000;
}

int getPaddingCount(const Mp3DataFrameHeader &header) {
	if (0 == header.paddingBit) {
		return 0;
	}
	else {
		switch (header.layerVersion) {
		case 0b11://Layer 1
			return 32 / 8;
		case 0b01://Layer 3
		case 0b10://Layer 2
			return 8 / 8;
		default:
			assert(false);
			return 0;
		}
	}
}

struct Mp3Info {
	FILE *file;
	unsigned char szCheck[11];
	size_t checkLen;
	size_t curFrameReadLen;

	uint32_t firstAudioOffset;//第一个音频帧的偏移

	Mp3DataFrameHeader header;//当前帧头部
	Mp3DataFrameHeader vbrDataFrameHeader;

	bool haveParseFirstFrame;
	Mp3VBRHeader vbrHeader;//如果第一个帧包含vbr，则存储vbr
	uint32_t frameCount;
	uint32_t fileLenght;
	bool isHaveTOC;
	unsigned char toc[100];
	uint32_t quaility;
};

#define XING_NAME "Xing"
#define INFO_NAME "Info"
#define APETAGEX_NAME "APETAGEX"
#define LYRICSBEGIN_NAME "LYRICSBEGIN"
#define ID3V1_NAME "TAG"
#define ID3V2_NAME "ID3"

void parseXingHeader(Mp3Info &info) {
	Mp3DataFrameHeader &header = info.header;

	Mp3VBRHeader &vbrHeader = info.vbrHeader;
	if (info.checkLen > 0) {
		memcpy(&vbrHeader, info.szCheck, info.checkLen);
	}
	fread(reinterpret_cast<unsigned char*>(&vbrHeader) + info.checkLen, 1, sizeof(vbrHeader) - info.checkLen, info.file);
	assert(0 == strncmp(vbrHeader.type, XING_NAME, 4) || 0 == strncmp(vbrHeader.type, INFO_NAME, 4));
	info.curFrameReadLen += sizeof(Mp3VBRHeader);


	if (vbrHeader.flags & TOTAL_FRAME_EXIST_FLAG) {
		fread(&info.frameCount, 1, sizeof(info.frameCount), info.file);
		info.frameCount = ByteSwap::betoh(info.frameCount);
		info.curFrameReadLen += sizeof(info.frameCount);
	}
	if (vbrHeader.flags & FILE_LENGTH_EXIST_FLAG) {
		fread(&info.fileLenght, 1, sizeof(info.fileLenght), info.file);
		info.fileLenght = ByteSwap::betoh(info.fileLenght);
		info.curFrameReadLen += sizeof(info.fileLenght);
	}
	if (vbrHeader.flags & TOC_EXIST_FLAG) {
		info.isHaveTOC = true;
		fread(info.toc, 1, sizeof(info.toc), info.file);
		info.curFrameReadLen += sizeof(info.toc);
	}
	if (vbrHeader.flags & QUALITY_EXIST_FLAG) {
		fread(&info.quaility, 1, sizeof(info.quaility), info.file);
		info.quaility = ByteSwap::betoh(info.quaility);
		info.curFrameReadLen += sizeof(info.quaility);
	}

	info.vbrDataFrameHeader = header;
}

void parseFrame(Mp3Info &info) {
	Mp3DataFrameHeader &header = info.header;
	if (info.checkLen > 0) {
		memcpy(&header, info.szCheck, info.checkLen);
	}
	int needReadLen = sizeof(header) - info.checkLen;
	if (fread(reinterpret_cast<char*>(&header) + info.checkLen, 1, sizeof(header) - info.checkLen, info.file) != needReadLen) {
		throw - 1;
	}

	info.curFrameReadLen = sizeof(header);
	assert(header.frameSyncFlag1 == 0xFF);
	printf("\n");
	printHeader(header);

	bool needSetFirstAudioOffset = false;
	if (!info.haveParseFirstFrame) {
		info.haveParseFirstFrame = true;

		int seekOffset = getVBROffset(header);
		fseek(info.file, seekOffset, SEEK_CUR);
		info.curFrameReadLen += seekOffset;

		info.checkLen = fread(info.szCheck, 1, 4, info.file);
		if (strncmp(reinterpret_cast<const char*>(info.szCheck), XING_NAME, 4) == 0) {
			parseXingHeader(info);
			needSetFirstAudioOffset = true;
		}
		else if (strncmp(reinterpret_cast<const char*>(info.szCheck), INFO_NAME, 4) == 0) {
			parseXingHeader(info);
			needSetFirstAudioOffset = true;
		}
		else {
			info.curFrameReadLen += info.checkLen;
			info.firstAudioOffset = ftell(info.file);
			info.firstAudioOffset -= info.curFrameReadLen;
		}
	}

	int paddingBytes = getPaddingCount(header);
	int frameLen = int(144 * getBitRate(header) / getSampleRate(header) + paddingBytes);
	int sampleCountPerFrame = getSampleCountPerFrame(header);
	int totalSampleCount = info.frameCount * sampleCountPerFrame;
	int sampleRate = getSampleRate(header);
	int musicSecond = totalSampleCount / sampleRate;

	fseek(info.file, frameLen - info.curFrameReadLen, SEEK_CUR);
	if (needSetFirstAudioOffset) {
		info.firstAudioOffset = ftell(info.file);
	}
}

struct Mp3ApeTagExHeader {
	char tag[8];//APETAGEX ascii码
	uint32_t version;//APEV版本，现在常用APEV2（D0 07 00 00）1000 or 2000
	uint32_t size;//所有标签帧和标签尾的总长度，低位在前，不包括头部
	uint32_t count;//标签帧个数，低位在前
	uint32_t flag;	//0
	uint64_t reserved;//0
};

struct Mp3ApeTagExFrame {
	uint32_t frameSize;//帧内容长度，低位在前
	uint32_t flags;//
	//字段名，\0结尾
	//字段值，长度由size决定
};

void parseAptTagExFrame(Mp3Info &info) {
	Mp3ApeTagExFrame aptFrame = Mp3ApeTagExFrame();
	if (fread(&aptFrame, 1, sizeof(aptFrame), info.file) != sizeof(aptFrame)) {
		throw - 1;
	}
	info.curFrameReadLen += sizeof(aptFrame);
	aptFrame.frameSize = ByteSwap::letoh(aptFrame.frameSize);
	std::string tagName, tagValue;
	char tmpChar;
	while (1 == fread(&tmpChar, 1, 1, info.file)) {
		info.curFrameReadLen++;
		if (tmpChar != '\0') {
			tagName += tmpChar;
		}
		else {
			break;
		}
	}
	tagValue.resize(aptFrame.frameSize);
	if (fread(&*tagValue.begin(), 1, tagValue.size(), info.file) != tagValue.size()) {
		throw - 1;
	}
	info.curFrameReadLen += tagValue.size();
	printf("apt tag name: %s value: %s\n", tagName.c_str(), tagValue.c_str());
}

void parseApeTagEx(Mp3Info &info) {
	Mp3ApeTagExHeader aptTagExHeader = Mp3ApeTagExHeader();
	if (info.checkLen > 0) {
		memcpy(&aptTagExHeader, info.szCheck, info.checkLen);
	}
	int readLen = sizeof(aptTagExHeader) - info.checkLen;
	if (fread(reinterpret_cast<unsigned char*>(&aptTagExHeader) + info.checkLen, 1, readLen, info.file) != readLen) {
		throw - 1;
	}
	assert(0 == strncmp(aptTagExHeader.tag, APETAGEX_NAME, 8));
	aptTagExHeader.version = ByteSwap::letoh(aptTagExHeader.version);
	aptTagExHeader.size = ByteSwap::letoh(aptTagExHeader.size);
	aptTagExHeader.count = ByteSwap::letoh(aptTagExHeader.count);
	aptTagExHeader.flag = ByteSwap::letoh(aptTagExHeader.flag);

	printf("aptTag version: %d", aptTagExHeader.version);
	printf("aptTag size: %d", aptTagExHeader.size);
	printf("aptTag count: %d", aptTagExHeader.count);

	info.curFrameReadLen = 0;//不包含头部
	for (unsigned int i = 0; i < aptTagExHeader.count; i++) {
		parseAptTagExFrame(info);
	}

	int frameLen = aptTagExHeader.size;
	fseek(info.file, frameLen - info.curFrameReadLen, SEEK_CUR);
}

struct Mp3LyricsHeader {
	//LYRICSBEGIN
	//001065LYRICS200
};
void getLyricsNamValue(Mp3Info &info, std::string &name, std::string &value) {
	name.resize(3);
	if (3 != fread(&*name.begin(), 1, 3, info.file)) {
		throw - 1;
	}
	info.curFrameReadLen += 3;

	if (name[0] >= '0' && name[0] <= '9') {
		//到达末尾了
		std::string totalLen(6, '\0');
		memcpy(&totalLen[0], name.data(), 3);
		if (3 != fread(&totalLen[3], 1, 3, info.file)) {
			assert(false);
			throw - 1;
		}
		info.curFrameReadLen += 3;
		name = totalLen;
		value.resize(9);
		if (9 != fread(&value[0], 1, 9, info.file)) {
			assert(false);
			throw - 1;
		}
		info.curFrameReadLen += 9;
	}
	else {
		std::string valueLength(5, '\0');
		if (5 != fread(&*valueLength.begin(), 1, 5, info.file)) {
			throw - 1;
		}
		info.curFrameReadLen += 5;

		int len = atoi(valueLength.c_str());
		value.resize(len);
		if (len != fread(&*value.begin(), 1, len, info.file)) {
			assert(false);
			throw - 1;
		}
		info.curFrameReadLen += len;
	}
}
void parseLyrics(Mp3Info &info) {
	info.curFrameReadLen = strlen(LYRICSBEGIN_NAME);
	while (true) {
		std::string name, value;
		getLyricsNamValue(info, name, value);
		if (name.size() > 3) {
			break;
		}
		printf("Lyrics name: %s\n", name.c_str());
		printf("Lyrics value: %s\n", value.c_str());
	}
}

struct Mp3ID3V1Comment {
	char comment[28];
	unsigned char flag;//0 存在曲目，非0，不存在曲目
	unsigned char track;//曲目，如果flag是0
};

struct Mp3ID3V1Header {
	char tag[3];//TAG
	char title[30];//歌曲名
	char artist[30];//歌手名
	char album[30];//专辑名
	char year[4];	//日期
	union Comment
	{
		Mp3ID3V1Comment commentTrack;
		char commnet[30];
	}comment;//注释信息
	unsigned char genre;//歌曲风格
};

void parseID3V1(Mp3Info &info) {
	Mp3ID3V1Header id3V1Header = Mp3ID3V1Header();
	if (info.checkLen > 0) {
		memcpy(&id3V1Header, info.szCheck, info.checkLen);
	}
	int readLen = sizeof(Mp3ID3V1Header) - info.checkLen;
	if (readLen != fread(reinterpret_cast<unsigned char*>(&id3V1Header) + info.checkLen, 1, readLen, info.file)) {
		throw -1;
	}
	std::string strTmp;
	strTmp.assign(id3V1Header.title, 30);
	printf("ID3V1 title: %s\n", strTmp.c_str());
	
	strTmp.assign(id3V1Header.artist, 30);
	printf("ID3V1 artist: %s\n", strTmp.c_str());

	strTmp.assign(id3V1Header.album, 30);
	printf("ID3V1 album: %s\n", strTmp.c_str());

	strTmp.assign(id3V1Header.year, 4);
	printf("ID3V1 year: %s\n", strTmp.c_str());

	if (0 == id3V1Header.comment.commentTrack.flag) {
		strTmp.assign(id3V1Header.comment.commentTrack.comment, 28);
		printf("ID3V1 commnet: %s\n", strTmp.c_str());
		printf("ID3V1 track: %d\n", (int)id3V1Header.comment.commentTrack.track);
	}
	else {
		strTmp.assign(id3V1Header.comment.commnet, 30);
		printf("ID3V1 commnet: %s\n", strTmp.c_str());
	}

	printf("ID3V1 genre: %d", (int)id3V1Header.genre);
}

struct Mp3ID3V2Header {
	char tag[3];//ID3
	uint8_t version;//版本号
	uint8_t subversion;//子版本号
	uint8_t flag;//0babcd0000  a为Unsynchronisation b为Extended header c为Experimental indicator d - Footer present(10bytes)
	uint8_t sizes[4];//标签内容长度，不包括头部，var size = size4 & 0x7f | ((size3 & 0x7f) << 7) | ((size2 & 0x7f) << 14) | ((size1 & 0x7f) << 21);
	//扩展字节
};
static_assert(sizeof(Mp3ID3V2Header) == 10, "");
#pragma pack(1)
struct  Mp3ID3V2HeaderExtended {
	uint32_t size;
	uint16_t flags;
	uint32_t paddingSize;
};
#pragma pack()
static_assert(sizeof(Mp3ID3V2HeaderExtended) == 10, "");

inline uint32_t getSize(uint8_t (&sizes)[4]) {
	uint32_t size = sizes[3] & 0x7f | ((sizes[2] & 0x7f) << 7) | ((sizes[1] & 0x7f) << 14) | ((sizes[0] & 0x7f) << 21);
	return size;
}

struct Mp3ID3V2Frame {
	char frame[4];//ascii字符，标识符名称
	uint8_t sizes[4];//标签内容长度，不包括头部，var size = size4 & 0x7f | ((size3 & 0x7f) << 7) | ((size2 & 0x7f) << 14) | ((size1 & 0x7f) << 21);
	uint16_t flags;
	//uint32_t encode;//内容所用的编码
	//data 至少1个字节
};
static_assert(sizeof(Mp3ID3V2Frame) == 10, "");

void parseID3V2Frame(Mp3Info &info, uint32_t totalSize) {
	while (info.curFrameReadLen < totalSize){
		Mp3ID3V2Frame frame = Mp3ID3V2Frame();
		if (sizeof(frame) != fread(&frame, 1, sizeof(frame), info.file)) {
			throw - 1;
		}
		info.curFrameReadLen += sizeof(frame);
		if (frame.frame[0] >= '0' && frame.frame[0] <= '9'
			|| frame.frame[0] >= 'A' && frame.frame[0] <= 'Z') {
			uint32_t size = getSize(frame.sizes);
			frame.flags = ByteSwap::betoh(frame.flags);
			std::string value(size, '\0');
			if (fread(&value[0], 1, value.size(), info.file) != value.size()) {
				throw - 1;
			}
			info.curFrameReadLen += value.size();
			/*
			$00 – ISO-8859-1 (LATIN-1, Identical to ASCII for values smaller than 0x80).
			$01 – UCS-2 encoded Unicode with BOM, in ID3v2.2 and ID3v2.3.
			$02 – UTF-16BE encoded Unicode without BOM, in ID3v2.4.
			$03 – UTF-8 encoded Unicode, in ID3v2.4.
			*/
			if (value[0] >= 0 && value[0] <= 0x03) {
				value.erase(value.begin());
			}
			printf("id3v2 frame %s: %s\n", std::string(frame.frame, 4).c_str(), value.c_str());
		}
		else {
			break;
		}
		
	}
}

void parseID3V2(Mp3Info &info) {
	Mp3ID3V2Header id3V2Header = Mp3ID3V2Header();
	if (info.checkLen > 0) {
		memcpy(&id3V2Header, info.szCheck, info.checkLen);
	}
	int readLen = sizeof(id3V2Header) - info.checkLen;
	if (readLen != fread(reinterpret_cast<unsigned char*>(&id3V2Header) + info.checkLen, 1, readLen, info.file)) {
		throw - 1;
	}
	uint32_t size = getSize(id3V2Header.sizes);
	int framesSize = size;
	if (id3V2Header.flag & 0b01000000) {
		//有扩展头
		Mp3ID3V2HeaderExtended headerExtended = Mp3ID3V2HeaderExtended();
		if (sizeof(Mp3ID3V2HeaderExtended) != fread(&headerExtended, 1, sizeof(Mp3ID3V2HeaderExtended), info.file)) {
			throw - 1;
		}
		framesSize -= sizeof(Mp3ID3V2HeaderExtended);
		assert(false);
	}
	if (id3V2Header.flag & 0b00010000) {
		framesSize -= 10;
		assert(false);
	}
	info.curFrameReadLen = 0;
	parseID3V2Frame(info, framesSize);
	fseek(info.file, framesSize - info.curFrameReadLen, SEEK_CUR);
}

void parseMp3(Mp3Info &info) {
	
	try {
		while (true)
		{
			info.checkLen = fread(info.szCheck, 1, 4, info.file);
			if (info.checkLen == 4) {
				if (info.szCheck[0] == 0xFF) {
					parseFrame(info);
				}
				else{
					if (0 == strncmp(reinterpret_cast<const char*>(info.szCheck), APETAGEX_NAME, 4)) {
						int readLen = fread(info.szCheck + 4, 1, 4, info.file);
						if (readLen != 4) {
							break;
						}
						if (0 == strncmp(reinterpret_cast<const char*>(info.szCheck), APETAGEX_NAME, 8)) {
							info.checkLen += 4;
							parseApeTagEx(info);
						}
						else {
							assert(false);
							printf("parse APETAGEX_NAME error \n");
							break;
						}
					}
					else if (0 == strncmp(reinterpret_cast<const char*>(info.szCheck), LYRICSBEGIN_NAME, 4)) {
						int readLen = fread(info.szCheck + 4, 1, 7, info.file);
						if (readLen != 7) {
							break;
						}
						if (0 == strncmp(reinterpret_cast<const char*>(info.szCheck), LYRICSBEGIN_NAME, 11)) {
							info.checkLen += 7;
							parseLyrics(info);
						}
						else {
							assert(false);
							break;
						}
					}
					else if (0 == strncmp(reinterpret_cast<const char*>(info.szCheck), ID3V1_NAME, 3)) {
						parseID3V1(info);
					}
					else if (0 == strncmp(reinterpret_cast<const char*>(info.szCheck), ID3V2_NAME, 3)) {
						parseID3V2(info);
					}
					else {
						assert(false);
						break;
					}
				}
			}
			else if (0 == info.checkLen){
				printf("parse end\n");
				break;
			}
			else {
				printf("parse error\n");
				assert(false);
				break;
			}
		}
	}
	catch (...) {

	}
}

bool seekToFrameHeader(FILE *file) {
	uint8_t c;
	while (1 == fread(&c, 1, 1, file)) {
		if (c == 0xff) {
			if (1 == fread(&c, 1, 1, file)) {
				if ((c & 0b11100000) == 0b11100000) {
					fseek(file, -2, SEEK_CUR);
					return true;
				}
			}
		}
	}
	return false;
}


int main()
{
	Mp3DataFrameHeader tmpHeader;
	char cc[4] = { 0xFF, 0xFB, 0xb4, 0x40 };
	memcpy(&tmpHeader, cc, sizeof(tmpHeader));

	int frameLen2 = int(144 * getBitRate(tmpHeader) / getSampleRate(tmpHeader) + getPaddingCount(tmpHeader));


	long curPos = 0;
	Mp3Info info = Mp3Info();
	info.file = fopen("d:/test2.mp3", "rb");
	parseMp3(info);
	

	auto &header = info.vbrDataFrameHeader;

	int paddingBytes = getPaddingCount(header);
	int sampleRate = getSampleRate(header);
	int bitRate = getBitRate(header);
	int frameLen = int(144 * bitRate / sampleRate + paddingBytes);
	int sampleCountPerFrame = getSampleCountPerFrame(header);
	int totalSampleCount = info.frameCount * sampleCountPerFrame;
	int totalSecond = totalSampleCount / sampleRate;

	int seekSecond = 30;
	int tocIndex = seekSecond * 100 / totalSecond;
	uint8_t tocValue = info.toc[tocIndex];
	double offsetPercent = (double)tocValue / 256;
	int offsetSampleCount = offsetPercent * totalSampleCount;
	int offsetFrameCount = offsetSampleCount / sampleCountPerFrame;
	int offset = offsetFrameCount * frameLen + info.firstAudioOffset;


	
	fseek(info.file, offset, SEEK_SET);
	if (!seekToFrameHeader(info.file)) {
		assert(false);
	}

	parseMp3(info);

	fclose(info.file);
	info.file = NULL;
	return 0;
}

