#ifndef SimpleWAVHelper_h_
#define SimpleWAVHelper_h_
#include <stdint.h>
#include <assert.h>

struct wav_header_t
{
    char chunkID[4]; //"RIFF" = 0x46464952
    uint32_t chunkSize; //文件长度-8
    char format[4]; //"WAVE" = 0x45564157
    char subchunk1ID[4]; //"fmt " = 0x20746D66
    uint32_t subchunk1Size; //16 18 40[+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
    uint16_t audioFormat;//数据类型,"01 00"表示 PCM
    uint16_t numChannels;//通道数
    uint32_t sampleRate;//采样率，比如""表示44100采样率
    uint32_t byteRate;//码率： 采样率x位深度x通道数/8 比如双通道的44.1K 16位采样的码率为176400
    uint16_t blockAlign;//采样一次，占内存大小 ： 位深度x通道数/8
    uint16_t bitsPerSample;//采样深度

    //uint16_t cbSize;//Size of the extension (0 or 22)

    //uint16_t wValidBitsPerSample;//Number of valid bits
    //uint32_t dwChannelMask;//Speaker position mask
    //uint8_t SubFormat[16];//GUID including the data format code
};

//Chunks
struct chunk_t
{
    char ID[4]; //"data" = 0x61746164
    uint32_t size;  //Chunk data bytes
};
#define WAVE_FORMAT_PCM 0x0001
#define WAVE_FORMAT_IEEE_FLOAT 0x0003
#define WAVE_FORMAT_EXTENSIBLE 0xFFFE

inline void innerSkipHeader(FILE* f) {
    chunk_t tmpChunk = { 0 };
    do
    {
        if (sizeof(tmpChunk) != fread(&tmpChunk, 1, sizeof(tmpChunk), f)) {
            assert(false);
            break;
        }
        if (0 == strncmp(tmpChunk.ID, "data", 4)) {
            break;
        }
        if (0 != fseek(f, tmpChunk.size, SEEK_CUR)) {
            assert(false);
            break;
        }
    } while (0 != strncmp(tmpChunk.ID, "data", 4));
}
//读取s16个数wav信息
inline int getWavInfo(FILE* f, int* sampleRate, int *channels) {
    int ret = -1;

    do
    {
        wav_header_t wavHeader = { 0 };
        if (fread(&wavHeader, 1, sizeof(wavHeader), f) != sizeof(wavHeader)) {
            assert(false);
            break;
        }
        if (wavHeader.audioFormat != WAVE_FORMAT_PCM) {
            assert(false);
            break;
        }
        *sampleRate = wavHeader.sampleRate;
        *channels = wavHeader.numChannels;
        innerSkipHeader(f);
        ret = 0;
    } while (false);
    return ret;
}

inline int getWavHeaderSize() {
    return sizeof(wav_header_t) + sizeof(chunk_t);
}

inline int rewriteWavHeader(FILE* f, int sampleRate, int channels, int totalSampleByte) {
    fseek(f, 0, SEEK_SET);
    wav_header_t header = { 0 };
    int bytePerSample = sizeof(int16_t);
    memcpy(header.chunkID, "RIFF", 4);
    header.chunkSize = static_cast<int32_t>(getWavHeaderSize() + totalSampleByte - 8);
    memcpy(header.format, "WAVE", 4);
    memcpy(header.subchunk1ID, "fmt ", 4);
    header.subchunk1Size = 16;
    header.audioFormat = WAVE_FORMAT_PCM;
    header.numChannels = channels;
    header.sampleRate = sampleRate;
    header.byteRate = sampleRate * bytePerSample * channels;
    header.blockAlign = bytePerSample * channels;
    header.bitsPerSample = bytePerSample * CHAR_BIT;
    fwrite(&header, 1, sizeof(header), f);

    chunk_t chunk = { 0 };
    memcpy(chunk.ID, "data", 4);
    chunk.size = totalSampleByte;
    fwrite(&chunk, 1, sizeof(chunk), f);
    return 0;
}

#endif