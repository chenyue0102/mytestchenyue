// testreadmp4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <fstream>
#include <map>


typedef void (*PARSEFUN)(FILE* f, int realDataSize, int tabCount);
std::map<std::string, PARSEFUN> g_parseFun;

bool isBigEndian()
{
    union
    {
        uint32_t i;
        unsigned char s[sizeof(uint32_t)];
    }u;
    u.i = 0x12345678;
    return 0x12 == u.s[0];
}

uint64_t ftol(uint64_t i)
{
    if (isBigEndian()) 
    {
        return i;
    }
    else
    {
        //0x0123456789abcdef
        return 
            ((i & 0xff00000000000000LL) >> 56) |
            ((i & 0x00ff000000000000LL) >> 40) |
            ((i & 0x0000ff0000000000LL) >> 24) |
            ((i & 0x000000ff00000000LL) >> 8) |
            ((i & 0x00000000ff000000LL) << 8) |
            ((i & 0x0000000000ff0000LL) << 24) |
            ((i & 0x000000000000ff00LL) << 40) | 
            ((i & 0x00000000000000ffLL) << 56);
    }
}

uint32_t ftol(uint32_t i)
{
    if (isBigEndian())
    {
        return i;
    }
    else
    {
        //0x12345678;
        return 
            ((i & 0xff000000) >> 24) |
            ((i & 0x00ff0000) >> 8) |
            ((i & 0x0000ff00) << 8) |
            ((i & 0x000000ff) << 24);
    }
}

uint16_t ftol(uint16_t i)
{
    0x1234;
    return ((i & 0xff00) >> 8) |
        ((i & 0x00ff) << 8);
}

uint32_t flv24to32(uint8_t(&num)[3])
{
    uint32_t size = 0;
    size += num[0];
    size <<= 8;
    size += num[1];
    size <<= 8;
    size += num[2];
    return size;
}

#pragma warning(disable : 4200)
struct FileTypeBox
{
    char majorBrand[4];
    uint32_t minorVersion;
    char compatibleBrands[];
};

void printTab(int tabCount)
{
    for (int i = 0; i < tabCount; i++)
    {
        printf("%c", '\t');
    }
}

void myfread(FILE* f, void* data, int dataLen)
{
    if (fread(data, 1, (size_t)dataLen, f) != dataLen)
    {
        assert(false);
        throw - 1;
    }
}

void parseftyp(FILE* f, int realDataSize, int tabCount)
{
    printTab(tabCount);
    std::shared_ptr<FileTypeBox> fileTypeBox((FileTypeBox*)malloc((size_t)realDataSize), &free);
    myfread(f, fileTypeBox.get(), realDataSize);
    fileTypeBox->minorVersion = ftol(fileTypeBox->minorVersion);
    printf(" majorBrand=%.*s minorVersion=%u compatibleBrands=%.*s\n", 4, fileTypeBox->majorBrand, fileTypeBox->minorVersion,
        int(realDataSize - 8), fileTypeBox->compatibleBrands);
}
void parseFormat(FILE* f, int realDataSize, int tabCount);
void parsemoov(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}

struct MovieHeaderBox0
{
    uint8_t version;             //
    uint8_t flags[3];
    uint32_t creationTime;      //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t modificationTime; //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t timeScale;         //时间刻度的时间值,即每秒通过的时间单位数
    uint32_t duration;          //以时间刻度单位表示电影持续时间的时间值,movie时长:duration/timeScale second

    uint32_t rate;              //播放此movie的速度。1.0为正常播放速度
    uint16_t volume;            //播放此movie的音量。1.0为最大音量
    int8_t reserved[10];         //保留
    int32_t matrix[9];          //该矩阵定义了此movie中两个坐标空间的映射关系
    int32_t previewTime;        //开始预览此movie的时间
    int32_t previewDuration;    //以movie的time scale为单位，预览的duration
    int32_t posterTime;         //The time value of the time of the movie poster.
    int32_t selectionTime;      //The time value for the start time of the current selection.
    int32_t selectionDuration;  //The duration of the current selection in movie time scale units.
    int32_t currentTime;        //当前时间
    uint16_t nextTrackId;       //下一个待添加track的ID值。0不是一个有效的ID值。
};
#pragma pack(1)
struct MovieHeaderBox1
{
    uint8_t version;             //
    uint8_t flags[3];
    uint64_t creationTime;      //基准时间是1904 - 1 - 1 0:00 AM
    uint64_t modificationTime; //基准时间是1904 - 1 - 1 0:00 AM
    uint64_t timeScale;         //时间刻度的时间值,即每秒通过的时间单位数
    uint64_t duration;          //以时间刻度单位表示电影持续时间的时间值,movie时长:duration/timeScale second

