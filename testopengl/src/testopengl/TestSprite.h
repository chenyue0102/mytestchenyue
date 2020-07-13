#pragma once
#include <vector>
#include "GL\glew.h"
#include "OpenGLHelper.h"
#include "targa.h"

namespace TestSprite {
	static const char *g_vString = R"(
#version 430 core
layout(location=0) in vec3 vertexPosition;
void main(){
	//gl_PointSize = 
	gl_Position = vec4(vertexPosition, 1.0f);
}
)";
	static const char *g_fString = R"(
#version 430 core
layout(location=1) uniform sampler2D tex;
out vec4 fColor;
void main(){
	fColor = texture(tex, gl_PointCoord);
}
)";
	static GLuint g_vbuffer;
	static GLuint g_vertex;
	static GLuint g_texture;
	static GLuint g_program;
	static int g_pointcount;

	static void init() {
		g_program = glCreateProgram();
		OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, g_vString, 0);
		OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_program);
		OpenGLHelper::outputProgramLog(g_program);
		CHECKERR();

		std::vector<GLfloat> vertexs = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
		};
		g_pointcount = vertexs.size() / 3;
		glGenBuffers(1, &g_vbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexs.size(), vertexs.data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &g_vertex);
		glBindVertexArray(g_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		int vertexLocation = 0;
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vertexLocation);
		CHECKERR();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glGenTextures(1, &g_texture);
		GLenum format;
		int width, height;
		unsigned char *buf = vtarga::load_targa("sprite.tga", format, width, height);
		
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, buf);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		CHECKERR();
		
		vtarga::free_targa_buffer(buf);
	}

	static void testdraw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glPointSize(50);
		glUseProgram(g_program);

		glBindVertexArray(g_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		CHECKERR();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glUniform1i(glGetUniformLocation(g_program, "tex"), 0);
		CHECKERR();

		glDrawArrays(GL_POINTS, 0, g_pointcount);
		glFlush();
		CHECKERR();

		glUseProgram(0);
		glPointSize(1);
	}
}