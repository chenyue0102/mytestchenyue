//
// Created by chenyue on 2020/8/25.
//

#ifndef TESTFFMPEG_TESTFFMPEG_H
#define TESTFFMPEG_FFMPEGTEST_H


namespace FFMPEGTest {
    void test_demux_mux(const char *inputfile, const char *outputfile);
    void test_decode_encode(const char *inputfile, const char *outputfile);
};


#endif //TESTFFMPEG_TESTFFMPEG_H