    uint32_t rate;              //播放此movie的速度。16.16浮点表示,0x00010000 为1.0
    uint16_t volume;            //播放此movie的音量。8.8浮点表示,0x0100为1.0
    int8_t reserved[10];         //保留
    int32_t matrix[9];          //该矩阵定义了此movie中两个坐标空间的映射关系
    int32_t previewTime;        //开始预览此movie的时间
    int32_t previewDuration;    //以movie的time scale为单位，预览的duration
    int32_t posterTime;         //The time value of the time of the movie poster.
    int32_t selectionTime;      //The time value for the start time of the current selection.
    int32_t selectionDuration;  //The duration of the current selection in movie time scale units.
    int32_t currentTime;        //当前时间
    uint16_t nextTrackId;       //下一个待添加track的ID值。0不是一个有效的ID值。
};
#pragma pack()
void parsemvhd(FILE* f, int realDataSize, int tabCount)
{
    printTab(tabCount);
    MovieHeaderBox0 movieHeaderBox = { 0 };
    myfread(f, &movieHeaderBox, sizeof(MovieHeaderBox0));
	movieHeaderBox.creationTime = ftol(movieHeaderBox.creationTime);
	movieHeaderBox.modificationTime = ftol(movieHeaderBox.modificationTime);
	movieHeaderBox.timeScale = ftol(movieHeaderBox.timeScale);
	movieHeaderBox.duration = ftol(movieHeaderBox.duration);
	movieHeaderBox.rate = ftol(movieHeaderBox.rate);
	movieHeaderBox.volume = ftol(movieHeaderBox.volume);
	printf("creationTime=%u modificationTime=%u timeScale=%u duration=%u", movieHeaderBox.creationTime, movieHeaderBox.modificationTime,
		movieHeaderBox.timeScale, movieHeaderBox.duration);
    printf("\n");
}

struct TrackHeaderBox0
{
    uint8_t version;             //
    uint8_t flags[3];               //0x0001 track生效,0x0002track用在movie中,0x0004用在movie预览中,0x0008move poster中
    uint32_t creationTime;      //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t modificationTime; //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t trackID;
    uint32_t reserved;
    uint32_t duration;

    uint32_t reserved2[2];      //
    uint16_t layer;              //视频层,0表示最上层
    uint16_t alternateGroup;       //track分组,0表示没有与其他track有群组关系
    uint16_t volume;             //声音8.8形式
    uint16_t reserved3;
    int32_t matrix[9];
    uint32_t width;                 //16.16形式
    uint32_t height;                //16.16形式
};
struct TrackHeaderBox1
{
    uint8_t version;             //
    uint64_t creationTime;      //基准时间是1904 - 1 - 1 0:00 AM
    uint64_t modificationTime; //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t trackID;
    uint32_t reserved;
    uint64_t duration;
};

#define PRINTFU(name) \
    std::cout << #name##"=" << box.name << " ";

void printFloat(uint32_t i)
{
    uint16_t h = (i >> 16 & 0xffff), l = (i & 0xffff);
    printf("%hu.%hu", h, l);
}

void printFloat(uint16_t i)
{
    uint16_t h = (i >> 8 & 0xff00), l = (i & 0x00ff);
    printf("%hu.%hu", h, l);
}
    
