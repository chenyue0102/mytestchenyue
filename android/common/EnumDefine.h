//
// Created by chenyue on 2020/8/12.
//

#ifndef TESTFFMPEG_ENUMDEFINE_H
#define TESTFFMPEG_ENUMDEFINE_H

enum EPlayState{
    EPlayStateNone,
    EPlayStatePlaying,
    EPlayStatePause,
    EPlayStateStopped,
};

enum EAudioFormat {
	EAudioFormatNone,
	EAudioFormatS16LE,
};

enum EVideoFormat{
	EVideoFormatNone,
	EVideoFormatYUV420P,
};

#endif //TESTFFMPEG_ENUMDEFINE_H
