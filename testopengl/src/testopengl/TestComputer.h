#pragma once
#include <GL/glew.h>
#include "OpenGLHelper.h"
#include "TestJpeg.h"

namespace TestComputer {
	static GLuint g_program = 0;
	static const char *g_cString = R"(
#version 430 core
layout(local_size_x = 1, local_size_y = 1) in;
layout(binding=0,rgba8ui) readonly uniform uimage2D image_in;
layout(binding=1,rgba8ui) writeonly uniform uimage2D image_out;
void main(){
	ivec2 dims = imageSize(image_in);
	for (uint row = 0; row < dims.y; row++){
		for (uint column = 0; column < dims.x; column++){
			ivec2 pos = ivec2(column, row);
			uvec4 data = imageLoad(image_in, pos);
			imageStore(image_out, pos, data);
		}
	}
}
)";
	static void test() {
		const int width = 4, height = 2;
		const unsigned char img_data[] = {
			0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00,
			0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00,
		};
		g_program = glCreateProgram();
		CHECKERR();
		OpenGLHelper::attachShader(g_program, GL_COMPUTE_SHADER, g_cString, 0);
		CHECKERR();
		glLinkProgram(g_program);
		CHECKERR();

		glUseProgram(g_program);
		CHECKERR();

		GLuint tex_in, tex_out;
		glGenTextures(1, &tex_in);
		glGenTextures(1, &tex_out);
		glBindTexture(GL_TEXTURE_2D, tex_in);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		CHECKERR();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, width, height, 0, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, img_data);
		CHECKERR();
		glBindImageTexture(0, tex_in, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8UI);
		CHECKERR();

		glBindTexture(GL_TEXTURE_2D, tex_out);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		CHECKERR();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, width, height, 0, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, 0);
		CHECKERR();
		glBindImageTexture(1, tex_out, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8UI);
		CHECKERR();

		CHECKERR();
		if (true) {
			glDispatchCompute(10, 10, 1);//GL_MAX_COMPUTE_WORK_GROUP_SIZE
			CHECKERR();
		}
		else {
			static const struct {
				GLuint num_groups_x;
				GLuint num_groups_y;
				GLuint num_groups_z;
			}dispatch_params = {16,16, 1};
			GLuint buf = 0;
			glGenBuffers(1, &buf);
			glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, buf);
			glBufferData(GL_DISPATCH_INDIRECT_BUFFER, sizeof(dispatch_params), &dispatch_params, GL_STATIC_DRAW);
			glDispatchComputeIndirect(0);
			CHECKERR();
			glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, 0);
			glDeleteBuffers(1, &buf);
			CHECKERR();
		}
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
		CHECKERR();

		glBindTexture(GL_TEXTURE_2D, tex_out);
		CHECKERR();
		unsigned char img_data2[width * height * 3] = { 0 };
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, img_data2);
		CHECKERR();

		glBindTexture(GL_TEXTURE_2D, 0);
		CHECKERR();
		glUseProgram(0);
		CHECKERR();
	}

	static const char *g_rgb2yuv = R"(
#version 430 core
layout(local_size_x = 1, local_size_y = 1) in;
layout(binding=0,rgba8ui) readonly uniform uimage2D image_rgb;
layout(binding=1,r8ui) writeonly uniform uimage2D image_y;
layout(binding=2,r8ui) writeonly uniform uimage2D image_u;
layout(binding=3,r8ui) writeonly uniform uimage2D image_v;

void rgb2yuv(const in uint r, const in uint g, const in uint b, out uint y, out uint u, out uint v)
{
	y = uint(0.299f * r + 0.587f * g + 0.114f * b) & 0xff;
	u = uint(-0.169f * r - 0.331f * g + 0.5f * b + 128) & 0xff;
	v = uint(0.5f * r - 0.419f * g - 0.081f * b + 128) & 0xff;
}

void rgb2y(const in uint r, const in uint g, const in uint b, out uint y)
{
	y = uint(0.299f * r + 0.587f * g + 0.114f * b) & 0xff;
}

uint getColCountPerThread(uint width, uint threadCount)
{
	uint count = (width / threadCount);
	if ((width % threadCount) != 0)
	{
		count++;
	}
	return count;
}

