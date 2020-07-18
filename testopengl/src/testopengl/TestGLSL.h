#pragma once
#include <GL\glew.h>
#include "OpenGLHelper.h"

namespace TestGLSL {
	static const char *g_cString = R"(
#version 430 core
layout (local_size_x=1,local_size_y=1) in;
layout(location=0) uniform vec3 param;
layout(binding=1) buffer ResultBuffer{
	float f[];
}resultBuffer;
void main(){
	vec3 v = vec3(param.x, param.y, param.z);
	vec3 n = normalize(v);
	resultBuffer.f[0] = n.x;
	resultBuffer.f[1] = n.y;
	resultBuffer.f[2] = n.z;
}
)";
	static GLuint g_program = 0;
	static GLuint g_rbuffer;
	static void init() {
		g_program = glCreateProgram();
		OpenGLHelper::attachShader(g_program, GL_COMPUTE_SHADER, g_cString, 0);
		glLinkProgram(g_program);
		OpenGLHelper::outputProgramLog(g_program);
		CHECKERR();

		glGenBuffers(1, &g_rbuffer);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, g_rbuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(GLfloat) * 3, NULL, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		CHECKERR();
	}

	static void testdraw() {
		glUseProgram(g_program);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, g_rbuffer);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, g_rbuffer);
		CHECKERR();

		GLfloat f[3] = { 0.802f, 0.267f, 0.534f };
		GLint paramLocation = glGetUniformLocation(g_program, "param");
		glProgramUniform3f(g_program, paramLocation, f[0], f[1], f[2]);
		CHECKERR();

		glDispatchCompute(1, 1, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);

		void *buf = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
		memcpy(f, buf, sizeof(f));
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glUseProgram(0);
	}
}