#pragma once
#include "GL\glew.h"
#include "TestSphere.h"
#include "vmath.h"
#include "TestJpeg.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/rotate_vector.hpp>

namespace TestLight {
	static const char* g_vString = R"(
#version 430 core
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 vertexTexCoord;
layout(location=2) in vec3 vertexNormal;
layout(location=3) uniform mat4 viewMatrix;
layout(location=4) uniform int type;
layout(location=5) uniform vec3 vertexLightColor;
layout(location=7) uniform mat4 projectionMatrix;
layout(location=8) uniform mat4 modelMatrix;
out vec2 texCoord;
out vec3 lightColor;
out vec3 esNormal;
out vec4 esPosition;
flat out int esType;

void main(){
	esPosition = viewMatrix * vec4(vertexPosition, 1.0f);
	gl_Position = projectionMatrix * modelMatrix * viewMatrix * vec4(vertexPosition, 1.0f);
	texCoord = vertexTexCoord;
	lightColor = vertexLightColor;
	vec4 tmpNormal = viewMatrix * vec4(vertexNormal, 1.0f);
	esNormal = tmpNormal.xyz;
	esType = type;
}
)";

	static const char* g_fString = R"(
#version 430 core
layout(location=10) uniform sampler2D tex;
layout(location=11) uniform vec3 lightPosition;//光源方向
layout(location=12) uniform vec3 eyePositon;
layout(location=13) uniform vec3 ambient;	//光照等级
layout(location=14) uniform float strength;//调整光泽度数据
layout(location=15) uniform float shininess;//高光尖锐指数
in vec2 texCoord;
in vec3 lightColor;
in vec3 esNormal;
in vec4 esPosition;
flat in int esType;
out vec4 fColor;
void main(){
	vec4 texColor = texture2D(tex, texCoord);
	if (1 == esType){
		//混合光源颜色和材质颜色
		vec3 rgb = min(texColor.rgb * lightColor, vec3(1.0f, 1.0f, 1.0f));
		fColor = vec4(rgb, texColor.a);
	}else if (2 == esType){
		//增加法向量
		vec3 lightDirect = normalize(lightPosition - esPosition.xyz);
		float diffuse = max(0.0, dot(esNormal, lightDirect));
		if (diffuse == 0.0){
			fColor = vec4(0.0f,0.0,0.0,1.0);
		}else{
			vec4 tmpTexColor = texColor * diffuse;
			fColor = vec4(min(tmpTexColor.rgb * lightColor, vec3(1.0f, 1.0f, 1.0f)), 1.0f);
		}
	}else if (3 == esType){
		vec3 lightDirect = normalize(lightPosition - esPosition.xyz);
		vec3 eyeDirect = normalize(eyePositon - esPosition.xyz);
		vec3 halfVector = normalize(lightDirect + eyeDirect);
		float diffuse = max(0.0, dot(esNormal, lightDirect));
		float specular = max(0.0, dot(esNormal, halfVector));

		if (diffuse == 0.0){
			specular = 0.0f;
		}else{
			specular = pow(specular, shininess);
		}
		
		vec3 scatteredLight = ambient + lightColor * diffuse;//散射光
		vec3 reflectedLight = lightColor * specular * strength;//反射光

		vec3 rgb = min(texColor.rgb * scatteredLight + reflectedLight, vec3(1.0f));
		fColor = vec4(rgb, texColor.a);
	}
}
)";
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
	static GLfloat g_xcameraoffset = 0.f;
	static GLfloat g_ycameraoffset = 0.f;
	static GLfloat g_zcameraoffset = 0.f;

	void init() {
		g_program = glCreateProgram();
		OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, g_vString, 0);
		OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_program);
		OpenGLHelper::outputProgramLog(g_program);
		CHECKERR();

		TestSphere::buildVertices(50, 50, g_vertexs, g_texcoords, g_normals, g_indices);

		auto iterVertex = g_vertexs.begin(), iterTex = g_texcoords.begin(), iterNormal = g_normals.begin();
		while (iterVertex != g_vertexs.end() && iterTex != g_texcoords.end() && iterNormal != g_normals.end()) {
			g_allvertexs.push_back(*(iterVertex++));
			g_allvertexs.push_back(*(iterVertex++));
			g_allvertexs.push_back(*(iterVertex++));

			g_allvertexs.push_back(*(iterTex++));
			g_allvertexs.push_back(*(iterTex++));

			g_allvertexs.push_back(*(iterNormal++));
			g_allvertexs.push_back(*(iterNormal++));
			g_allvertexs.push_back(*(iterNormal++));
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
		GLuint vertexPositionLocation = glGetAttribLocation(g_program, "vertexPosition");
		glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vertexPositionLocation);
		GLuint vertexTexCoordLocation = glGetAttribLocation(g_program, "vertexTexCoord");
		glVertexAttribPointer(vertexTexCoordLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(vertexTexCoordLocation);
		GLuint vertexNormalLocation = glGetAttribLocation(g_program, "vertexNormal");
		glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(vertexNormalLocation);
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

		glm::vec3 tmpEye = glm::vec3(0.f, -2.0f, 0.0f);
		tmpEye = glm::rotateZ(tmpEye, glm::radians(g_zcameraoffset));//旋转相机的位置
		glm::vec3 normalEye = glm::normalize(tmpEye);
		//vmath::vec3 eye = vmath::vec3(0.f, -2.0f, 0.0f);
		vmath::vec3 eye = vmath::vec3(tmpEye[0], tmpEye[1], tmpEye[2]);
		vmath::vec3 center = vmath::vec3(0.f, 0.f, 0.f);
		vmath::vec3 up = vmath::vec3(0.f, 0.f, 1.f);
		vmath::mat4 viewMatrix = vmath::rotate(0.f, 0.f, g_zoffset);//旋转球
		float fovy = 45.f;
		float aspect = 1.0f / 1.0f;//width/height
		float n = 0.5f, f = 10.f;
		//设置相机照射的范围，长宽比率，近点与远点值
		vmath::mat4 cameraLookAt = vmath::lookat(eye, center, up);//设置相机位置，朝向，与相机上部的方向
		vmath::mat4 cameraPerspective = vmath::perspective(fovy, aspect, n, f);// vmath::perspective(fovy, aspect, 0.1f, 100.f);
		vmath::mat4 projectionMatrix = cameraPerspective;
		vmath::mat4 modelMatrix = cameraLookAt;
		GLuint viewMatrixLocation = glGetUniformLocation(g_program, "viewMatrix");
		glProgramUniformMatrix4fv(g_program, viewMatrixLocation, 1, GL_FALSE, viewMatrix);
		GLuint modelMatrixLocation = glGetUniformLocation(g_program, "modelMatrix");
		glProgramUniformMatrix4fv(g_program, modelMatrixLocation, 1, GL_FALSE, modelMatrix);
		GLuint projectionMatrixLocation = glGetUniformLocation(g_program, "projectionMatrix");
		glProgramUniformMatrix4fv(g_program, projectionMatrixLocation, 1, GL_FALSE, projectionMatrix);
		GLuint typeLocation = glGetUniformLocation(g_program, "type");
		GLint type = 3;
		glProgramUniform1i(g_program, typeLocation, type);
		CHECKERR();

		glm::vec3 lightPosition(1.0, -1.0f, 1.0f);
		GLuint lightPositonLocation = glGetUniformLocation(g_program, "lightPosition");
		glProgramUniform3f(g_program, lightPositonLocation, lightPosition.x, lightPosition.y, lightPosition.z);
		CHECKERR();

		GLuint eyePositonLocation = glGetUniformLocation(g_program, "eyePositon");
		glProgramUniform3f(g_program, eyePositonLocation, tmpEye.x, tmpEye.y, tmpEye.z);

		glm::vec3 ambient = glm::vec3(1.0f, 1.0f, 1.0f) * 0.1f;//环境光照等级
		GLuint ambientLocation = glGetUniformLocation(g_program, "ambient");
		glProgramUniform3f(g_program, ambientLocation, ambient.r, ambient.g, ambient.b);
		CHECKERR();
		

		float strength = 0.5f;//光泽度倍数调整值
		GLuint strengthLocation = glGetUniformLocation(g_program, "strength");
		glProgramUniform1f(g_program, strengthLocation, strength);
		CHECKERR();

		float shininess = 10.0f;//光泽度指数
		GLuint shininessLocation = glGetUniformLocation(g_program, "shininess");
		glProgramUniform1f(g_program, shininessLocation, shininess);
		CHECKERR();

		GLuint lightColorLocation = glGetUniformLocation(g_program, "vertexLightColor");
		glProgramUniform3f(g_program, lightColorLocation, 1.0f, 1.f, 1.f);
		glDrawElements(GL_TRIANGLES, g_indices.size(), GL_UNSIGNED_INT, 0);
		glFlush();
		CHECKERR();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	static void onspecialkey(int key, int x, int y) {
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

	static void onkeyboard(int key, int x, int y) {
		if (key == 'a' || key == 'A') {
			g_zcameraoffset -= 10.f;
		}
		else if (key == 'd' || key == 'D') {
			g_zcameraoffset += 10.f;
		}
	}
}