void main(){
	ivec2 dims = imageSize(image_rgb);
	int texWidth = dims.x;
	int texHeight = dims.y;
	const uvec3 groupSize = gl_NumWorkGroups;
	const uvec3 groupIndex = gl_WorkGroupID;
	const uint columnCountPerThread = getColCountPerThread(texWidth, groupSize.x);
	//一行执行完后，再执行+groupSize.y后的一行
	for (uint row = groupIndex.y; row < texHeight; row += groupSize.y){
		bool bEvenRow = (row & 0x00000001) == 0;
		for (uint column = groupIndex.x * columnCountPerThread, columnCount = 0; column < texWidth && columnCount < columnCountPerThread; column++, columnCount++){
			ivec2 pos = ivec2(column, row);
			uvec4 rgb = imageLoad(image_rgb, pos);
			bool bEvenColumn = (column & 0x00000001) == 0;
			if (bEvenRow && bEvenColumn){
				uint y=0, u=0, v=0;
				rgb2yuv(rgb.r, rgb.g, rgb.b, y, u, v);
				imageStore(image_y, pos, uvec4(y));
				ivec2 uvPos = pos / 2;
				imageStore(image_u, uvPos, uvec4(u));
				imageStore(image_v, uvPos, uvec4(v));
			}else{
				uint y=0;
				rgb2y(rgb.r, rgb.g, rgb.b, y);
				imageStore(image_y, pos, uvec4(y,0,0,0));
			}
		}
	}
}
)";

	const char *g_yuv2rgbString = R"(
#verson 430 core
layout(local_size_x = 1, local_size_y = 1) in;
layout(binding=0,rgba8ui) readonly uniform uimageBuffer image_rgb;
layout(binding=1,r8ui) writeonly uniform uimageBuffer image_y;
layout(binding=2) readonly uniform ivec2 dims;
void main(){
}
)";

	const char *g_rgb2yuvString2 = R"(
#version 430 core
layout(local_size_x = 1, local_size_y = 1) in;
layout(binding=0,r8ui) readonly uniform uimageBuffer image_rgb;
layout(binding=1,r8ui) writeonly uniform uimageBuffer image_yuv;
layout(location=2) uniform ivec2 dims;

void rgb2yuv(const in uint r, const in uint g, const in uint b, out uint y, out uint u, out uint v)
{
	y = uint(0.299f * r + 0.587f * g + 0.114f * b) & 0xff;
	u = uint(-0.169f * r - 0.331f * g + 0.5f * b + 128) & 0xff;
	v = uint(0.5f * r - 0.419f * g - 0.081f * b + 128) & 0xff;
}

void rgb2y(const in uint r, const in uint g, const in uint b, out uint y)
{
	y = uint(0.299f * r + 0.587f * g + 0.114f * b) & 0xff;
}

uint getColCountPerThread(uint width, uint threadCount)
{
	uint count = (width / threadCount);
	if ((width % threadCount) != 0)
	{
		count++;
	}
	return count;
}

