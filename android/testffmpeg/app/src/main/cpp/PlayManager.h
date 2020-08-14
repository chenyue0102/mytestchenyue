//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_PLAYMANAGER_H
#define TESTFFMPEG_PLAYMANAGER_H

#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>
extern "C"{
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
}


#ifdef _WIN32
class DirectSoundHelper;
typedef DirectSoundHelper PlayHelper;
#else
class OpenSLESHelper;
typedef OpenSLESHelper PlayHelper;
#endif

struct PlayManagerData;
class PlayManager {
public:
    PlayManager();
    ~PlayManager();

public:
    bool openFile(const char *filePath);
	bool setPlayState(uint32_t playState);

private:
	std::thread mReadThread;
	std::thread mLoopThread;
	PlayManagerData *mData;
};


#endif //TESTFFMPEG_PLAYMANAGER_H
