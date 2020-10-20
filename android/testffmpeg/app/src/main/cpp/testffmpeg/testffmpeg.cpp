// testffmpeg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <assert.h>
#include <Windows.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>
#include "PlayManager.h"
#include "DirectSoundHelper.h"
#include "EnumDefine.h"
#include "RingQueue.h"
#include "SDL.h"
#include "SDLAudioHelper.h"
#include "OpenGLPlay.h"
#include "FFMPEGTest.h"
#include "BitBuffer.h"
#include "freeverb/myexport.h"

#define BUFFER_UPDATE_SIZE (1024*4)
struct wav_header_t
{
	char chunkID[4]; //"RIFF" = 0x46464952
	uint32_t chunkSize; //文件长度-8
	char format[4]; //"WAVE" = 0x45564157
	char subchunk1ID[4]; //"fmt " = 0x20746D66
	uint32_t subchunk1Size; //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
	uint16_t audioFormat;//数据类型,"01 00"表示 PCM
	uint16_t numChannels;//通道数
	uint32_t sampleRate;//采样率，比如""表示44100采样率
	uint32_t byteRate;//码率： 采样率x位深度x通道数/8 比如双通道的44.1K 16位采样的码率为176400
	uint16_t blockAlign;//采样一次，占内存大小 ： 位深度x通道数/8
	uint16_t bitsPerSample;//采样深度
};

//Chunks
struct chunk_t
{
	char ID[4]; //"data" = 0x61746164
	unsigned long size;  //Chunk data bytes
};
PlayManager *g_playManager = 0;

void testdraw() {
	g_playManager->getVideoPlay().draw();
}

void myIdle() {
	testdraw();
	std::this_thread::sleep_for(std::chrono::microseconds(1));
}
#include <bitset>
//#define CACHED_BITSTREAM_READER
#define BITSTREAM_READER_LE
typedef struct GetBitContext {
	const uint8_t* buffer, * buffer_end;
#if CACHED_BITSTREAM_READER
	uint64_t cache;
	unsigned bits_left;
#endif
	int index;
	int size_in_bits;
	int size_in_bits_plus8;
} GetBitContext;
#define UNCHECKED_BITSTREAM_READER 1
static inline unsigned int get_bits1(GetBitContext* s)
{
#if CACHED_BITSTREAM_READER
	if (!s->bits_left)
#ifdef BITSTREAM_READER_LE
		refill_64(s, 1);
#else
		refill_64(s, 0);
#endif

#ifdef BITSTREAM_READER_LE
	return get_val(s, 1, 1);
#else
	return get_val(s, 1, 0);
#endif
#else
	unsigned int index = s->index;
	uint8_t result = s->buffer[index >> 3];
#ifdef BITSTREAM_READER_LE
	result >>= index & 7;
	result &= 1;
#else
	result <<= index & 7;
	result >>= 8 - 1;
#endif
#if !UNCHECKED_BITSTREAM_READER
	if (s->index < s->size_in_bits_plus8)
#endif
		index++;
	s->index = index;

	return result;
#endif
}
static inline int init_get_bits_xe(GetBitContext* s, const uint8_t* buffer,
	int bit_size, int is_le)
{
	int buffer_size;
	int ret = 0;

	if (bit_size >= INT_MAX - FFMAX(7, AV_INPUT_BUFFER_PADDING_SIZE * 8) || bit_size < 0 || !buffer) {
		bit_size = 0;
		buffer = NULL;
		ret = AVERROR_INVALIDDATA;
	}

	buffer_size = (bit_size + 7) >> 3;

	s->buffer = buffer;
	s->size_in_bits = bit_size;
	s->size_in_bits_plus8 = bit_size + 8;
	s->buffer_end = buffer + buffer_size;
	s->index = 0;

#if CACHED_BITSTREAM_READER
	s->cache = 0;
	s->bits_left = 0;
	refill_64(s, is_le);
#endif

	return ret;
}
static inline int init_get_bits(GetBitContext* s, const uint8_t* buffer,
	int bit_size)
{
#ifdef BITSTREAM_READER_LE
	return init_get_bits_xe(s, buffer, bit_size, 1);
#else
	return init_get_bits_xe(s, buffer, bit_size, 0);
#endif
}

