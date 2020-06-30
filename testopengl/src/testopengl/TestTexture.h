#pragma once
#include <thread>
#include "OpenGLHelper.h"

using namespace OpenGLHelper;
namespace TestTexture {
	
	static const GLubyte tex_checkerboard_data[] = {
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
		0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
		0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
	};

	static const GLfloat g_vertex[][2] = {
		{ -1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ -1.0f, 1.0f },
		{ 1.0f, 1.0f },
	};

	static const GLfloat g_cvertex[][2] = {
		{0.0f, 0.0f},
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
	};

	static const char *g_vString = R"(
#version 430 core
layout(location=0) in vec4 vPosition;
layout(location=1) in vec4 tPosition;
//#define USE_PIPELINE
//pipeline形式,内置的gl_PerVertex必须重新声明
#ifdef USE_PIPELINE
out gl_PerVertex{
	vec4 gl_Position;
	float gl_PointSize;
};
#endif
out Param{
	vec4 fPosition;
};
void main(){
	gl_Position = vPosition;
	fPosition = tPosition;
}
)";

	static const char *g_fString = R"(
#version 430 core
layout(location=2) uniform sampler2D tex;
in Param{
	vec4 fPosition;
};
out vec4 fColor;
void main(){
	fColor = vec4(texture2D(tex, fPosition.xy).rgb, 1.0f);
}
)";

	static GLsizei g_texture_width = 8;
	static GLsizei g_texture_height = 8;
	static GLuint g_texture = 0;
	static GLuint g_vertexindex = 0;
	static GLuint g_buffer = 0, g_pixelbuffer = 0;
	static GLuint g_vprogramX = 0, g_fprogramX = 0;
	static GLuint g_pipelineX = 0;

	static void setTexture(GLuint tex) {
		g_texture = tex;
	}

	static void setWidthHeight(GLsizei width, GLsizei height) {
		g_texture_width = width;
		g_texture_height = height;
	}

	static void init() {
		glGenTextures(1, &g_texture);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLsizei levels = 1;//mip的数量
		GLsizei level = 0;//mip等级
		GLint internalformat = GL_R8;//材质内部编码
		GLint border = 0;//must be 0
		GLenum format = GL_RED;//tex_checkerboard_data编码
		GLenum type = GL_UNSIGNED_BYTE;//tex_checkerboard_data类型
		if (false) {
			glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, g_texture_width, g_texture_height);//不可改变存储
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, level, internalformat, g_texture_width, g_texture_height, border, format, type, nullptr);//可以改变存储
		}
		CHECKERR();

		
		glGenBuffers(1, &g_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, g_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex) + sizeof(g_cvertex), nullptr, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vertex), g_vertex);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vertex), sizeof(g_cvertex), g_cvertex);
		CHECKERR();

		glGenVertexArrays(1, &g_vertexindex);
		glBindVertexArray(g_vertexindex);
		glBindBuffer(GL_ARRAY_BUFFER, g_buffer);

		GLuint vPositionLocation = 0;
		glVertexAttribPointer(vPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vPositionLocation);

		GLuint tPositionLocation = 1;
		glVertexAttribPointer(tPositionLocation, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vertex)));
		glEnableVertexAttribArray(tPositionLocation);
		CHECKERR();
#if 0
		g_vprogramX = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &g_vString);
		g_fprogramX = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &g_fString);
		glCreateProgramPipelines(1, &g_pipelineX);
#else
		g_vprogramX = glCreateProgram();
		attachShader(g_vprogramX, GL_VERTEX_SHADER, g_vString, 0);
		attachShader(g_vprogramX, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_vprogramX);
		outputProgramLog(g_vprogramX);
		CHECKERR();
#endif

		//创建pixel unpack 缓存
		glGenBuffers(1, &g_pixelbuffer);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, g_pixelbuffer);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(tex_checkerboard_data), tex_checkerboard_data, GL_STATIC_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

		if (false) {
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_texture_width, g_texture_height, GL_RED, GL_UNSIGNED_BYTE, tex_checkerboard_data);
		}
		else {
			//使用pixel unpack缓存
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, g_pixelbuffer);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_texture_width, g_texture_height, GL_RED, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
			glDeleteBuffers(1, &g_pixelbuffer);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	static void testdraw() {
		/*glUseProgramStages(g_pipelineX, GL_VERTEX_SHADER_BIT, g_vprogramX);
		CHECKERR();
		glUseProgramStages(g_pipelineX, GL_FRAGMENT_SHADER_BIT, g_fprogramX);
		CHECKERR();
		glBindProgramPipeline(g_pipelineX);*/
		glUseProgram(g_vprogramX);
		CHECKERR();

		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(g_vertexindex);
		CHECKERR();

		glActiveTexture(GL_TEXTURE0);//激活纹理单元
		glBindTexture(GL_TEXTURE_2D, g_texture);
		GLuint texLocation = glGetUniformLocation(g_vprogramX, "tex");
		glUniform1i(texLocation, 0);
		CHECKERR();

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		CHECKERR();
		glFlush();
	}

	static void myIdle() {
		testdraw();
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	static const char *g_vStringTextureBuffer = R"(
#version 430 core
uniform usamplerBuffer buf;
in int tex_coord;
layout (location = 0) out vec4 color;
void main(){
	color = texelFetch(buf, tex_coord);
}
)";

	static GLuint g_texturebuffer = 0;
	static GLuint g_texturetexturebuffer = 0;
	static void inittexturebuffer() {
		glGenBuffers(1, &g_texturebuffer);
		glBindBuffer(GL_TEXTURE_BUFFER, g_texturebuffer);
		glBufferData(GL_TEXTURE_BUFFER, sizeof(tex_checkerboard_data), tex_checkerboard_data, GL_STATIC_DRAW);
		CHECKERR();

		glGenTextures(1, &g_texturetexturebuffer);
		glBindTexture(GL_TEXTURE_BUFFER, g_texturetexturebuffer);
		glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, g_texturebuffer);
		CHECKERR();
	}
}