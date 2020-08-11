//
// Created by chenyue on 2020/8/8.
//

#include "Demux.h"

Demux::Demux(): mMutex(), mCV(), mThread(), mFormatContext(nullptr) {

}

Demux::~Demux() {

}

void Demux::setFormatContext(AVFormatContext *formatContext) {
    std::lock_guard<std::mutex> lk(mMutex);

    mFormatContext = formatContext;
}

void Demux::demutexThread() {

}