void parsetkhd(FILE* f, int realDataSize, int tabCount)
{
    printTab(tabCount);
    TrackHeaderBox0 box = { 0 };
    myfread(f, &box, sizeof(box));
    //box.version = ftol(box.version);
    box.creationTime = ftol(box.creationTime);
    box.trackID = ftol(box.trackID);
    box.duration = ftol(box.duration);
    box.layer = ftol(box.layer);
    box.alternateGroup = ftol(box.alternateGroup);
    box.volume = ftol(box.volume);
    box.width = ftol(box.width);
    box.height = ftol(box.height);
    std::cout << "version=" << (int)box.version << " ";
    std::cout << "flags=" << (int)box.flags[2] << " ";
    //PRINTFU(version);
    //PRINTFU(flags[2]);
    PRINTFU(creationTime);
    PRINTFU(modificationTime);
    PRINTFU(trackID);
    PRINTFU(duration);
    PRINTFU(layer);
    PRINTFU(alternateGroup);
    printf("\n");
    printTab(tabCount);
    printf("volume="); printFloat(box.volume);
    printf(" width="); printFloat(box.width);
    printf(" height="); printFloat(box.height);
    printf("\n");
}
void parsetrak(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}

void parsetmdia(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}
//媒体头
struct MediaHeaderBox
{
    uint8_t version;             //
    uint8_t flags[3];
    uint32_t creationTime;      //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t modificationTime; //基准时间是1904 - 1 - 1 0:00 AM
    uint32_t timeScale;         //时间刻度的时间值,即每秒通过的时间单位数
    uint32_t duration;          //以时间刻度单位表示电影持续时间的时间值,movie时长:duration/timeScale second
    uint16_t language;          //媒体语言代码
    uint16_t quality;           //媒体质量
};
void parsemdhd(FILE* f, int realDataSize, int tabCount)
{
    MediaHeaderBox box = { 0 };
    myfread(f, &box, sizeof(box));
    printTab(tabCount);
    box.creationTime = ftol(box.creationTime);
    box.modificationTime = ftol(box.modificationTime);
    box.timeScale = ftol(box.timeScale);
    box.duration = ftol(box.duration);
    box.language = ftol(box.language);
    box.quality = ftol(box.quality);
    printf("timeScale=%u duration=%u language=%hu quality=%hu\n", box.timeScale, box.duration, box.language, box.quality);
}

//句柄参考
struct HandlerReferenceBox
{
    uint8_t version;             //
    uint8_t flags[3];
    char component[4];         //类型'mhlr' media handlers, 'dhlr' data handlers
    char subComponent[4];      //子类型,类型为'mhlr',则子类型为'vide' video,'soun' sound, 'dhlr' 数据引用类型如'alis'文件别名
    uint32_t reserved[3];
    char componentName[0];      //类型名字,可以为0
};

void parsehdlr(FILE* f, int realDataSize, int tabCount)
{
    printTab(tabCount);
    std::shared_ptr< HandlerReferenceBox> box((HandlerReferenceBox*)malloc(realDataSize), &free);
    myfread(f, box.get(), realDataSize);
    printf("component=%.*s subComponent=%.*s componentName=%.*s\n", 4, box->component, 4, box->subComponent,
        realDataSize - sizeof(HandlerReferenceBox), box->componentName);
}

void parseminf(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}

//vmhd,视频信息头
struct VideoMediaInfoBox
{
    uint8_t version;             //
    uint8_t flags[3];           //固定为0x000001
    uint16_t mode;              //传输模式
    uint8_t opColor[3];         //颜色值,RGB形式
};

void parsevmhd(FILE* f, int realDataSize, int tabCount)
{
    VideoMediaInfoBox box;
    myfread(f, &box, sizeof(box));
    box.mode = ftol(box.mode);
    printTab(tabCount);
    printf("mode=%u opColor=%u,%u,%u\n", box.mode, (int)box.opColor[0], (int)box.opColor[1], (int)box.opColor[2]);
}

//smhd
struct SoundMediaInfoBox
{
    uint8_t version;             //
    uint8_t flags[3];           //固定为0
    uint16_t equalization;      //均衡,控制2个扬声器声音混合效果
    uint16_t reserved;          //
};

void parsevsmhd(FILE* f, int realDataSize, int tabCount)
{
    SoundMediaInfoBox box = { 0 };
    myfread(f, &box, sizeof(box));
    box.equalization = ftol(box.equalization);
    printTab(tabCount);
    printf("equalization=%u\n", box.equalization);
}

struct HeaderCommon
{
    uint32_t size;
    char type[4];
};