static inline int init_get_bits8(GetBitContext* s, const uint8_t* buffer,
	int byte_size)
{
	if (byte_size > INT_MAX / 8 || byte_size < 0)
		byte_size = -1;
	return init_get_bits(s, buffer, byte_size * 8);
}

uint8_t* ff_nal_unit_extract_rbsp(const uint8_t* src, uint32_t src_len,
	uint32_t* dst_len, int header_len)
{
	uint8_t* dst;
	uint32_t i, len;

	dst = (uint8_t*)malloc(src_len + AV_INPUT_BUFFER_PADDING_SIZE);
	if (!dst)
		return NULL;

	/* NAL unit header */
	i = len = 0;
	while (i < header_len && i < src_len)
		dst[len++] = src[i++];

	while (i + 2 < src_len)
		if (!src[i] && !src[i + 1] && src[i + 2] == 3) {
			dst[len++] = src[i++];
			dst[len++] = src[i++];
			i++; // remove emulation_prevention_three_byte
		}
		else
			dst[len++] = src[i++];

	while (i < src_len)
		dst[len++] = src[i++];

	memset(dst + len, 0, AV_INPUT_BUFFER_PADDING_SIZE);

	*dst_len = len;
	return dst;
}
#define OPEN_READER_NOSIZE(name, gb)            \
    unsigned int name ## _index = (gb)->index;  \
    unsigned int av_unused name ## _cache

#   define AV_RL32(x)                                \
    (((uint32_t)((const uint8_t*)(x))[3] << 24) |    \
               (((const uint8_t*)(x))[2] << 16) |    \
               (((const uint8_t*)(x))[1] <<  8) |    \
                ((const uint8_t*)(x))[0])
