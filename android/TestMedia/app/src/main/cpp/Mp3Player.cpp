//
// Created by chenyue on 2020/7/18.
//

#include "Mp3Player.h"
#include <stdlib.h>
#include <memory>
extern "C"{
#include <android/log.h>
}
#define         MAX_U_32_NUM            0xFFFFFFFF
#if 1

struct PcmBuffer {
    void   *ch[2];           /* buffer for each channel */
    int     w;               /* sample width */
    int     n;               /* number samples allocated */
    int     u;               /* number samples used */
    int     skip_start;      /* number samples to ignore at the beginning */
    int     skip_end;        /* number samples to ignore at the end */
};

typedef struct PcmBuffer PcmBuffer;
typedef void SNDFILE;
/* global data for get_audio.c. */
typedef struct get_audio_global_data_struct {
    int     count_samples_carefully;
    int     pcmbitwidth;
    int     pcmswapbytes;
    int     pcm_is_unsigned_8bit;
    int     pcm_is_ieee_float;
    unsigned int num_samples_read;
    FILE   *music_in;
    SNDFILE *snd_file;
    hip_t   hip;
    PcmBuffer pcm32;
    PcmBuffer pcm16;
    size_t  in_id3v2_size;
    unsigned char* in_id3v2_tag;
} get_audio_global_data;

static get_audio_global_data global;

static size_t
lenOfId3v2Tag(unsigned char const* buf)
{
    unsigned int b0 = buf[0] & 127;
    unsigned int b1 = buf[1] & 127;
    unsigned int b2 = buf[2] & 127;
    unsigned int b3 = buf[3] & 127;
    return (((((b0 << 7) + b1) << 7) + b2) << 7) + b3;
}
typedef struct UiConfig
{
    int   silent;                   /* Verbosity */
    int   brhist;
    int   print_clipping_info;      /* print info whether waveform clips */
    float update_interval;          /* to use Frank's time status display */
} UiConfig;
UiConfig global_ui_config = {0,0,0,0};
static int
check_aid(const unsigned char *header)
{
    return 0 == memcmp(header, "AiD\1", 4);
}
void
frontend_msgf(const char *format, va_list ap)
{
    //(void) my_console_printing(Console_IO.Console_fp, format, ap);
}
void
frontend_errorf(const char *format, va_list ap)
{
    //(void) my_error_printing(Console_IO.Error_fp, format, ap);
}
void
frontend_debugf(const char *format, va_list ap)
{
    //(void) my_report_printing(Console_IO.Report_fp, format, ap);
}
typedef enum sound_file_format_e {
    sf_unknown,
    sf_raw,
    sf_wave,
    sf_aiff,
    sf_mp1,                  /* MPEG Layer 1, aka mpg */
    sf_mp2,                  /* MPEG Layer 2 */
    sf_mp3,                  /* MPEG Layer 3 */
    sf_mp123,                /* MPEG Layer 1,2 or 3; whatever .mp3, .mp2, .mp1 or .mpg contains */
    sf_ogg
} sound_file_format;
typedef struct ReaderConfig
{
    sound_file_format input_format;
    int   swapbytes;                /* force byte swapping   default=0 */
    int   swap_channel;             /* 0: no-op, 1: swaps input channels */
    int   input_samplerate;
    int   ignorewavlength;
} ReaderConfig;
ReaderConfig global_reader = { sf_unknown, 0, 0, 0, 0 };
static int
is_syncword_mp123(const void *const headerptr)
{
    const unsigned char *const p = (const unsigned char *const)headerptr;
    static const char abl2[16] = { 0, 7, 7, 7, 0, 7, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8 };

    if ((p[0] & 0xFF) != 0xFF)
        return 0;       /* first 8 bits must be '1' */
    if ((p[1] & 0xE0) != 0xE0)
        return 0;       /* next 3 bits are also */
    if ((p[1] & 0x18) == 0x08)
        return 0;       /* no MPEG-1, -2 or -2.5 */
    switch (p[1] & 0x06) {
        default:
        case 0x00:         /* illegal Layer */
            return 0;

        case 0x02:         /* Layer3 */
            if (global_reader.input_format != sf_mp3 && global_reader.input_format != sf_mp123) {
                return 0;
            }
            global_reader.input_format = sf_mp3;
            break;

        case 0x04:         /* Layer2 */
            if (global_reader.input_format != sf_mp2 && global_reader.input_format != sf_mp123) {
                return 0;
            }
            global_reader.input_format = sf_mp2;
            break;

        case 0x06:         /* Layer1 */
            if (global_reader.input_format != sf_mp1 && global_reader.input_format != sf_mp123) {
                return 0;
            }
            global_reader.input_format = sf_mp1;
            break;
    }
    if ((p[1] & 0x06) == 0x00)
        return 0;       /* no Layer I, II and III */
    if ((p[2] & 0xF0) == 0xF0)
        return 0;       /* bad bitrate */
    if ((p[2] & 0x0C) == 0x0C)
        return 0;       /* no sample frequency with (32,44.1,48)/(1,2,4)     */
    if ((p[1] & 0x18) == 0x18 && (p[1] & 0x06) == 0x04 && abl2[p[2] >> 4] & (1 << (p[3] >> 6)))
        return 0;
    if ((p[3] & 3) == 2)
        return 0;       /* reserved enphasis mode */
    return 1;
}

