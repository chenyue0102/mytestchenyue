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
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
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
				imageStore(image_u, pos / 2, uvec4(u));
				imageStore(image_v, pos / 2, uvec4(v));
			}else{
				uint y=0;
				rgb2y(rgb.r, rgb.g, rgb.b, y);
				imageStore(image_y, pos, uvec4(y,0,0,0));
			}
		}
	}
}
)";
	static GLuint g_rgb2yuvprogram = 0;
	static void init() {
		g_rgb2yuvprogram = glCreateProgram();
		OpenGLHelper::attachShader(g_rgb2yuvprogram, GL_COMPUTE_SHADER, g_rgb2yuv, 0);
		glLinkProgram(g_rgb2yuvprogram);
		OpenGLHelper::outputProgramLog(g_rgb2yuvprogram);
		CHECKERR();
	}

	void setTexParameteri(GLenum target, GLint paramFilter, GLint paramWrap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, paramFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, paramFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, paramWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, paramWrap);
	}

	static void rgb2yuv(int width, int height, const void *rgbBuffer, int rgblen, void *yuvBuffer, int yuvlen) {
		glUseProgram(g_rgb2yuvprogram);

		GLuint rgbTex;
		glGenTextures(1, &rgbTex);
		glBindTexture(GL_TEXTURE_2D, rgbTex);
		setTexParameteri(GL_TEXTURE_2D, GL_LINEAR, GL_CLAMP_TO_EDGE);//必须设置filter,
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, width, height, 0, GL_RGB_INTEGER, GL_UNSIGNED_BYTE, rgbBuffer);
		CHECKERR();
		glBindImageTexture(0, rgbTex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8UI);
		CHECKERR();

		GLuint yuvTex[3];
		glGenTextures(3, yuvTex);
		for (int i = 0; i < 3; i++){
			glBindTexture(GL_TEXTURE_2D, yuvTex[i]);
			setTexParameteri(GL_TEXTURE_2D, GL_LINEAR, GL_CLAMP_TO_EDGE);
			CHECKERR();
			if (i == 0) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 0);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width / 2, height / 2, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 0);
			}
			
			CHECKERR();
			glBindImageTexture(i + 1, yuvTex[i], 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8UI);
			CHECKERR();
		}

		glDispatchCompute(1, 1, 1);
		CHECKERR();

		glMemoryBarrier(GL_ALL_BARRIER_BITS);
		CHECKERR();

		int offset = 0;
		glBindTexture(GL_TEXTURE_2D, yuvTex[0]);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, (char*)yuvBuffer + offset);
		offset += width * height;
		CHECKERR();
		glBindTexture(GL_TEXTURE_2D, yuvTex[1]);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, (char*)yuvBuffer + offset);
		offset += width * height / 4;
		CHECKERR();
		glBindTexture(GL_TEXTURE_2D, yuvTex[2]);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, (char*)yuvBuffer + offset);
		CHECKERR();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &rgbTex);
		glDeleteTextures(3, yuvTex);
		glUseProgram(0);
	}
}