struct HeaderFlag
{
    uint8_t version;             //
    uint8_t flags[3];           //
};

struct DataReferenceData
{
    uint32_t size;              //尺寸
    char type[4];               //类型'url','alis','rsrc'
    uint8_t version;             //
    uint8_t flags[3];           //固定为0x000001
    uint8_t data[0];
};
//dref
struct DataReferenceBox
{
    uint8_t version;             //
    uint8_t flags[3];           //固定为0
    uint32_t itemCount;             //条目数
    //DataReferenceBox item[0];
};
void parsedref(FILE* f, int realDataSize, int tabCount)
{
    DataReferenceBox box;
    myfread(f, &box, sizeof(box));
    printTab(tabCount);
    box.itemCount = ftol(box.itemCount);
    printf("itemCount=%u \n", box.itemCount);
    for (unsigned int i = 0; i < box.itemCount; i++)
    {
        HeaderCommon header = {0};
        myfread(f, &header, sizeof(header));
        printTab(tabCount + 1);
        header.size = ftol(header.size);
        printf("boxType=%.*s boxSize=%ld \n", 4, header.type, header.size);
        HeaderFlag flag = { 0 };
        myfread(f, &flag, sizeof(flag));
        int size = header.size - sizeof(header) - sizeof(flag);
        if (0 == size)
        {
            continue;
        }
        std::string str;
        str.resize(size);
        myfread(f, &str[0], str.size());
        printTab(tabCount + 2);
        printf("data=%s\n", str.c_str());
    }
}
void parsedinf(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}

//stbl
void parsestbl(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}

//edts
void parseedts(FILE* f, int realDataSize, int tabCount)
{
    parseFormat(f, realDataSize, tabCount);
}


//stsd
struct SampleDescriptionBox
{
    uint8_t version;             //
    uint8_t flags[3];           //
    uint32_t itemCount;
};


void parsestsd(FILE* f, int realDataSize, int tabCount)
{
    SampleDescriptionBox box = {0};
    myfread(f, &box, sizeof(box));
    box.itemCount = ftol(box.itemCount);
    for (unsigned int i = 0; i < box.itemCount; i++)
    {
        HeaderCommon header = { 0 };
        myfread(f, &header, sizeof(header));
        printTab(tabCount);
        printf("boxType=%.*s boxSize=%ld \n", 4, header.type, header.size);

    }
}

void parseFormat(FILE *f, int realDataSize, int tabCount)
{
    uint32_t boxSize = 0;
    int curReadCount = 0;
    while (curReadCount < realDataSize)
    {
        if (fread(&boxSize, 1, sizeof(boxSize), f) != sizeof(boxSize)) 
        {
            if (0 != feof(f))
            {
                break;
            }
            else 
            {
                assert(false);
                throw - 1;
            }
        }
        boxSize = ftol(boxSize);
        char boxType[5] = { 0 };
        if (fread(boxType, 1, 4, f) != 4)
        {
            assert(false);
            throw - 1;
        }
        uint64_t largeSize = 0;
        if (0 == boxSize)
        {
            printf("boxEnd\n");
            break;
        }
        else if (1 == boxSize)
        {
            if (fread(&largeSize, 1, sizeof(largeSize), f) != sizeof(largeSize))
            {
                assert(false);
                throw - 1;
            }
            largeSize = ftol(largeSize);
        }
        printTab(tabCount);
        uint64_t realBoxSize = largeSize != 0 ? largeSize : boxSize;
        uint64_t realHeaderSize = largeSize != 0 ? 16 : 8;
        uint64_t realDataSize = realBoxSize - realHeaderSize;
        curReadCount += (int)realBoxSize;
        printf("boxType=%s boxSize=%lld \n", boxType, realBoxSize);
        long long nextOffset = _ftelli64(f) + realDataSize;
        extern std::map<std::string, PARSEFUN> g_parseFun;
        auto iter = g_parseFun.find(boxType);
        if (iter != g_parseFun.end())
        {
            iter->second(f, (int)realDataSize, tabCount + 1);
        }
        else
        {
            
        }
        if (0 != _fseeki64(f, nextOffset, SEEK_SET))
        {
            assert(false);
            throw - 1;
        }
    }
    
}

