#pragma once
#include <GL\glew.h>
#include "OpenGLHelper.h"
#include "TestJpeg.h"
#include <vector>
#include "vmath.h"

namespace TestNormalMapping {
	static const char *g_vString = R"(
#version 430 core
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 vertexTexCoord;
layout(location=2) in vec3 vertexNormal;
layout(location=3) in vec3 vertexTangent;
layout(location=4) in vec3 vertexBitangent;
layout(location=5) uniform mat4 viewMatrix;
layout(location=6) uniform mat4 modelMatrix;
layout(location=7) uniform mat4 projectionMatrix;
layout(location=8) uniform vec3 vertexLightPosition;
layout(location=9) uniform int type;


out vec2 texCoord;
out vec4 esPosition;
out mat3 TBN;
out flat int esType;
out vec3 lightPosition;

void main(){
	esType = type;
	texCoord = vertexTexCoord;
	esPosition = viewMatrix * vec4(vertexPosition, 1.0f);
	gl_Position = projectionMatrix * modelMatrix * esPosition;
	lightPosition = vertexLightPosition;
	vec3 T = normalize(vec3(modelMatrix * viewMatrix * vec4(vertexTangent, 0.0)));
	vec3 B = normalize(vec3(modelMatrix * viewMatrix * vec4(vertexBitangent, 0.0)));
	vec3 N = normalize(vec3(modelMatrix * viewMatrix * vec4(vertexNormal, 0.0)));
	TBN = mat3(T, B, N);
}
)";
	static const char *g_fString = R"(
#version 430 core
layout(location=10) uniform sampler2D tex;
layout(location=11) uniform sampler2D normalMap;
layout(location=12) uniform vec3 eyePositon;
layout(location=13) uniform float constantAttenuation;//固定衰减系数
layout(location=14) uniform float linearAttenuation;//线性衰减系数
layout(location=15) uniform float quadraticAttenuation;//二次衰减系数

in vec2 texCoord;
in vec4 esPosition;
in mat3 TBN;
in flat int esType;
in vec3 lightPosition;

