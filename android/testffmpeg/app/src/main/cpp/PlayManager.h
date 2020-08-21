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
class SDLAudioHelper;
typedef SDLAudioHelper PlayHelper;
#else
class OpenSLPlay;
typedef OpenSLPlay PlayHelper;
#endif

struct PlayManagerData;
class PlayManager {
public:
    PlayManager();
    ~PlayManager();

public:
    bool openFile(const char *filePath);
	bool setPlayState(uint32_t playState);
	bool seek(int64_t ms);
	bool close();

private:
	std::thread mReadThread;
	PlayManagerData *mData;
};


#endif //TESTFFMPEG_PLAYMANAGER_H