void parsemp4()
{
    g_parseFun.insert(std::make_pair(std::string(), &parseFormat));
    g_parseFun.insert(std::make_pair(std::string("ftyp"), &parseftyp));
    g_parseFun.insert(std::make_pair(std::string("moov"), &parsemoov));
    g_parseFun.insert(std::make_pair(std::string("mvhd"), &parsemvhd));
    g_parseFun.insert(std::make_pair(std::string("trak"), &parsetrak));
    g_parseFun.insert(std::make_pair(std::string("tkhd"), &parsetkhd));
    g_parseFun.insert(std::make_pair(std::string("mdia"), &parsetmdia));
    g_parseFun.insert(std::make_pair(std::string("mdhd"), &parsemdhd));
    g_parseFun.insert(std::make_pair(std::string("hdlr"), &parsehdlr));
    g_parseFun.insert(std::make_pair(std::string("minf"), &parseminf));
    g_parseFun.insert(std::make_pair(std::string("vmhd"), &parsevmhd));
    g_parseFun.insert(std::make_pair(std::string("smhd"), &parsevsmhd));
    g_parseFun.insert(std::make_pair(std::string("dinf"), &parsedinf));
    g_parseFun.insert(std::make_pair(std::string("dref"), &parsedref));
    g_parseFun.insert(std::make_pair(std::string("stbl"), &parsestbl));
    g_parseFun.insert(std::make_pair(std::string("edts"), &parseedts));

    const char* fileName = "d:/test.mp4";
    FILE* f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    try {
        parseFormat(f, size, 0);
    }
    catch (int)
    {

    }

    fclose(f);
}
#define	__LITTLE_ENDIAN	1234
#define	__BIG_ENDIAN	4321

#define __BYTE_ORDER __LITTLE_ENDIAN

#pragma pack(1)
struct FLV_FILE_HEADER
{
    int8_t signature[3];//'F' 'L' 'V'
    uint8_t version;    //0x01
    //从低到高每bit为:是否显示视频标签,固定为0,是否显示音频标签,其次为0
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t videoFlag : 1;
    uint8_t flagReserved : 1;
    uint8_t audioFlag : 1;
    uint8_t flagReserved2 : 5;
#else
    uint8_t flagReserved2 : 5;
    uint8_t audioFlag : 1;
    uint8_t flagReserved : 1;
    uint8_t videoFlag : 1;
#endif
    uint32_t dataOffset;    //这个头的字节数
};

struct FLV_TAG
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t tagType : 5;    //0x08 音频TAG 0x09 视频TAG 0x12脚本数据
    uint8_t filter : 1;     //主要用文件内容加密处理,0不预处理,1预处理
    uint8_t reserved : 2;
#else
    uint32_t reserved : 2;
    uint32_t filter : 1;     //主要用文件内容加密处理,0不预处理,1预处理
    uint32_t tagType : 5;    //0x08 音频TAG 0x09 视频TAG 0x12脚本数据
    uint32_t dataSize : 24; //TAG的DATA部分大小
#endif
    uint8_t dataSize[3]; //TAG的DATA部分大小,24bit数值
    uint8_t timeStamp[3];//毫秒为单位展示时间,24bit数值
    uint8_t timeStampExtended;//针对时间戳的补充时间戳
    uint8_t streamID[3];//0
    //data
};

struct FLV_TAG_SCRIPT_HEADER
{
    uint8_t type;//0:number 1:boolean 2:string 3:object 5:null 6:undefined 7:reference 8:ecma array 9:object end marker 10:strict array 11:data 12:long string
    //data
};

struct FLV_TAG_AUDIO_HEADER
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t soundType : 1;  //0:Mono sound 1:Stereo Sound AAC是1
    uint8_t soundSize : 1;  //0:8位采样 1:16位采样
    uint8_t soundRate : 2;  //FLV_SOUND_RATE
    uint8_t soundFormat : 4;//FLV_SOUND_FORMAT
#else
    uint8_t soundFormat : 4;//FLV_SOUND_FORMAT
    uint8_t soundRate : 2;  //FLV_SOUND_RATE
    uint8_t soundSize : 1;
    uint8_t soundType : 1;