out vec4 fColor;
void main(){
	vec4 texColor = texture2D(tex, texCoord);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	if (0 == esType){
		fColor = vec4(texColor.rgb, 1.0);
	}else if (1 == esType){
		vec3 normal = texture(normalMap, texCoord).rgb;
		normal = normal * 2.0 - 1.0;
	
		vec3 lightDirect = normalize(lightPosition - esPosition.xyz);
		float diffuse = max(0.0, dot(normal, lightDirect));
		
		if (0.0 == diffuse){
			fColor = vec4(0.0f,0.0,0.0,1.0);
		}else{
			vec4 tmpTexColor = texColor * diffuse;
			fColor = vec4(min(tmpTexColor.rgb * lightColor, vec3(1.0f, 1.0f, 1.0f)), 1.0f);
		}
	}else if (2 == esType){
		float lightDistance = length(lightPosition - esPosition.xyz);//光源到顶点的距离
		vec3 lightDirect = normalize(lightPosition - esPosition.xyz);
		vec3 eyeDirect = normalize(eyePositon - esPosition.xyz);
		vec3 halfVector = normalize(lightDirect + eyeDirect);
		

		vec3 normal = texture(normalMap, texCoord).rgb;
		normal = normalize(normal * 2.0 - 1.0);
		normal = normalize(TBN * normal);

		float tmpValue = (constantAttenuation + linearAttenuation * lightDistance + quadraticAttenuation * lightDistance * lightDistance);
		float attenuation = tmpValue > 0.0f ? 1.0 / tmpValue : 1.0f ;

		float diffuse = max(0.0, dot(normal, lightDirect));
		float specular = max(0.0, dot(normal, halfVector));
		
		if (diffuse == 0.0){
			specular = 0.0f;
		}else{
			specular = pow(specular, 20.0f);
		}
		
		// ambient
		vec3 ambient = vec3(1.0f, 1.0f, 1.0f) * 0.1;
		float strength = 0.5f;

		vec3 scatteredLight = ambient + lightColor * diffuse * attenuation;//散射光
		vec3 reflectedLight = lightColor * specular * strength * attenuation;//反射光

		vec3 rgb = min(texColor.rgb * scatteredLight + reflectedLight, vec3(1.0f));
		fColor = vec4(rgb, texColor.a);
	}
}
)";

	static GLuint g_vertex;
	static GLuint g_texture;
	static GLuint g_texturenormal;
	static GLuint g_vbuffer;
	static GLuint g_program;

	static GLfloat g_xoffset = 0.f;
	static GLfloat g_yoffset = 0.f;
	static GLfloat g_zoffset = 0.f;
	static GLfloat g_xcameraoffset = 0.f;
	//static GLfloat g_ycameraoffset = -30.f;
	static GLfloat g_ycameraoffset = 0.f;
	static GLfloat g_zcameraoffset = 0.f;

	static void init() {
		g_program = glCreateProgram();
		OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, g_vString, 0);
		OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, g_fString, 0);
		glLinkProgram(g_program);
		OpenGLHelper::outputProgramLog(g_program);
		CHECKERR();

		GLfloat vertexs[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
		};
		GLfloat texUV[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
		};

		GLfloat normals[] = {
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
		};

		glm::vec3 vpos1(vertexs[0], vertexs[1], vertexs[2]);
		glm::vec3 vpos2(vertexs[3], vertexs[4], vertexs[5]);
		glm::vec3 vpos3(vertexs[6], vertexs[7], vertexs[8]);
		glm::vec2 uv1(texUV[0], texUV[1]);
		glm::vec2 uv2(texUV[2], texUV[3]);
		glm::vec2 uv3(texUV[4], texUV[5]);
		glm::vec3 normal(normals[0], normals[1], normals[2]);

		normal = glm::rotateY(normal, glm::radians(g_ycameraoffset));//旋转相机的位置,正值顺时针，负值逆时针
		for (int i = 0; i < 3; i++) {
			normals[i * 3 + 0] = normal.x;
			normals[i * 3 + 1] = normal.y;
			normals[i * 3 + 2] = normal.z;
		}

		glm::vec3 tangent, bitangent;
		OpenGLHelper::getTangent<glm::vec2, glm::vec3>(vpos1, vpos2, vpos3, uv1, uv2, uv3, normal, tangent, bitangent);
		
		GLfloat tangentVertex[3 * 3] = {
			tangent.x, tangent.y, tangent.z,
			tangent.x, tangent.y, tangent.z,
			tangent.x, tangent.y, tangent.z,
		};
		GLfloat bitangentVertex[3 * 3] = {
			bitangent.x, bitangent.y, bitangent.z,
			bitangent.x, bitangent.y, bitangent.z,
			bitangent.x, bitangent.y, bitangent.z,
		};

		int width, height, channel;
		//glGenTextures(1, &g_texture);
		bool success = TestJpeg::genTextureAndLoadJpg("brickwall.jpg", false, GL_RGB, &g_texture, &width, &height, &channel);
		assert(success);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		CHECKERR();

		//glGenTextures(1, &g_texturenormal);
		success = TestJpeg::genTextureAndLoadJpg("brickwall_normal.jpg", false, GL_RGB, &g_texturenormal, &width, &height, NULL);
		//success = TestJpeg::genTextureAndLoadJpg("normal.jpg", false, GL_RGB, &g_texturenormal, &width, &height, NULL);
		assert(success);
		glBindTexture(GL_TEXTURE_2D, g_texturenormal);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		CHECKERR();

		glBindTexture(GL_TEXTURE_2D, 0);

		glGenBuffers(1, &g_vbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs) + sizeof(texUV) + sizeof(normals) + sizeof(tangentVertex) + sizeof(bitangentVertex), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexs), vertexs);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexs), sizeof(texUV), texUV);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexs) + sizeof(texUV), sizeof(normals), normals);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexs) + sizeof(texUV) + sizeof(normals), sizeof(tangentVertex), tangentVertex);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexs) + sizeof(texUV) + sizeof(normals) + sizeof(tangentVertex), sizeof(bitangentVertex), bitangentVertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECKERR();

		glGenVertexArrays(1, &g_vertex);
		glBindVertexArray(g_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		GLuint vertexPositionLocation = glGetAttribLocation(g_program, "vertexPosition");
		glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glEnableVertexAttribArray(vertexPositionLocation);
		CHECKERR();
		GLuint vertexTexCoordLocation = glGetAttribLocation(g_program, "vertexTexCoord");
		glVertexAttribPointer(vertexTexCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexs)));
		glEnableVertexAttribArray(vertexTexCoordLocation);
		CHECKERR();
		GLuint vertexNormalLocation = glGetAttribLocation(g_program, "vertexNormal");
		glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexs) + sizeof(texUV)));
		glEnableVertexAttribArray(vertexNormalLocation);
		CHECKERR();
		GLuint vertexTangentLocation = glGetAttribLocation(g_program, "vertexTangent");
		glVertexAttribPointer(vertexTangentLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexs) + sizeof(texUV) + sizeof(normals)));
		glEnableVertexAttribArray(vertexTangentLocation);
		CHECKERR();
		GLuint vertexBitangentLocation = glGetAttribLocation(g_program, "vertexBitangent");
		glVertexAttribPointer(vertexBitangentLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexs) + sizeof(texUV) + sizeof(normals) + sizeof(tangentVertex)));
		glVertexAttribPointer(vertexBitangentLocation, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexs) + sizeof(texUV) + sizeof(normals)));
		glEnableVertexAttribArray(vertexBitangentLocation);
		CHECKERR();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	static void testdraw() {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glUseProgram(g_program);

		glBindVertexArray(g_vertex);
		glBindBuffer(GL_ARRAY_BUFFER, g_vbuffer);
		CHECKERR();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		GLuint texLocation = glGetUniformLocation(g_program, "tex");
		glUniform1i(texLocation, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, g_texturenormal);
		GLuint texnormalLocation = glGetUniformLocation(g_program, "normalMap");
		glUniform1i(texnormalLocation, 1);

		glProgramUniform1i(g_program, glGetUniformLocation(g_program, "type"), 2);

		vmath::mat4 standardMatrix = vmath::mat4(
			vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		glm::vec3 tmpEye = glm::vec3(0.f, 0.0f, 2.0f);
		tmpEye = glm::rotateY(tmpEye, glm::radians(g_ycameraoffset));//旋转相机的位置,正值顺时针，负值逆时针
		vmath::vec3 eye = vmath::vec3(tmpEye[0], tmpEye[1], tmpEye[2]);
		vmath::vec3 center = vmath::vec3(0.f, 0.f, 0.f);
		vmath::vec3 up = vmath::vec3(0.f, 1.f, 0.f);
		vmath::mat4 viewMatrix = vmath::rotate(0.f, g_yoffset, 0.f);//旋转物体
		float fovy = 90.f;
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
		GLuint eyePositonLocation = glGetUniformLocation(g_program, "eyePositon");
		glProgramUniform3f(g_program, eyePositonLocation, tmpEye.x, tmpEye.y, tmpEye.z);

		GLuint vertexLightPositionLocation = glGetUniformLocation(g_program, "vertexLightPosition");
		glProgramUniform3f(g_program, vertexLightPositionLocation, 1.f, 0.2f, 3.f);
		CHECKERR();

		float constantAttenuation = 0.2f;
		GLuint constantAttenuationLocation = glGetUniformLocation(g_program, "constantAttenuation");
		glProgramUniform1f(g_program, constantAttenuationLocation, constantAttenuation);
		CHECKERR();

		float linearAttenuation = 0.0 / 1.0f;
		GLuint linearAttenuationLocation = glGetUniformLocation(g_program, "linearAttenuation");
		glProgramUniform1f(g_program, linearAttenuationLocation, linearAttenuation);
		CHECKERR();

		float quadraticAttenuation = 0.1f / (1.0f * 1.0f);
		GLuint quadraticAttenuationLocation = glGetUniformLocation(g_program, "quadraticAttenuation");
		glProgramUniform1f(g_program, quadraticAttenuationLocation, quadraticAttenuation);
		CHECKERR();

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glFlush();

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);
		CHECKERR();
	}
}