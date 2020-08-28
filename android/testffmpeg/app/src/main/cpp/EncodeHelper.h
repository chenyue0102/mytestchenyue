//
// Created by chenyue on 2020/8/26.
//

#ifndef TESTFFMPEG_ENCODEHELPER_H
#define TESTFFMPEG_ENCODEHELPER_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <list>
extern "C"{
#include "libavformat/avformat.h"
};

class EncodeHelper {
public:
    struct StreamInfo{
		AVStream *stream = nullptr;
        AVCodecParameters *codecParameters = nullptr;
        //AVCodecContext *codecContext = nullptr;
		AVRational streamTimeBase;
		AVRational encoderTimeBase;
        std::list<AVFrame*> frames;
        int32_t sendFrameCount = 0;
        bool receivePacketEnd = false;
        uint32_t streamIndex = 0;
    };

    struct EncodeThreadInfo{
        std::mutex mtx;
        std::condition_variable cv;
        bool exit = false;
        bool running = false;
        std::vector<StreamInfo> streamInfo;
        AVFormatContext *formatContext = nullptr;
    };
public:
    EncodeHelper();
    ~EncodeHelper();

public:
    //按照stream index顺序依次填入AVCodecParameters
    bool addStreamInfo(AVCodecParameters *codecParameters, AVRational encoderTimeBase, AVRational streamTimeBase);
    bool open(const char *outputFile);
    //frame为null表示最后一个包
    bool addFrame(uint32_t streamIndex, AVFrame *frame);
    void close();

private:
    EncodeThreadInfo mEncodeThreadInfo;
    std::thread mEncodeThread;
};


#endif //TESTFFMPEG_ENCODEHELPER_H