#endif
    uint8_t aacPacketType;//当音频是AAC类型时,占用这个字节,0:AACsequence header 1:aac raw数据
    //data
};

struct FLV_TAG_VIDEO_HEADER
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t codecID : 4;        //编码标识FLV_CODEC
    uint8_t frameType : 4;      //帧类型FLV_VIDEO_FRAME
    uint8_t packetType;         //H.264的包类型
    uint8_t compositonTime[3];  //编码使用B帧的时候,DTS和PTS不相等,CTS用于表示PTS和DTS之间的差值
#else
    uint8_t frameType : 4;
    uint8_t codecID : 4;
    uint8_t packetType;
    uint8_t compositonTime[3];
#endif
};
#pragma pack()
#define INIT_FLV_TYPE(id) \
    {id, #id}

#define FLV_SOUND_FORMAT_PCM 0      //线行PCM,大小端取决于平台
#define FLV_SOUND_FORMAT_ADPCM 1    //ADPCM音频格式
#define FLV_SOUND_FORMAT_MP3 2      //MP3
#define FLV_SOUND_FORMAT_PCM_LE 3    //PCM,小端
#define FLV_SOUND_FORMAT_NELLYMOSER16 4 //nellymoser 16hz mono
#define FLV_SOUND_FORMAT_NELLYMOSER8 5 //nellymoser 8hz mono
#define FLV_SOUND_FORMAT_NELLYMOSER 6   //nellymoser
#define FLV_SOUND_FORMAT_G711_ALAW 7    //G.711 A-law
#define FLV_SOUND_FORMAT_G711_MULAW 8   //G.711 mu-law
#define FLV_SOUND_FORMAT_RESERVED 9     //保留
#define FLV_SOUND_FORMAT_AAC 10         //AAC
#define FLV_SOUND_FORMAT_SPEEX 11       //Speex
#define FLV_SOUND_FORMAT_MP38 14        //mp3 8kHz
#define FLV_SOUND_FORMAT_DEVICE 15      //设备支持的声音

#define FLV_SOUND_RATE_55   0   //5.5kHz
#define FLV_SOUND_RATE_11   1   //11kHz
#define FLV_SOUND_RATE_22   2   //22kHz
#define FLV_SOUND_RATE_44   3   //44kHz


#define FLV_CODEC_SORENSON 2    //Sornson H.263,用的很少
#define FLV_CODEC_SCREEN_VIDEO 3//Screen Video,用的很少
#define FLV_CODEC_VP6   4   //On2 VP6,偶尔用
#define FLV_CODEC_VP6_ALPHA 5 //带Alpha通道On2 VP6,偶尔用
#define FLV_CODEC_SCREEN_VIDEO2 6 //Screen Video2,用的很少
#define FLV_CODEC_H264 7 //H.264

#define FLV_VIDEO_FRAME_H264_I 1 //关键帧,H.264使用,可以seek的帧
#define FLV_VIDEO_FRAME_H264_PB 2//P or B 帧,H.264
#define FLV_VIDEO_FRAME_H263 3//H.263
#define FLV_VIDEO_FRAME_GEN_KEY 4//生成关键帧,服务器端使用
#define FLV_VIDEO_FRAME_INFO    5 //视频信息/命令帧

#define FLV_VIDEO_PACKET_SEQUENCE_HEADER 0 //H.264 Sequence Header
#define FLV_VIDEO_PACKET_NALU 1 //NALU
#define FLV_VIDEO_PACKET_SEQUENCE_END 2 //H.264 Sequence的end

void parsetagvideo(FILE* f, int realDataSize, int tabCount)
{
    FLV_TAG_VIDEO_HEADER header = { 0 };
    printTab(tabCount);
    if (fread(&header, 1, sizeof(header), f) < sizeof(header))
    {
        assert(false);
        throw - 1;
    }
    std::string frame;
    std::pair<int, std::string> frames[] = {
        INIT_FLV_TYPE(FLV_VIDEO_FRAME_H264_I),
        INIT_FLV_TYPE(FLV_VIDEO_FRAME_H264_PB),
        INIT_FLV_TYPE(FLV_VIDEO_FRAME_H263),
        INIT_FLV_TYPE(FLV_VIDEO_FRAME_GEN_KEY),
        INIT_FLV_TYPE(FLV_VIDEO_FRAME_INFO),
    };
    for (auto& pair : frames)
    {
        if (pair.first == header.frameType)
        {
            frame = pair.second;
            break;
        }
    }
    std::string codec;
    std::pair<int, std::string> codecs[] = {
        INIT_FLV_TYPE(FLV_CODEC_SORENSON),
        INIT_FLV_TYPE(FLV_CODEC_SCREEN_VIDEO),
        INIT_FLV_TYPE(FLV_CODEC_VP6),
        INIT_FLV_TYPE(FLV_CODEC_VP6_ALPHA),
        INIT_FLV_TYPE(FLV_CODEC_SCREEN_VIDEO2),
        INIT_FLV_TYPE(FLV_CODEC_H264),
    };
    for (auto& pair : codecs)
    {
        if (pair.first == header.codecID)
        {
            codec = pair.second;
            break;
        }
    }
    std::string packetType;
    std::pair<int, std::string> packetTypes[] = {
        INIT_FLV_TYPE(FLV_VIDEO_PACKET_SEQUENCE_HEADER),
        INIT_FLV_TYPE(FLV_VIDEO_PACKET_NALU),
        INIT_FLV_TYPE(FLV_VIDEO_PACKET_SEQUENCE_END),
    };
    for (auto& pair : packetTypes)
    {
        if (pair.first == header.packetType)
        {
            packetType = pair.second;
            break;
        }
    }
    uint32_t CTS = flv24to32(header.compositonTime);
    printf("frame=%s codec=%s packettype=%s CTS=%u\n", frame.c_str(), codec.c_str(), packetType.c_str(), CTS);
}

void parsetagaudio(FILE* f, int realDataSize, int tabCount)
{
    FLV_TAG_AUDIO_HEADER header = { 0 };
    if (fread(&header, 1, sizeof(header), f) < sizeof(header))
    {
        assert(false);
        throw - 1;
    }
    printTab(tabCount);
    std::pair<int, std::string> soundFormats[] = {
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_PCM),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_ADPCM),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_MP3),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_PCM_LE),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_NELLYMOSER16),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_NELLYMOSER8),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_NELLYMOSER),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_G711_ALAW),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_G711_MULAW),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_RESERVED),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_AAC),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_SPEEX),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_MP38),
        INIT_FLV_TYPE(FLV_SOUND_FORMAT_DEVICE),
    };
    std::pair<int, std::string> soundRates[] = {
        INIT_FLV_TYPE(FLV_SOUND_RATE_55),
        INIT_FLV_TYPE(FLV_SOUND_RATE_11),
        INIT_FLV_TYPE(FLV_SOUND_RATE_22),
        INIT_FLV_TYPE(FLV_SOUND_RATE_44),
    };

    std::string format;
    for (auto& pair : soundFormats)
    {
        if (pair.first == header.soundFormat)
        {
            format = pair.second;
            break;
        }
    }
    std::string rate;
    for (auto& pair : soundRates)
    {
        if (pair.first == header.soundRate)
        {
            rate = pair.second;
            break;
        }
    }
    printTab(tabCount);
    std::string size = header.soundSize == 0 ? "8bit" : "16bit";
    std::string type = header.soundType == 0 ? "mono" : "stereo";
    std::string actType = header.aacPacketType == 0 ? "aac sequence" : "aac raw";
    printf("format=%s rate=%s size=%s type=%s aactype=%s\n", format.c_str(), rate.c_str(), size.c_str(), type.c_str(), actType.c_str());
}

