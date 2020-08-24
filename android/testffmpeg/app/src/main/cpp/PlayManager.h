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

struct PlayManagerData;
class OpenGLPlay;
class PlayManager {
public:
    PlayManager();
    ~PlayManager();

public:
    bool openFile(const char *filePath);
	bool setPlayState(uint32_t playState);
	bool seek(int64_t ms);
	bool close();
	OpenGLPlay& getVideoPlay();

private:
	std::thread mReadThread;
	PlayManagerData *mData;
};


#endif //TESTFFMPEG_PLAYMANAGER_H