#define OPEN_READER(name, gb) OPEN_READER_NOSIZE(name, gb)
# define UPDATE_CACHE_LE(name, gb) name ## _cache = \
      AV_RL32((gb)->buffer + (name ## _index >> 3)) >> (name ## _index & 7)
# define UPDATE_CACHE(name, gb) UPDATE_CACHE_LE(name, gb)

static inline av_const unsigned zero_extend(unsigned val, unsigned bits)
{
	return (val << ((8 * sizeof(int)) - bits)) >> ((8 * sizeof(int)) - bits);
}
#define SHOW_UBITS_LE(name, gb, num) zero_extend(name ## _cache, num)
#   define SHOW_UBITS(name, gb, num) SHOW_UBITS_LE(name, gb, num)
#   define SKIP_COUNTER(name, gb, num) name ## _index += (num)
#define LAST_SKIP_BITS(name, gb, num) SKIP_COUNTER(name, gb, num)
#define CLOSE_READER(name, gb) (gb)->index = name ## _index
static inline unsigned int get_bits(GetBitContext* s, int n)
{
	register unsigned int tmp;
#if CACHED_BITSTREAM_READER

	av_assert2(n > 0 && n <= 32);
	if (n > s->bits_left) {
#ifdef BITSTREAM_READER_LE
		refill_32(s, 1);
#else
		refill_32(s, 0);
#endif
		if (s->bits_left < 32)
			s->bits_left = n;
	}

#ifdef BITSTREAM_READER_LE
	tmp = get_val(s, n, 1);
#else
	tmp = get_val(s, n, 0);
#endif
#else
	OPEN_READER(re, s);
	//av_assert2(n > 0 && n <= 25);
	UPDATE_CACHE(re, s);
	tmp = SHOW_UBITS(re, s, n);
	LAST_SKIP_BITS(re, s, n);
	CLOSE_READER(re, s);
#endif
	//av_assert2(tmp < UINT64_C(1) << n);
	return tmp;
}
static inline void skip_bits(GetBitContext* s, int n)
{
#if CACHED_BITSTREAM_READER
	if (n < s->bits_left)
		skip_remaining(s, n);
	else {
		n -= s->bits_left;
		s->cache = 0;
		s->bits_left = 0;

		if (n >= 64) {
			unsigned skip = (n / 8) * 8;

			n -= skip;
			s->index += skip;
		}
#ifdef BITSTREAM_READER_LE
		refill_64(s, 1);
#else
		refill_64(s, 0);
#endif
		if (n)
			skip_remaining(s, n);
	}
#else
	OPEN_READER(re, s);
	LAST_SKIP_BITS(re, s, n);
	CLOSE_READER(re, s);
#endif
}
static av_always_inline int get_bitsz(GetBitContext* s, int n)
{
	return n ? get_bits(s, n) : 0;
}
static inline int get_ue_golomb(GetBitContext* gb) {
	int i;
	for (i = 0; i < 32 && !get_bits1(gb); i++)
		;
	return get_bitsz(gb, i) + (1 << i) - 1;
}
static inline void skip_bits1(GetBitContext* s)
{
	skip_bits(s, 1);
}
static inline int get_se_golomb(GetBitContext* gb) {
	int v = get_ue_golomb(gb) + 1;
	int sign = -(v & 1);
	return ((v >> 1) ^ sign) - sign;
}
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))
void ff_avc_decode_sps(const uint8_t* buf, int buf_size)
{
	int i, j, ret, rbsp_size, aspect_ratio_idc, pic_order_cnt_type;
	int num_ref_frames_in_pic_order_cnt_cycle;
	int delta_scale, lastScale = 8, nextScale = 8;
	int sizeOfScalingList;
	GetBitContext gb;
	uint8_t* rbsp_buf;

	rbsp_buf = ff_nal_unit_extract_rbsp(buf, buf_size, (uint32_t*)&rbsp_size, 0);
	if (!rbsp_buf)
		return;

	ret = init_get_bits8(&gb, rbsp_buf, rbsp_size);
	if (ret < 0)
		return;

	
	uint8_t nal_unit_type = get_bits(&gb, 5);
	uint8_t nal_ref_idc = get_bits(&gb, 2);
	uint8_t forbidden_zero_bit = get_bits1(&gb);

	uint8_t profile_idc = get_bits(&gb, 8);
	uint8_t constraint_set_flags = 0;
	constraint_set_flags |= get_bits1(&gb) << 0; // constraint_set0_flag
	constraint_set_flags |= get_bits1(&gb) << 1; // constraint_set1_flag
	constraint_set_flags |= get_bits1(&gb) << 2; // constraint_set2_flag
	constraint_set_flags |= get_bits1(&gb) << 3; // constraint_set3_flag
	constraint_set_flags |= get_bits1(&gb) << 4; // constraint_set4_flag
	constraint_set_flags |= get_bits1(&gb) << 5; // constraint_set5_flag
	skip_bits(&gb, 2);							// reserved_zero_2bits
	uint8_t level_idc = get_bits(&gb, 8);
	int id = get_ue_golomb(&gb);

	if (profile_idc == 100 || profile_idc == 110 ||
		profile_idc == 122 || profile_idc == 244 || profile_idc == 44 ||
		profile_idc == 83 || profile_idc == 86 || profile_idc == 118 ||
		profile_idc == 128 || profile_idc == 138 || profile_idc == 139 ||
		profile_idc == 134) {
		int chroma_format_idc = get_ue_golomb(&gb); // chroma_format_idc
		if (chroma_format_idc == 3) {
			skip_bits1(&gb); // separate_colour_plane_flag
		}
		int bit_depth_luma = get_ue_golomb(&gb) + 8;
		int bit_depth_chroma = get_ue_golomb(&gb) + 8;
		skip_bits1(&gb); // qpprime_y_zero_transform_bypass_flag
		if (get_bits1(&gb)) { // seq_scaling_matrix_present_flag
			for (i = 0; i < ((chroma_format_idc != 3) ? 8 : 12); i++) {
				if (!get_bits1(&gb)) // seq_scaling_list_present_flag
					continue;
				lastScale = 8;
				nextScale = 8;
				sizeOfScalingList = i < 6 ? 16 : 64;
				for (j = 0; j < sizeOfScalingList; j++) {
					if (nextScale != 0) {
						delta_scale = get_se_golomb(&gb);
						nextScale = (lastScale + delta_scale) & 0xff;
					}
					lastScale = nextScale == 0 ? lastScale : nextScale;
				}
			}
		}
	}
	else {
		/*chroma_format_idc = 1;
		bit_depth_luma = 8;
		bit_depth_chroma = 8;*/
	}

	int log2_max_frame_num_minus4 = get_ue_golomb(&gb); // log2_max_frame_num_minus4
	pic_order_cnt_type = get_ue_golomb(&gb);

	if (pic_order_cnt_type == 0) {
		get_ue_golomb(&gb); // log2_max_pic_order_cnt_lsb_minus4
	}
	else if (pic_order_cnt_type == 1) {
		skip_bits1(&gb);    // delta_pic_order_always_zero
		get_se_golomb(&gb); // offset_for_non_ref_pic
		get_se_golomb(&gb); // offset_for_top_to_bottom_field
		num_ref_frames_in_pic_order_cnt_cycle = get_ue_golomb(&gb);
		for (i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++)
			get_se_golomb(&gb); // offset_for_ref_frame
	}

	int max_num_ref_frames = get_ue_golomb(&gb); // max_num_ref_frames
	skip_bits1(&gb); // gaps_in_frame_num_value_allowed_flag
	int pic_width_in_mbs_minus1 = get_ue_golomb(&gb); // pic_width_in_mbs_minus1
	int pic_height_in_map_units_minus1 = get_ue_golomb(&gb); // pic_height_in_map_units_minus1

	uint8_t frame_mbs_only_flag = get_bits1(&gb);
	if (!frame_mbs_only_flag)
		skip_bits1(&gb); // mb_adaptive_frame_field_flag

	skip_bits1(&gb); // direct_8x8_inference_flag

	if (get_bits1(&gb)) { // frame_cropping_flag
		int frame_crop_left_offset = get_ue_golomb(&gb); // frame_crop_left_offset
		int frame_crop_right_offset = get_ue_golomb(&gb); // frame_crop_right_offset
		int frame_crop_top_offset = get_ue_golomb(&gb); // frame_crop_top_offset
		int frame_crop_bottom_offset = get_ue_golomb(&gb); // frame_crop_bottom_offset
	}

	if (get_bits1(&gb)) { // vui_parameters_present_flag
		if (get_bits1(&gb)) { // aspect_ratio_info_present_flag
			aspect_ratio_idc = get_bits(&gb, 8);
			if (aspect_ratio_idc == 0xff) {
				uint16_t num = get_bits(&gb, 16);
				uint16_t den = get_bits(&gb, 16);
			}
			/*else if (aspect_ratio_idc < FF_ARRAY_ELEMS(avc_sample_aspect_ratio)) {
				sar = avc_sample_aspect_ratio[aspect_ratio_idc];
			}*/
		}
	}
	uint8_t numOfPictureParameterSets = get_bits(&gb, 8);
	uint16_t pictureParameterSetLength = get_bits(&gb, 16);
	return;
	/*if (!sar.den) {
		sar.num = 1;
		sar.den = 1;
	}*/

//end:
//	av_free(rbsp_buf);
//	return sps;
}
uint8_t data[] = {
	0x01, 0x64, 0x00, 0x28,
		0xff,
		0xe1,
		0x00, 0x1b,
		0x67,	0x64, 0x00, 0x28,
				0xac, 0xd9, 0x40, 0x78,
				0x02, 0x27, 0xe5, 0xc0,
				0x44, 0x00, 0x00, 0x03,
				0x00, 0x04, 0x00, 0x00,
				0x03, 0x00, 0xc8, 0x3c,
				0x60, 0xc6, 0x58,
		0x01,
		0x00, 0x06,
		0x68, 0xeb, 0xe3, 0xcb, 0x22, 0xc0 };