#define FLV_TAG_AUDIO 0x08
#define FLV_TAG_VIDEO 0x09
#define FLV_TAG_SCRIPT_DATA 0x12

#define FLV_SCRIPT_NUMBER 0
#define FLV_SCRIPT_BOOLEAN 1
#define FLV_SCRIPT_STRING 2
#define FLV_SCRIPT_OBJECT 3
#define FLV_SCRIPT_NULL 5
#define FLV_SCRIPT_UNDEFINED 6
#define FLV_SCRIPT_REFERENCE 7
#define FLV_SCRIPT_ECMA_ARRAY 8
#define FLV_SCRIPT_OBJECT_END_MARKER 9
#define FLV_SCRIPT_STRICT_ARRAY 10
#define FLV_SCRIPT_DATE 11
#define FLV_SCRIPT_LONG_STRING 12


void parsetagscripdata(FILE* f, int realDataSize, int tabCount)
{
    FLV_TAG_SCRIPT_HEADER header = { 0 };
    if (fread(&header, 1, sizeof(header), f) < sizeof(header))
    {
        assert(false);
        throw -1;
    }
    printTab(tabCount);
    std::pair<uint8_t, std::string> scriptTypes[] = {
        INIT_FLV_TYPE(FLV_SCRIPT_NUMBER),
        INIT_FLV_TYPE(FLV_SCRIPT_BOOLEAN),
        INIT_FLV_TYPE(FLV_SCRIPT_STRING),
        INIT_FLV_TYPE(FLV_SCRIPT_OBJECT),
        INIT_FLV_TYPE(FLV_SCRIPT_NULL),
        INIT_FLV_TYPE(FLV_SCRIPT_UNDEFINED),
        INIT_FLV_TYPE(FLV_SCRIPT_REFERENCE),
        INIT_FLV_TYPE(FLV_SCRIPT_ECMA_ARRAY),
        INIT_FLV_TYPE(FLV_SCRIPT_OBJECT_END_MARKER),
        INIT_FLV_TYPE(FLV_SCRIPT_STRICT_ARRAY),
        INIT_FLV_TYPE(FLV_SCRIPT_DATE),
        INIT_FLV_TYPE(FLV_SCRIPT_LONG_STRING),
    };
    std::string type;
    for (auto& pair : scriptTypes)
    {
        if (pair.first == header.type)
        {
            type = pair.second;
            break;
        }
    }
    printf("scripttype=%s\n", type.c_str());
}