void main(){
	int texWidth = dims.x;
	int texHeight = dims.y;
	const uvec3 groupSize = gl_NumWorkGroups;
	const uvec3 groupIndex = gl_WorkGroupID;
	const uint columnCountPerThread = getColCountPerThread(texWidth, groupSize.x);
	//一行执行完后，再执行+groupSize.y后的一行
	for (uint row = groupIndex.y; row < texHeight; row += groupSize.y){
		bool bEvenRow = (row & 0x00000001) == 0;
		for (uint column = groupIndex.x * columnCountPerThread, columnCount = 0; column < texWidth && columnCount < columnCountPerThread; column++, columnCount++){
			int pos = int(row * (texWidth * 3) + column * 3);
			//ivec2 pos = ivec2(column, row);
			uvec4 r = imageLoad(image_rgb, pos);
			uvec4 g = imageLoad(image_rgb, pos + 1);
			uvec4 b = imageLoad(image_rgb, pos + 2);
			bool bEvenColumn = (column & 0x00000001) == 0;
			int yPos = int(row * texWidth + column);
			if (bEvenRow && bEvenColumn){
				int uvPos = int((row / 2) * (texWidth / 2) + column / 2);
				uint y=0, u=0, v=0;
				rgb2yuv(r.r, g.r, b.r, y, u, v);
				imageStore(image_yuv, yPos, uvec4(y));
				imageStore(image_yuv, int(texWidth * texHeight + uvPos), uvec4(u));
				imageStore(image_yuv, int(texWidth * texHeight + (texWidth * texHeight / 4) + uvPos), uvec4(v));
			}else{
				uint y=0;
				rgb2y(r.r, g.r, b.r, y);
				imageStore(image_yuv, yPos, uvec4(y));
			}
		}
	}
}
)";

	static GLuint g_rgb2yuvprogram = 0;
	static GLuint g_yuv2rgbprogram = 0;

	static GLuint g_rgb2yuvprogram2 = 0;

	static void init() {
		g_rgb2yuvprogram = glCreateProgram();
		OpenGLHelper::attachShader(g_rgb2yuvprogram, GL_COMPUTE_SHADER, g_rgb2yuv, 0);
		glLinkProgram(g_rgb2yuvprogram);
		OpenGLHelper::outputProgramLog(g_rgb2yuvprogram);
		CHECKERR();

		g_rgb2yuvprogram2 = glCreateProgram();
		OpenGLHelper::attachShader(g_rgb2yuvprogram2, GL_COMPUTE_SHADER, g_rgb2yuvString2, 0);
		glLinkProgram(g_rgb2yuvprogram2);
		OpenGLHelper::outputProgramLog(g_rgb2yuvprogram2);
		CHECKERR();
	}

	void setTexParameteri(GLenum target, GLint paramFilter, GLint paramWrap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, paramFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, paramFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paramWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paramWrap);
	}
	typedef unsigned char uchar8;
	static void rgb2yuv(uchar8 r, uchar8 g, uchar8 b, uchar8 *y, uchar8 *u, uchar8 *v)
	{
		*y = (unsigned int)(0.299f * r + 0.587f * g + 0.114f * b) & 0xff;
		*u = (unsigned int)(-0.169f * r - 0.331f * g + 0.5f * b + 128) & 0xff;
		*v = (unsigned int)(0.5f * r - 0.419f * g - 0.081f * b + 128) & 0xff;
	}
	static void rgb2y(uchar8 r, uchar8 g, uchar8 b, uchar8 *y)
	{
		*y = (unsigned int)(0.299f * r + 0.587f * g + 0.114f * b) & 0xff;
	}
	static int getYPos(int width, int height, int column, int row) {
		return row * width + column;
	}
	static int getUVPos(int width, int height, int column, int row) {
		return row / 2 * width / 2 + column / 2;
	}
	//rgbBuffer对齐值为1
	static void rgb2yuv_cpu(int width, int height, const void *rgbBuffer, int rgblen, void *tmpyuvBuffer, int yuvlen) {
		uchar8 *yBuffer = (uchar8*)tmpyuvBuffer;
		uchar8 *uBuffer = yBuffer + width * height;
		uchar8 *vBuffer = uBuffer + width * height / 4;
		for (int row = 0; row < height; row++) {
			bool bEvenRow = (row & 0x00000001) == 0;
			const char *pOneRow = (const char*)rgbBuffer + row * (width * 3);
			for (int column = 0; column < width; column++) {
				bool bEvenColumn = (column & 0x00000001) == 0;
				uchar8 r = pOneRow[column * 3 + 0];
				uchar8 g = pOneRow[column * 3 + 1];
				uchar8 b = pOneRow[column * 3 + 2];
				if (bEvenRow && bEvenColumn) {
					uchar8 y, u, v;
					rgb2yuv(r, g, b, &y, &u, &v);
					yBuffer[getYPos(width, height, column, row)] = y;
					uBuffer[getUVPos(width, height, column, row)] = u;
					vBuffer[getUVPos(width, height, column, row)] = v;
				}
				else {
					uchar8 y;
					rgb2y(r, g, b, &y);
					yBuffer[getYPos(width, height, column, row)] = y;
				}

			}
		}
	}

	static GLuint g_rgb2yuv_rgbtexture;
	static GLuint g_rgb2yuv_yuvtexture;
	static GLuint g_rgb2yuv_yuvtextures[3];
	static GLuint g_rgb2yuv_yuvbuffer;
	static GLuint g_rgb2yuv_rgbbuffer;