static  size_t
min_size_t(size_t a, size_t b)
{
    if (a < b) {
        return a;
    }
    return b;
}
static int
fskip(FILE * fp, long offset, int whence)
{
#ifndef PIPE_BUF
    char    buffer[4096];
#else
    char    buffer[PIPE_BUF];
#endif

/* S_ISFIFO macro is defined on newer Linuxes */
#ifndef S_ISFIFO
# ifdef _S_IFIFO
    /* _S_IFIFO is defined on Win32 and Cygwin */
#  define S_ISFIFO(m) (((m)&_S_IFIFO) == _S_IFIFO)
# endif
#endif

#ifdef S_ISFIFO
    /* fseek is known to fail on pipes with several C-Library implementations
       workaround: 1) test for pipe
       2) for pipes, only relatvie seeking is possible
       3)            and only in forward direction!
       else fallback to old code
     */
    {
        int const fd = fileno(fp);
        struct stat file_stat;

        if (fstat(fd, &file_stat) == 0) {
            if (S_ISFIFO(file_stat.st_mode)) {
                if (whence != SEEK_CUR || offset < 0) {
                    return -1;
                }
                while (offset > 0) {
                    size_t const bytes_to_skip = min_size_t(sizeof(buffer), offset);
                    size_t const read = fread(buffer, 1, bytes_to_skip, fp);
                    if (read < 1) {
                        return -1;
                    }
                    assert( read <= LONG_MAX );
                    offset -= (long) read;
                }
                return 0;
            }
        }
    }
#endif
    if (0 == fseek(fp, offset, whence)) {
        return 0;
    }

    if (whence != SEEK_CUR || offset < 0) {
        if (global_ui_config.silent < 10) {
//            error_printf
//                    ("fskip problem: Mostly the return status of functions is not evaluate so it is more secure to polute <stderr>.\n");
        }
        return -1;
    }

    while (offset > 0) {
        size_t const bytes_to_skip = min_size_t(sizeof(buffer), offset);
        size_t const read = fread(buffer, 1, bytes_to_skip, fp);
        if (read < 1) {
            return -1;
        }
        assert( read <= LONG_MAX );
        offset -= (long) read;
    }

    return 0;
}
int
lame_decode_initfile(FILE * fd, mp3data_struct * mp3data, int *enc_delay, int *enc_padding)
{
    /*  VBRTAGDATA pTagData; */
    /* int xing_header,len2,num_frames; */
    unsigned char buf[100];
    int     ret;
    size_t  len;
    int     aid_header;
    short int pcm_l[1152], pcm_r[1152];
    int     freeformat = 0;

    memset(mp3data, 0, sizeof(mp3data_struct));
    if (global.hip) {
        hip_decode_exit(global.hip);
    }
    global.hip = hip_decode_init();
    hip_set_msgf(global.hip, global_ui_config.silent < 10 ? &frontend_msgf : 0);
    hip_set_errorf(global.hip, global_ui_config.silent < 10 ? &frontend_errorf : 0);
    hip_set_debugf(global.hip, &frontend_debugf);

    len = 4;
    if (fread(buf, 1, len, fd) != len)
        return -1;      /* failed */
    while (buf[0] == 'I' && buf[1] == 'D' && buf[2] == '3') {
        len = 6;
        if (fread(&buf[4], 1, len, fd) != len)
            return -1;  /* failed */
        len = lenOfId3v2Tag(&buf[6]);
        if (global.in_id3v2_size < 1) {
            global.in_id3v2_size = 10 + len;
            global.in_id3v2_tag = (unsigned char*)malloc(global.in_id3v2_size);
            if (global.in_id3v2_tag) {
                memcpy(global.in_id3v2_tag, buf, 10);
                if (fread(&global.in_id3v2_tag[10], 1, len, fd) != len)
                    return -1;  /* failed */
                len = 0; /* copied, nothing to skip */
            }
            else {
                global.in_id3v2_size = 0;
            }
        }
        assert( len <= LONG_MAX );
        fskip(fd, (long) len, SEEK_CUR);
        len = 4;
        if (fread(&buf, 1, len, fd) != len)
            return -1;  /* failed */
    }
    aid_header = check_aid(buf);
    if (aid_header) {
        if (fread(&buf, 1, 2, fd) != 2)
            return -1;  /* failed */
        aid_header = (unsigned char) buf[0] + 256 * (unsigned char) buf[1];
        if (global_ui_config.silent < 9) {
            //console_printf("Album ID found.  length=%i \n", aid_header);
        }
        /* skip rest of AID, except for 6 bytes we have already read */
        fskip(fd, aid_header - 6, SEEK_CUR);

        /* read 4 more bytes to set up buffer for MP3 header check */
        if (fread(&buf, 1, len, fd) != len)
            return -1;  /* failed */
    }
    len = 4;
    while (!is_syncword_mp123(buf)) {
        unsigned int i;
        for (i = 0; i < len - 1; i++)
            buf[i] = buf[i + 1];
        if (fread(buf + len - 1, 1, 1, fd) != 1)
            return -1;  /* failed */
    }

    if ((buf[2] & 0xf0) == 0) {
        if (global_ui_config.silent < 9) {
            //console_printf("Input file is freeformat.\n");
        }
        freeformat = 1;
    }
    /* now parse the current buffer looking for MP3 headers.    */
    /* (as of 11/00: mpglib modified so that for the first frame where  */
    /* headers are parsed, no data will be decoded.   */
    /* However, for freeformat, we need to decode an entire frame, */
    /* so mp3data->bitrate will be 0 until we have decoded the first */
    /* frame.  Cannot decode first frame here because we are not */
    /* yet prepared to handle the output. */
    ret = hip_decode1_headersB(global.hip, buf, len, pcm_l, pcm_r, mp3data, enc_delay, enc_padding);
    if (-1 == ret)
        return -1;

    /* repeat until we decode a valid mp3 header.  */
    while (!mp3data->header_parsed) {
        len = fread(buf, 1, sizeof(buf), fd);
        if (len != sizeof(buf))
            return -1;
        ret =
                hip_decode1_headersB(global.hip, buf, len, pcm_l, pcm_r, mp3data, enc_delay,
                                     enc_padding);
        if (-1 == ret)
            return -1;
    }

    if (mp3data->bitrate == 0 && !freeformat) {
        if (global_ui_config.silent < 10) {
            //error_printf("fail to sync...\n");
        }
        return lame_decode_initfile(fd, mp3data, enc_delay, enc_padding);
    }

    if (mp3data->totalframes > 0) {
        /* mpglib found a Xing VBR header and computed nsamp & totalframes */
    }
    else {
        /* set as unknown.  Later, we will take a guess based on file size
         * ant bitrate */
        mp3data->nsamp = MAX_U_32_NUM;
    }


    /*
       report_printf("ret = %i NEED_MORE=%i \n",ret,MP3_NEED_MORE);
       report_printf("stereo = %i \n",mp.fr.stereo);
       report_printf("samp = %i  \n",freqs[mp.fr.sampling_frequency]);
       report_printf("framesize = %i  \n",framesize);
       report_printf("bitrate = %i  \n",mp3data->bitrate);
       report_printf("num frames = %ui  \n",num_frames);
       report_printf("num samp = %ui  \n",mp3data->nsamp);
       report_printf("mode     = %i  \n",mp.fr.mode);
     */

    return 0;
}

