//
// Created by chenyue on 2020/8/4.
//

#ifndef TESTCAMERA_AUDIORECORDLOGIC_H
#define TESTCAMERA_AUDIORECORDLOGIC_H
#include <stdint.h>

struct AudioRecordLogicData;
class AudioRecordLogic {
public:
    enum{
        NONE,
        WAV,
        MP3,
    };
public:
    AudioRecordLogic();
    ~AudioRecordLogic();

public:
    void setOutputFormat(int format);
    void setMp3BRate(int brate);
    void setInputStreamInfo(uint16_t numChannels, uint32_t sampleRate, uint16_t bitsPerSample);
    bool startRecord(const char *filePath);
    void stopRecord();
    size_t appendData(const void *data, size_t len);

private:
    AudioRecordLogicData *mData;
};


#endif //TESTCAMERA_AUDIORECORDLOGIC_H