//#define USE_IMAGE2D
	static void initrgb2yuvtexture(int width, int height) {
#ifdef USE_IMAGE2D
		glGenTextures(1, &g_rgb2yuv_rgbtexture);
		glBindTexture(GL_TEXTURE_2D, g_rgb2yuv_rgbtexture);
		setTexParameteri(GL_TEXTURE_2D, GL_LINEAR, GL_CLAMP_TO_EDGE);//必须设置filter,
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, width, height, 0, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, 0);
		CHECKERR();

		glGenTextures(3, g_rgb2yuv_yuvtextures); 
		for (int i = 0; i < 3; i++) {
			glBindTexture(GL_TEXTURE_2D, g_rgb2yuv_yuvtextures[i]);
			setTexParameteri(GL_TEXTURE_2D, GL_LINEAR, GL_CLAMP_TO_EDGE);
			CHECKERR();
			if (i == 0) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 0);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width / 2, height / 2, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 0);
			}

			CHECKERR();
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		glGenBuffers(1, &g_rgb2yuv_yuvbuffer);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, g_rgb2yuv_yuvbuffer);
		glBufferData(GL_PIXEL_PACK_BUFFER, width * height + width * height / 2, nullptr, GL_STREAM_READ);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
		CHECKERR();
#else
		GLuint tmpTex;
		glGenTextures(1, &tmpTex);

		glGenBuffers(1, &g_rgb2yuv_rgbbuffer);
		glBindBuffer(GL_TEXTURE_BUFFER, g_rgb2yuv_rgbbuffer);
		glBufferData(GL_TEXTURE_BUFFER, width * height * 3, nullptr, GL_DYNAMIC_DRAW);
		CHECKERR();

		glGenTextures(1, &g_rgb2yuv_rgbtexture);
		glBindTexture(GL_TEXTURE_BUFFER, g_rgb2yuv_rgbtexture);
		//setTexParameteri(GL_TEXTURE_BUFFER, GL_LINEAR, GL_CLAMP_TO_EDGE);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, g_rgb2yuv_rgbbuffer);
		CHECKERR();

		glGenBuffers(1, &g_rgb2yuv_yuvbuffer);
		glBindBuffer(GL_TEXTURE_BUFFER, g_rgb2yuv_yuvbuffer);
		glBufferData(GL_TEXTURE_BUFFER, width * height + width * height / 2, nullptr, GL_DYNAMIC_READ);
		CHECKERR();

		glGenTextures(1, &g_rgb2yuv_yuvtexture);
		glBindTexture(GL_TEXTURE_BUFFER, g_rgb2yuv_yuvtexture);
		//setTexParameteri(GL_TEXTURE_BUFFER, GL_LINEAR, GL_CLAMP_TO_EDGE);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, g_rgb2yuv_yuvbuffer);
		CHECKERR();