#endif
#define INBUFSIZE 4096
#define MP3BUFSIZE (int) (1.25 * INBUFSIZE) + 7200//官方推荐大小，类型为int
Mp3Player::Mp3Player(): mFile(NULL), mHip(NULL), mBuffer(NULL) {
    mHip = hip_decode_init();
    mBuffer = (unsigned char*)malloc(MP3BUFSIZE);
}

Mp3Player::~Mp3Player() {
    hip_decode_exit(mHip);
    mHip = NULL;
    free(mBuffer);
}

/*
For lame_decode_fromfile:  return code
  -1     error
   n     number of samples output.  either 576 or 1152 depending on MP3 file.


For lame_decode1_headers():  return code
  -1     error
   0     ok, but need more data before outputing any samples
   n     number of samples output.  either 576 or 1152 depending on MP3 file.
*/
static int
lame_decode_fromfile(FILE * fd, short pcm_l[], short pcm_r[], mp3data_struct * mp3data)
{
    int     ret = 0;
    size_t  len = 0;
    unsigned char buf[1024];

    /* first see if we still have data buffered in the decoder: */
    ret = hip_decode1_headers(global.hip, buf, len, pcm_l, pcm_r, mp3data);
    if (ret != 0)
        return ret;


    /* read until we get a valid output frame */
    for (;;) {
        len = fread(buf, 1, 1024, fd);
        if (len == 0) {
            /* we are done reading the file, but check for buffered data */
            ret = hip_decode1_headers(global.hip, buf, len, pcm_l, pcm_r, mp3data);
            if (ret <= 0) {
                return -1; /* done with file */
            }
            break;
        }

        ret = hip_decode1_headers(global.hip, buf, len, pcm_l, pcm_r, mp3data);
        if (ret == -1) {
            return -1;
        }
        if (ret > 0)
            break;
    }
    return ret;
}

