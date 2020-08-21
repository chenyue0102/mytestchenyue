#include <jni.h>
#include <string>
#include <assert.h>
#include <mutex>
#include <condition_variable>
#include <android/log.h>
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/error.h"
}

#include "TaskPool.h"
#include "Single.h"
#include "MacroDefine.h"
#include "Log.h"
#include "OpenSLESHelper.h"
#include "ObjectPool.h"
#include "PlayManager.h"

JavaVM *g_JavaVM = 0;
TaskPool g_TaskPool;
OpenSLESHelper g_OpenSLESHelper;

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved){
    g_JavaVM = vm;
    __android_log_write(ANDROID_LOG_DEBUG, "JNI", "JNI_OnLoad");
    g_TaskPool.open(10);
    return JNI_VERSION_1_4;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_test_testffmpeg_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_test_testffmpeg_MainActivity_init(JNIEnv *env, jobject thiz) {
    av_register_all();
    int ret = avformat_network_init();
    assert(0 == ret);
}

std::string g_filePath;

extern void LogAvError(int err);

int callback(void* param){

}
AVFormatContext *g_formatContext = nullptr;
AVCodecContext *g_vcc = nullptr;
AVCodecContext *g_acc = nullptr;

uint64_t getAudioPosition(){
    return 0;
}

uint64_t pts2ms(uint64_t pts){
    return pts * 1000 / AV_TIME_BASE;
}

void receiveVideoFrame(AVCodecContext *cc){
    AVFrame *frame = av_frame_alloc();
    int ret = 0;
    for (;;){
        ret = avcodec_receive_frame(cc, frame);
        if (AVERROR_EOF == ret){
            break;
        }
        else if (AVERROR(EAGAIN) == ret){
            break;
        }
        else{
            break;
        }
        if (pts2ms(frame->pts) < getAudioPosition()){
            av_frame_unref(frame);
            continue;
        }

        av_frame_unref(frame);
    }
    av_frame_unref(frame);
    av_frame_free(&frame);
}

std::condition_variable g_cv;
std::mutex g_mutex;
std::list<AVPacket*> g_packets;


void readFrame(int videoStream, int audioStream, AVCodecContext *vcc, AVCodecContext *acc){
    int ret = 0;
    for (;;){
        AVPacket *pkt = av_packet_alloc();
        ret = av_read_frame(g_formatContext, pkt);
        if (0 != ret){
            av_packet_free(&pkt);
            break;
        }
        AVCodecContext *cc = nullptr;
        if (pkt->stream_index == videoStream){
            cc = vcc;
        }else if (pkt->stream_index == audioStream){
            cc = acc;
        }else{
            //other
        }
        if (nullptr == cc){
            av_packet_unref(pkt);
            av_packet_free(&pkt);
            continue;
        }else{

            avcodec_send_packet(cc, pkt);
            av_packet_unref(pkt);
        }
    }


}

void openFile(){
    //g_formatContext = avformat_alloc_context();
//    AVIOInterruptCB interruptCb = {&callback, nullptr};
//    g_formatContext->interrupt_callback = interruptCb;
    int ret = avformat_open_input(&g_formatContext, g_filePath.c_str(), nullptr, nullptr);
    LogAvError(ret);
    ret = avformat_find_stream_info(g_formatContext, nullptr);
    LogAvError(ret);
    int videoStream = av_find_best_stream(g_formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    int audioStream = av_find_best_stream(g_formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);

    AVCodec *vcodec = avcodec_find_decoder(g_formatContext->streams[videoStream]->codecpar->codec_id);
    AVCodec *acodec = avcodec_find_decoder(g_formatContext->streams[audioStream]->codecpar->codec_id);

    g_vcc = avcodec_alloc_context3(vcodec);
    avcodec_parameters_to_context(g_vcc, g_formatContext->streams[videoStream]->codecpar);
    ret = avcodec_open2(g_vcc, nullptr, nullptr);
    LogAvError(ret);

    g_acc = avcodec_alloc_context3(acodec);
    avcodec_parameters_to_context(g_acc, g_formatContext->streams[audioStream]->codecpar);
    ret = avcodec_open2(g_acc, nullptr, nullptr);
    LogAvError(ret);

    g_TaskPool.addTask([videoStream, audioStream, vcodec, acodec](){readFrame(videoStream, audioStream, g_vcc, g_acc);});
}

void clean(){
    avcodec_close(g_vcc);
    avcodec_free_context(&g_vcc);

    avcodec_close(g_acc);
    avcodec_free_context(&g_acc);

    avformat_free_context(g_formatContext);
    g_formatContext = nullptr;
}
void bufferQueueCallback(
        SLAndroidSimpleBufferQueueItf caller,
        void *pContext
){

}
void createPlayer(){
    bool b = g_OpenSLESHelper.createEngine();
    b = g_OpenSLESHelper.createOutputMix();
    SLDataLocator_AndroidSimpleBufferQueue bufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            2,
            SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN,
    };
    SLDataSource slDataSource = {&bufferQueue, &pcm};
    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, g_OpenSLESHelper.getOutputMixObject()};
    SLDataSink slDataSink = {&outputMix, nullptr};
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    b = g_OpenSLESHelper.createPlayer(slDataSource, slDataSink, 3, ids, req);
    SLAndroidSimpleBufferQueueItf slBufferQueue = g_OpenSLESHelper.getPlayBufferQueue();
    g_OpenSLESHelper.registerPlayBufferQueueCallback(&bufferQueueCallback, nullptr);
    char szBuffer[] = "12345678";
    (*slBufferQueue)->Enqueue(slBufferQueue, szBuffer, 8);
    SLAndroidSimpleBufferQueueState state = {0};
    (*slBufferQueue)->GetState(slBufferQueue, &state);
    SC(Log).e("%d %d", state.count, state.index);
}

PlayManager g_PlayManager;
void openFile2(){
    g_PlayManager.openFile(g_filePath.c_str());
}
static bool g_init = false;
extern "C"
JNIEXPORT void JNICALL
Java_com_test_testffmpeg_MainActivity_openFile(JNIEnv *env, jobject thiz, jstring file_path) {
    if (!g_init){
        g_init = true;
        avcodec_register_all();
        avformat_network_init();
    }
    jboolean iscopy = 0;
    const char *str = env->GetStringUTFChars(file_path, &iscopy);
    if (nullptr != str) {
        g_filePath = str;
        FILE *f = fopen(str, "rb");
        fclose(f);
        env->ReleaseStringUTFChars(file_path, str);
        g_TaskPool.addTask(&openFile2);
    }
    //createPlayer();
}extern "C"
JNIEXPORT void JNICALL
Java_com_test_testffmpeg_MainActivity_closeFile(JNIEnv *env, jobject thiz) {
    clean();
}