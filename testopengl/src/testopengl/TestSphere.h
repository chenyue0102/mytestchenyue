#pragma once
#include <vector>
#include <math.h>
#include "GL\glew.h"
#include "OpenGLHelper.h"

#define PI M_PI
namespace TestSphere {
	static const char *g_vString = R"(
#version 430 core
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 vertexTexCoord;
layout(location=2) uniform mat4 matrix;
layout(location=4) uniform vec3 color;
out vec2 texCoord;
out vec3 lineColor;
void main(){
	gl_Position = matrix * vec4(vertexPosition, 1.0f);
	texCoord = vertexTexCoord;
	lineColor = color;
}
)";

	static const char *g_fString = R"(
#version 430 core
layout(location=3) uniform sampler2D tex;
in vec2 texCoord;
in vec3 lineColor;
out vec4 fColor;
void main(){
	fColor = vec4(texture2D(tex, texCoord).rgb, 1.0f);
	//fColor = vec4(lineColor.rgb, 1.0f);
}
)";
	void buildVertices(int stackCount, int sectorCount, std::vector<float> &vertices, std::vector<float> &texCoords, std::vector<GLfloat> &normals, std::vector<GLint> &indices);
	static GLuint g_program;
	static std::vector<GLfloat> g_vertexs;
	static std::vector<GLfloat> g_texcoords;
	static std::vector<GLfloat> g_normals;
	static std::vector<GLfloat> g_allvertexs;
	static std::vector<GLint> g_indices;
	static GLuint g_vertexarray;
	static GLuint g_vertexarraybuffer;
	static GLuint g_elementarraybuffer;
	static GLuint g_tex;
	static GLfloat g_xoffset = 0.f;
	static GLfloat g_yoffset = 0.f;
	static GLfloat g_zoffset = 0.f;
	static void init() {
		g_program = glCreateProgram();
		OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, g_vString, 0);
		OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_program);
		OpenGLHelper::outputProgramLog(g_program);
		CHECKERR();

		buildVertices(50, 50, g_vertexs, g_texcoords, g_normals, g_indices);

		auto iterVertex = g_vertexs.begin(), iterTex = g_texcoords.begin();
		while (iterVertex != g_vertexs.end() && iterTex != g_texcoords.end()) {
			g_allvertexs.push_back(*(iterVertex++));
			g_allvertexs.push_back(*(iterVertex++));
			g_allvertexs.push_back(*(iterVertex++));

			g_allvertexs.push_back(*(iterTex++));
			g_allvertexs.push_back(*(iterTex++));
		}

		glGenBuffers(1, &g_elementarraybuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_elementarraybuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * g_indices.size(), g_indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenBuffers(1, &g_vertexarraybuffer);
		glBindBuffer(GL_ARRAY_BUFFER, g_vertexarraybuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * g_allvertexs.size(), g_allvertexs.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECKERR();

		glGenVertexArrays(1, &g_vertexarray);
		glBindVertexArray(g_vertexarray);
		glBindBuffer(GL_ARRAY_BUFFER, g_vertexarraybuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		CHECKERR();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		int width, height;
		bool success = TestJpeg::genTextureAndLoadJpg("earth.jpg", true, GL_RGB, &g_tex, &width, &height, NULL);
		assert(success);
		glBindTexture(GL_TEXTURE_2D, g_tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	static void buildVertices(int stackCount, int sectorCount, std::vector<GLfloat> &vertices, std::vector<GLfloat> &texCoords, std::vector<GLfloat> &normals, std::vector<GLint> &indices) {
		GLfloat radius = 0.5f;
		GLfloat lengthInv = 1.0f / radius;
		GLfloat sectorSetp = static_cast<GLfloat>(2 * PI / sectorCount);
		GLfloat stackStep = static_cast<GLfloat>(PI / stackCount);
		GLfloat sectorAngle, stackAngle;
		GLfloat x, y, z;
		GLfloat s, t;
		GLfloat sectionRadius;
		for (int i = 0; i <= stackCount; i++) {
			stackAngle = static_cast<GLfloat>(PI / 2 - i * stackStep);//弧度
			sectionRadius = radius * cosf(stackAngle);//切面的半径
			z = radius * sinf(stackAngle);

			for (int j = 0; j <= sectorCount; j++) {
				sectorAngle = j * sectorSetp;
				x = sectionRadius * cosf(sectorAngle);
				y = sectionRadius * sinf(sectorAngle);

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				normals.push_back(x * lengthInv);
				normals.push_back(y * lengthInv);
				normals.push_back(z * lengthInv);

				s = (GLfloat)j / sectorCount;
				t = (GLfloat)i / stackCount;
				texCoords.push_back(s);
				texCoords.push_back(t);
			}
		}

		int k1, k2;
		for (int i = 0; i < stackCount; i++) {
			k1 = i * (sectorCount + 1);
			k2 = k1 + sectorCount + 1;
			for (int j = 0; j < sectorCount; j++, k1++, k2++) {
				if (i != 0) {
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				if (i != (stackCount - 1)) {
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}
	}

	static void testdraw() {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glUseProgram(g_program);

		glBindVertexArray(g_vertexarray);
		glBindBuffer(GL_ARRAY_BUFFER, g_vertexarraybuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_elementarraybuffer);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_tex);
		GLuint texLocation = glGetUniformLocation(g_program, "tex");
		glUniform1i(texLocation, 0);

		vmath::mat4 standardMatrix = vmath::mat4(
			vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		vmath::vec3 eye = vmath::vec3(0.f, -1.f, 0.0f);
		vmath::vec3 center = vmath::vec3(0.f, 0.f, 0.f);
		vmath::vec3 up = vmath::vec3(0.f, 0.f, 1.f);
		vmath::mat4 viewMatrix = vmath::lookat(eye, center, up);//设置相机位置，朝向，与相机上部的方向
		float fovy = 90.f;
		float aspect = 1.0f / 1.0f;//width/height
		float n = 0.1f, f = 10.f;
		//设置相机照射的范围，长宽比率，近点与远点值
		vmath::mat4 projectionMatrix = vmath::perspective(fovy, aspect, n, f);// vmath::perspective(fovy, aspect, 0.1f, 100.f);

		vmath::mat4 matrix = projectionMatrix * viewMatrix * vmath::rotate(0.f, 0.f, g_zoffset);
		//matrix = standardMatrix;
		glProgramUniformMatrix4fv(g_program, 2, 1, GL_FALSE, matrix);
		CHECKERR();

		//glDrawElements(GL_TRIANGLE_STRIP, g_indices.size(), GL_UNSIGNED_INT, 0);
		glProgramUniform3f(g_program, 4, 1.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, g_indices.size(), GL_UNSIGNED_INT, 0);
		//glProgramUniform3f(g_program, 4, 0.0f, 1.0f, 1.0f);
		//glDrawElements(GL_LINE_STRIP, g_indices.size(), GL_UNSIGNED_INT, 0);
		glFlush();
		CHECKERR();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	

	void onkeyboard(int key, int x, int y) {
		if (key == GLUT_KEY_RIGHT) {
			g_zoffset += 10.0f;
		}
		else if (key == GLUT_KEY_LEFT) {
			g_zoffset -= 10.0f;
		}
		else if (key == GLUT_KEY_UP) {
			g_xoffset += 10.f;
		}
		else if (key == GLUT_KEY_DOWN) {
			g_xoffset -= 10.f;
		}
	}
}