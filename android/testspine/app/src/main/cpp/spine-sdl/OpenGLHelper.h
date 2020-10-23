#pragma once
#include <GL/glew.h>
#include <stdio.h>
#include <assert.h>

inline void CHECKERR() {
	int err = 0;
	if (GL_NO_ERROR != (err = glGetError())){
		assert(false);
		printf("glGetError=%d\n", err);
	}
}

#define BUFFER_OFFSET(offset) ((void*)(offset))

#define CHECK_BREAK \
	if (GL_NO_ERROR != (ret = glGetError())) { \
		printf("glGetError=%x\n", ret); \
		assert(false); \
		break; \
	}

namespace OpenGLHelper {
void outputCompileShader(GLuint shader);
void outputProgramLog(GLuint program);
bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen);
GLenum attachShader(GLuint program, GLenum type, const char *source, GLint len);
GLenum createTexture2D(GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint filterParam, GLuint& tex);
GLenum createArrayBuffer(const void* vertexPointsBuffer, GLsizei vlen, const void* colorPointsBuffer, GLsizei clen, GLuint& buf);

template<typename T>
T length(T x, T y, T z) {
	return (T)sqrt(x *x + y * y + z * z);
}

template<typename VEC3>
VEC3 normalize(const VEC3 &in) {
	auto l = length(in.x, in.y, in.z);
	return VEC3(in.x / l, in.y / l, in.z / l);
}


template<typename VEC2, typename VEC3>
static void getTangent(const VEC3 &vertexPos1, const VEC3 &vertexPos2, const VEC3 &vertexPos3,
	const VEC2 &uv1, const VEC2 &uv2, const VEC2 &uv3, const VEC3 &normal, VEC3 &tangent, VEC3 &bitangent) {
	VEC3 edge1 = vertexPos2 - vertexPos1;
	VEC3 edge2 = vertexPos3 - vertexPos1;
	VEC2 deltaUV1 = uv2 - uv1;
	VEC2 deltaUV2 = uv3 - uv1;
	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);//x
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);//y
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);//z
	tangent = normalize(tangent);

	bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);//x
	bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);//y
	bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);//z
	bitangent = normalize(bitangent);
}
};