#endif
	}

	static void rgb2yuv(int width, int height, const void *rgbBuffer, int rgblen, void *yuvBuffer, int yuvlen) {
#ifdef USE_IMAGE2D
		glUseProgram(g_rgb2yuvprogram);

		glBindTexture(GL_TEXTURE_2D, g_rgb2yuv_rgbtexture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, rgbBuffer);
		glBindImageTexture(0, g_rgb2yuv_rgbtexture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8UI);
		CHECKERR();

		for (int i = 0; i < 3; i++){
			glBindTexture(GL_TEXTURE_2D, g_rgb2yuv_yuvtextures[i]);
			glBindImageTexture(i + 1, g_rgb2yuv_yuvtextures[i], 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8UI);
			CHECKERR();
		}

		glDispatchCompute(200, 100, 1);
		CHECKERR();

		glMemoryBarrier(GL_ALL_BARRIER_BITS);
		CHECKERR();

		if (0) {
			int offset = 0;
			GLint texWidth = 0, texHeight = 0;
			glGetTextureLevelParameteriv(g_rgb2yuv_yuvtextures[0], 0, GL_TEXTURE_WIDTH, &texWidth);
			glGetTextureImage(g_rgb2yuv_yuvtextures[0], 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, width * height, (char*)yuvBuffer + offset);
			offset += width * height;
			CHECKERR();
			glGetTextureLevelParameteriv(g_rgb2yuv_yuvtextures[1], 0, GL_TEXTURE_WIDTH, &texWidth);
			glGetTextureLevelParameteriv(g_rgb2yuv_yuvtextures[1], 0, GL_TEXTURE_HEIGHT, &texHeight);
			glPixelStorei(GL_PACK_ALIGNMENT, 1);//opengl 默认要求内存存储的宽度被4整除，这里改变下对齐值
			glGetTextureImage(g_rgb2yuv_yuvtextures[1], 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, texWidth * texHeight, (char*)yuvBuffer + offset);
			offset += width * height / 4;
			CHECKERR();
			glGetTextureImage(g_rgb2yuv_yuvtextures[2], 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, width * height / 4, (char*)yuvBuffer + offset);
			offset += width * height / 4;
			CHECKERR();
			glPixelStorei(GL_PACK_ALIGNMENT, 4);
		}
		else {
			glPixelStorei(GL_PACK_ALIGNMENT, 1);//opengl 默认要求内存存储的宽度被4整除，这里改变下对齐值
			int offset = 0;
			CHECKERR();
			glBindBuffer(GL_PIXEL_PACK_BUFFER, g_rgb2yuv_yuvbuffer);
			CHECKERR();
			glGetTextureImage(g_rgb2yuv_yuvtextures[0], 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, width * height, BUFFER_OFFSET(offset));
			CHECKERR();
			offset += width * height;
			glGetTextureImage(g_rgb2yuv_yuvtextures[1], 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, width * height / 4, BUFFER_OFFSET(offset));
			offset += width * height / 4;
			glGetTextureImage(g_rgb2yuv_yuvtextures[2], 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, width * height / 4, BUFFER_OFFSET(offset));
			CHECKERR();
			void *buf = glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
			CHECKERR();
			memcpy(yuvBuffer, buf, width * height + width * height / 2);
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
			CHECKERR();
			glPixelStorei(GL_PACK_ALIGNMENT, 4);
			CHECKERR();
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
#else
		glUseProgram(g_rgb2yuvprogram2);

		glBindTexture(GL_TEXTURE_BUFFER, g_rgb2yuv_rgbtexture);
		CHECKERR();
		glBindBuffer(GL_TEXTURE_BUFFER, g_rgb2yuv_rgbbuffer);
		CHECKERR();
		glBufferData(GL_TEXTURE_BUFFER, width * height * 3, rgbBuffer, GL_DYNAMIC_DRAW);
		CHECKERR();
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, g_rgb2yuv_rgbbuffer);
		CHECKERR();
		glBindImageTexture(0, g_rgb2yuv_rgbtexture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R8UI);
		CHECKERR();

		glBindTexture(GL_TEXTURE_BUFFER, g_rgb2yuv_yuvtexture);
		glBindBuffer(GL_TEXTURE_BUFFER, g_rgb2yuv_yuvbuffer);
		glBufferData(GL_TEXTURE_BUFFER, width * height + width * height / 2, nullptr, GL_DYNAMIC_READ);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, g_rgb2yuv_yuvbuffer);
		glBindImageTexture(1, g_rgb2yuv_yuvtexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8UI);
		CHECKERR();

		glProgramUniform2i(g_rgb2yuvprogram2, 2, width, height);
		CHECKERR();

		glDispatchCompute(200, 100, 1);
		CHECKERR();

		glMemoryBarrier(GL_ALL_BARRIER_BITS);
		CHECKERR();

		glBindBuffer(GL_TEXTURE_BUFFER, g_rgb2yuv_yuvbuffer);
		CHECKERR();
		void *buf = glMapBuffer(GL_TEXTURE_BUFFER, GL_READ_ONLY);
		CHECKERR();
		memcpy(yuvBuffer, buf, width * height + width * height / 2);
		glUnmapBuffer(GL_TEXTURE_BUFFER);
		CHECKERR();

		glBindBuffer(GL_TEXTURE_BUFFER, 0);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
#endif

		

	}
}