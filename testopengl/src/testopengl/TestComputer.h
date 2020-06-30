#pragma once
#include <GL/glew.h>
#include "OpenGLHelper.h"

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
			data.g = 0xfe;
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
}