void Mp3Player::openFile(const char *filePath) {
    mFile = fopen(filePath, "rb");
    if (NULL != mFile){
        __android_log_print(ANDROID_LOG_INFO, "tag", "Mp3Player::openFile success");
        mp3data_struct mp3str;
        int     enc_delay = 0, enc_padding = 0;
        global_reader.input_format = sf_mp3;
        if (0 == lame_decode_initfile(mFile, &mp3str, &enc_delay, &enc_padding)){
            __android_log_print(ANDROID_LOG_INFO, "tag", "Mp3Player::openFile samplerate %d stereo %d", mp3str.samplerate, mp3str.stereo);
        }
        short int mpg123pcm[2][1152];
        int readCount = 0;
        FILE *fout = fopen("/storage/emulated/0/out.pcm", "wb");
        while ((readCount = lame_decode_fromfile(mFile, mpg123pcm[0], mpg123pcm[1], &mp3str)) > 0){
            for (int i = 0; i < readCount; i++){
                fwrite(&mpg123pcm[0][i], 1, 2, fout);
                fwrite(&mpg123pcm[1][i], 1, 2, fout);
            }
            __android_log_print(ANDROID_LOG_INFO, "tag", "Mp3Player::openFile lame_decode_fromfile %d", readCount);
        }
        fclose(fout);
        __android_log_print(ANDROID_LOG_INFO, "tag", "Mp3Player::openFile lame_decode_fromfile finish %d", readCount);
    }else{
        __android_log_print(ANDROID_LOG_INFO, "tag", "Mp3Player::openFile failed");
    }
}