void parsetags(FILE* f, int realDataSize, int tabCount)
{
    uint32_t previewTagSize = 0;
    FLV_TAG tag = { 0 };
    while (true)
    {
        if (fread(&previewTagSize, 1, sizeof(previewTagSize), f) < sizeof(previewTagSize))
        {
            if (0 != feof(f))
            {
                break;
            }
            else
            {
                assert(false);
                throw - 1;
            }
        }
        realDataSize -= sizeof(previewTagSize);
        previewTagSize = ftol(previewTagSize);
        realDataSize -= previewTagSize;
        if (realDataSize <= 0)
        {
            break;
        }
        if (fread(&tag, 1, sizeof(tag), f) < sizeof(tag))
        {
            assert(false);
            throw - 1;
        }
        uint32_t dataSize = flv24to32(tag.dataSize);
        uint32_t timeStamp = flv24to32(tag.timeStamp);
        long long nextOffset = _ftelli64(f) + dataSize;
        switch (tag.tagType)
        {
        case FLV_TAG_AUDIO:
        {
            parsetagaudio(f, dataSize, tabCount + 1);
            break;
        }
        case FLV_TAG_VIDEO:
        {
            parsetagvideo(f, dataSize, tabCount + 1);
            break;
        }
        case FLV_TAG_SCRIPT_DATA:
        {
            parsetagscripdata(f, dataSize, tabCount + 1);
            break;
        }
        }
        if (0 != _fseeki64(f, nextOffset, SEEK_SET))
        {
            assert(false);
            throw - 1;
        }
    }
}

void parseflvformat(FILE* f, int realDataSize, int tabCount)
{
    FLV_FILE_HEADER fileHeader = { 0 };
    if (fread(&fileHeader, 1, sizeof(fileHeader), f) < sizeof(fileHeader))
    {
        assert(false);
        throw - 1;
    }
    fileHeader.dataOffset = ftol(fileHeader.dataOffset);

    if (0 != fseek(f, fileHeader.dataOffset, SEEK_SET))
    {
        throw - 1;
    }
    parsetags(f, realDataSize - fileHeader.dataOffset, tabCount);
}

void parseflv()
{
    const char* fileName = "E:\\test.flv";
    FILE* f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    try {
        parseflvformat(f, size, 0);
    }
    catch (int)
    {

    }

    fclose(f);
}

int main()
{
    parsemp4();
    parseflv();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