int getnum(BitBuffer& bb) {
	int i = 0;
	for (i = 0; i < 32 && !bb.get(1); i++)
		;
	return bb.get64(i) + (1 << i) - 1;
}
static inline int get_se_golomb(BitBuffer& bb) {
	int v = getnum(bb) + 1;
	int sign = -(v & 1);
	return ((v >> 1) ^ sign) - sign;
}
void testBitBuffer() {

	BitBuffer bb(true);
	
	for (auto& b : data) {
		bb.put(b, 8);
	}
	
	uint8_t configurationVersion = bb.get(8);
	uint8_t AVCProfileIndication = bb.get(8);
	uint8_t profile_compatibility = bb.get(8);
	uint8_t AVCLevelIndication = bb.get(8);
	uint8_t lengthSizeMinusOne = bb.get(8);
	lengthSizeMinusOne &= 0b11;
	uint8_t numOfSequenceParameterSets = bb.get(8);
	numOfSequenceParameterSets &= 0b11111;
	
	uint16_t sequenceParameterSetLength = bb.get64(16);
	uint8_t nal_unit_type = bb.get(8);
	/*uint8_t nal_unit_type = bb.get(5);
	uint8_t nal_ref_idc = bb.get(2);
	uint8_t forbidden_zero_bit = bb.get(1);*/
	uint8_t profile_idc = bb.get(8);//1
	uint8_t setflag = bb.get(8);//2
	uint8_t level_idc = bb.get(8);//3

	uint32_t seq_set_id = getnum(bb);//7

	int delta_scale, lastScale = 8, nextScale = 8;
	int sizeOfScalingList;
	if (profile_idc == 100 || profile_idc == 110 ||
		profile_idc == 122 || profile_idc == 244 || profile_idc == 44 ||
		profile_idc == 83 || profile_idc == 86 || profile_idc == 118 ||
		profile_idc == 128 || profile_idc == 138 || profile_idc == 139 ||
		profile_idc == 134) {
		int chroma_format_idc = getnum(bb); // chroma_format_idc
		if (chroma_format_idc == 3) {
			uint8_t separate_colour_plane_flag = bb.get(1);
			//skip_bits1(&gb); // separate_colour_plane_flag
		}
		int bit_depth_luma = getnum(bb) + 8;
		int bit_depth_chroma = getnum(bb) + 8;
		bb.get(1);//qpprime_y_zero_transform_bypass_flag
		if (bb.get(1)) { // seq_scaling_matrix_present_flag
			for (int i = 0; i < ((chroma_format_idc != 3) ? 8 : 12); i++) {
				if (!bb.get(1)) // seq_scaling_list_present_flag
					continue;
				lastScale = 8;
				nextScale = 8;
				sizeOfScalingList = i < 6 ? 16 : 64;
				for (int j = 0; j < sizeOfScalingList; j++) {
					if (nextScale != 0) {
						delta_scale = get_se_golomb(bb);
						nextScale = (lastScale + delta_scale) & 0xff;
					}
					lastScale = nextScale == 0 ? lastScale : nextScale;
				}
			}
		}
	}
	else {
		/*chroma_format_idc = 1;
		bit_depth_luma = 8;
		bit_depth_chroma = 8;*/
	}
	uint32_t log2_max_frame_num_minus4 = getnum(bb);//11
	uint32_t pic_order_cnt_type = getnum(bb);//15
	if (0 == pic_order_cnt_type) {
		uint32_t log2_max_pic_order_cnt_lsb_minus4 = getnum(bb);
	}
	else if (1 == pic_order_cnt_type){
		bb.get(1);
		getnum(bb);
		getnum(bb);
		int num_ref_frames_in_pic_order_cnt_cycle = getnum(bb);
		for (int i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++)
		{
			getnum(bb);
		}
	}
	uint32_t max_num_ref_frames = getnum(bb);//
	uint8_t gaps_in_frame_num_value_allowed_flag = bb.get(1);
	uint32_t pic_width_in_mbs_minus1 = getnum(bb);
	uint32_t pic_height_in_map_units_minus1 = getnum(bb);
	uint8_t frame_mbs_only_flag = bb.get(1);
	uint8_t mb_adaptive_frame_field_flag = 0;
	if (!frame_mbs_only_flag) {
		mb_adaptive_frame_field_flag = bb.get(1);
	}
	uint8_t direct_8x8_inference_flag = bb.get(1);
	uint8_t frame_cropping_flag = bb.get(1);
	if (frame_cropping_flag) {
		uint32_t frame_crop_left_offset = getnum(bb);
		uint32_t frame_crop_right_offset = getnum(bb);
		uint32_t frame_crop_top_offset = getnum(bb);
		uint32_t frame_crop_bottom_offset = getnum(bb);
	}
	uint8_t vui_parameters_present_flag = bb.get(1);
	if (vui_parameters_present_flag) {
		uint8_t aspect_ratio_info_present_flag = bb.get(1);
		if (aspect_ratio_info_present_flag) {
			uint8_t aspect_ratio_idc = bb.get(8);
			if (aspect_ratio_idc = 0xff) {
				uint16_t num = bb.get(16);
				uint16_t den = bb.get(16);
			}
			else {
			}
		}
	}

	uint8_t numOfPictureParameterSets = bb.get(8);
	uint16_t pictureParameterSetLength = bb.get(16);
}
void testfreeverb();
int main(int argc, char *argv[])
{
	testfreeverb();
	//testBitBuffer();
	//ff_avc_decode_sps(data + 8, sizeof(data));
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("OpenGL 程序");
	auto v = glGetString(GL_VERSION);
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	printf("OpenGL Version=%s texturemaxsize=%d\n", v, max);

	//初始化 glew wglMakeCurrent
	GLenum status = glewInit();
	assert(GLEW_OK == status);

#if 0
	FILE *file = fopen("d:/test.wav", "rb");
	wav_header_t wavHeader;
	fread(&wavHeader, 1, sizeof(wavHeader), file);
	chunk_t chunk;
	do
	{
		fread(&chunk, 1, sizeof(chunk), file);
		std::string s(chunk.ID, 4);
		printf("chunk:%s size%d\n", s.c_str(), chunk.size);
		if (0 != strncmp(chunk.ID, "data", 4)) {
			fseek(file, chunk.size, SEEK_CUR);
		}
	} while (0 != strncmp(chunk.ID, "data", 4));
#endif

	SDL_Init(SDL_INIT_AUDIO);
	avcodec_register_all();
	avformat_network_init();
	//av_log_set_level(AV_LOG_DEBUG);

	//FFMPEGTest::test_decode_encode("d:/v1080.mp4", "d:/mux.mp4");
#if 0
	SDLAudioHelper sdlAudioHelper;
	DirectSoundHelper directSoundHelper;
	IAudioPlay *audioPlay = &directSoundHelper;

	audioPlay->setSampleInfo(2, 44100, EAudioFormatS16LE);
	audioPlay->open();
	audioPlay->setPlayState(EPlayStatePlaying);
	std::thread t = std::thread([audioPlay, file]() {
		uint8_t buf[1024];
		for (;;) {
			uint32_t queueSize = audioPlay->getQueuedAudioSize();
			if (queueSize < 1024 * 200) {
				size_t len = fread(buf, 1, 1024, file);
				if (len > 0) {
					audioPlay->putData(buf, len);
				}
				else {
					printf("finish\n");
					break;
				}
			}
			else {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		});

	t.join();
#endif
	PlayManager playManager;
	//playManager.openFile("d:/v1080.mp4");
	playManager.openFile("d:/test.mp3");
	//playManager.openFile("rtmp://58.200.131.2:1935/livetv/hunantv");

	g_playManager = &playManager;
	glutDisplayFunc(&testdraw);
	glutIdleFunc(&myIdle);
	//glutKeyboardFunc(&keyboard);
	//glutSpecialFunc(&specialkey);
	
	glutMainLoop();



	int a = 0; 
	do
	{
		printf("0:exit 1:play 2:pause 3:seek\n");
		scanf("%d", &a);
		switch (a) {
		case 0:
			break;
		case 1:
			playManager.setPlayState(EPlayStatePlaying);
			break;
		case 2:
			playManager.setPlayState(EPlayStatePause);
			break;
		case 3:
			playManager.seek(5000);
			break;
		}
	} while (a != 0);
	playManager.close();

	SDL_Quit();
    return 0;
}

void testfreeverb() {
	float inl[16], inr[16], outl[16], outr[16];
	for (int i = 0; i < 16; i++) {
		inl[i] = inr[i] = 0.1f;
	}
	my_progenitor_t t = alloc_my_progenitor();

	//processreplace(t, inl, inr, outl, outr, 16);
	free_my_progenitor(t);
}