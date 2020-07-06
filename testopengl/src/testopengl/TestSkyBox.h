#pragma once
#include <string>
#include <GL/glew.h>
#include "TestJpeg.h"
#include "OpenGLHelper.h"
#include "vmath.h"

namespace TestSkyBox {

	static GLfloat skyboxVertices[] = {
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	static const char* g_vString = R"(
#version 430 core
layout(location=0) in vec3 aPos;
out vec3 TexCoords;
layout(location=1) uniform mat4 matrix;
void main(){
	TexCoords = aPos;
	gl_Position = matrix * vec4(aPos, 1.0);
}
)";

	static const char* g_fString = R"(
#version 430 core
out vec4 FragColor;
in vec3 TexCoords;
layout(location=4) uniform samplerCube skybox;
void main(){
	FragColor = texture(skybox, TexCoords);
}
)";

	static GLuint g_texture = 0;
	static GLuint g_program = 0;
	static GLuint g_vertex = 0;
	static GLuint g_vbuffer = 0;

	static void init() {
		int width = 0, height = 0, channelCount = 0;
		TestJpeg::getJpgInfo("./skybox/right.jpg", &width, &height, &channelCount);
		const char* jpgNames[] = {
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"front.jpg",
			"back.jpg",
		};
		glGenTextures(1, &g_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, g_texture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glTexStorage2D(GL_TEXTURE_CUBE_MAP, 10, GL_RGB8, width, height);//分配存储空间
		CHECKERR();
		
		int len = width * height * channelCount;
		void* buffer = malloc(len);
		for (int face = 0; face < 6; face++) {
			GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
			std::string filePath = "./skybox/";
			filePath += jpgNames[face];
			if (!TestJpeg::loadJpgImage(filePath.c_str(), buffer, len, NULL, NULL, NULL)) {
				assert(false);
			}
			glTexSubImage2D(target, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
			CHECKERR();
		}
		free(buffer);

		g_program = glCreateProgram();
		OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, g_vString, 0);
		OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_program);
		OpenGLHelper::outputProgramLog(g_program);

		glGenVertexArrays(1, &g_vertex);
		glBindVertexArray(g_vertex);
		glGenBuffers(1, &g_vbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glBindVertexArray(0);


	}
	static GLfloat g_xoffset = 0.f;
	static GLfloat g_yoffset = 0.f;

	void onkeyboard(int key, int x, int y) {
		if (key == GLUT_KEY_RIGHT) {
			g_yoffset += 10.0f;
		}
		else if (key == GLUT_KEY_LEFT){
			g_yoffset -= 10.0f;
		}
		else if (key == GLUT_KEY_UP) {
			g_xoffset += 10.f;
		}
		else if (key == GLUT_KEY_DOWN) {
			g_xoffset -= 10.f;
		}
	}

	static void testdraw() {
		glDepthMask(GL_FALSE);
		glUseProgram(g_program);

		glBindVertexArray(g_vertex);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, g_texture);
		GLint location = glGetUniformLocation(g_program, "skybox");
		glUniform1i(location, 0);

		GLint matrixLocation = glGetUniformLocation(g_program, "matrix");
		vmath::vec3 eye = vmath::vec3(0.f, 0.f, 0.0f);
		vmath::vec3 center = vmath::vec3(0.f, 0.f, -1.f);
		vmath::vec3 up = vmath::vec3(0.f, 1.f, 0.f);
		vmath::mat4 viewMatrix = vmath::lookat(eye, center, up);//设置相机位置，朝向，与相机上部的方向
		viewMatrix = vmath::rotate(0.f, g_yoffset, 0.f) * viewMatrix;
		float fovy = 90.f;
		float aspect = 1.0f / 1.0f;//width/height
		float n = 0.1f, f = 10.f;
		//设置相机照射的范围，长宽比率，近点与远点值
		vmath::mat4 projectionMatrix = vmath::perspective(fovy, aspect, n, f);// vmath::perspective(fovy, aspect, 0.1f, 100.f);
		vmath::mat4 matrix = projectionMatrix * viewMatrix;
		//matrix = vmath::scale(1.0f);
		glProgramUniformMatrix4fv(g_program, matrixLocation, 1, GL_FALSE, matrix);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindVertexArray(0);

		glDepthMask(GL_TRUE);

		glFlush();
	}
};