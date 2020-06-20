#pragma once
#include "glsl.h"
#include <GL/glew.h>
#include <memory>
#include <Windows.h>
#include "OpenGLHelper.h"
#include "vmath.h"

namespace Test {


#define BUFFER_OFFSET(offset) ((void*)(offset))
	GLuint g_vIndex = 0;
	GLuint g_bIndex = 0, g_ebIndex = 0;
	GLuint g_program = 0;
	GLuint g_pipeline = 0;
	GLuint g_vprogram = 0, g_fprogram = 0;

	//#define USE_UCHAR_COLOR

	//初始化顶点数组
	GLfloat g_vPoints[][4] = {
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};
#ifdef USE_UCHAR_COLOR
	//使用unsigned char 类型值
	GLbyte g_colors[][4] = {
		{ 255, 0, 0， 255 },
		{ 0, 255, 0， 255 },
		{ 0, 0, 255， 255 },
	};
#else
	GLfloat g_colors[][4] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f,
	};

	GLushort g_indices[] = {
		0, 1, 2, 3, 6, 7, 4, 5,
		0xFFFF,
		2, 6, 0, 4,1, 5, 3, 7 };//元素索引
	void initBufferArray()
	{
#endif
		glGenBuffers(1, &g_bIndex);//生成1个buffer对象
		glBindBuffer(GL_ARRAY_BUFFER, g_bIndex);//激活buffer对象
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vPoints) + sizeof(g_colors), nullptr, GL_STATIC_DRAW);//分配空间

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vPoints), g_vPoints);//设置顶点坐标缓存

#if 0
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vPoints), sizeof(g_colors), g_colors);//设置顶点颜色缓存
#endif
#if 1
																						//也可以使用map形式设置
		GLboolean isOk = GL_FALSE;
		if (false) {
			void* mapBuf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			memcpy((char*)mapBuf + sizeof(g_vPoints), g_colors, sizeof(g_colors));
			isOk = glUnmapBuffer(GL_ARRAY_BUFFER);
		}
		else {
			//map range,GL_MAP_FLUSH_EXPLICIT_BIT:应用程序主动通知刷新区域
			void* mapBuf = glMapBufferRange(GL_ARRAY_BUFFER, sizeof(g_vPoints), sizeof(g_colors), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);
			memcpy(mapBuf, g_colors, sizeof(g_colors));
			glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, sizeof(g_colors));
			isOk = glUnmapBuffer(GL_ARRAY_BUFFER);
		}
#endif
		//GLfloat checkPoints[3 * 4 + 3 * 4] = { 0.0 };
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPoints) + sizeof(colors), checkPoints);//获取缓冲数据


		GLuint buf = GL_INVALID_INDEX;
		glGenBuffers(1, &g_ebIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);
		//glDeleteBuffers(1, &buf);
		if (false) {
			//丢弃缓存数据
			glInvalidateBufferData(g_bIndex);
		}
	}


	void initVertex()
	{
		glGenVertexArrays(1, &g_vIndex);//分配1个顶点数组对象
		glBindVertexArray(g_vIndex);//激活第一个顶点数组对象
		glBindBuffer(GL_ARRAY_BUFFER, g_bIndex);//使用g_bIndex
		GLuint vertexIn = 1;//顶点着色器中vPosition的位置index, 可以通过glGetAttribLocation(m_program, "vPosition");获取
		GLint perVertexPointCount = 4;//一个顶点的坐标数量，如：xyz,则是3
		GLsizei stride = 0;//连续顶点之间的偏移量
		GLboolean normalized = GL_FALSE;
		int offset = 0;// sizeof(GLfloat) * 2;//从第二个顶点坐标开始
		glVertexAttribPointer(vertexIn, perVertexPointCount, GL_FLOAT, normalized, stride, BUFFER_OFFSET(offset));//指定顶点属性的数据格式和位置
		glEnableVertexAttribArray(vertexIn);//启用顶点

		GLuint tVertexIn = 2;
		glVertexAttribPointer(tVertexIn, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vPoints)));//指定颜色顶点的偏移
		glEnableVertexAttribArray(tVertexIn);//启用顶点
	}
#define USE_PIPELINE

#ifdef USE_PIPELINE
	void initProgram()
	{
		g_vprogram = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vString);
		g_fprogram = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fString);
		glGenProgramPipelines(1, &g_pipeline);
	}
#else
	void initProgram()
	{
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vShader, 1, &vString, nullptr);
		glShaderSource(fShader, 1, &fString, nullptr);

		glCompileShader(vShader);
		outputCompileShader(vShader);
		glCompileShader(fShader);
		outputCompileShader(fShader);
		CHECKERR();

		g_program = glCreateProgram();

		glAttachShader(g_program, vShader);
		CHECKERR();
		glAttachShader(g_program, fShader);
		CHECKERR();

		glLinkProgram(g_program);
		outputProgramLog(g_program);

		glDeleteShader(vShader);
		glDeleteShader(fShader);

		glUseProgram(g_program);
	}
#endif

	size_t TypeSize(GLenum type)
	{
		size_t size = 0;
#define CASE(Enum, Count, Type) \
case Enum:size = Count * sizeof(Type);break;
		switch (type) {
			CASE(GL_FLOAT, 1, GLfloat);
			CASE(GL_FLOAT_VEC2, 2, GLfloat);
			CASE(GL_FLOAT_VEC3, 3, GLfloat);
			CASE(GL_FLOAT_VEC4, 4, GLfloat);
			CASE(GL_INT, 1, GLint);
			CASE(GL_INT_VEC2, 2, GLint);
			CASE(GL_INT_VEC3, 3, GLint);
			CASE(GL_INT_VEC4, 4, GLint);
			CASE(GL_UNSIGNED_INT, 1, GLuint);
			CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
			CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
			CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);
			CASE(GL_BOOL, 1, GLboolean);
			CASE(GL_BOOL_VEC2, 2, GLboolean);
			CASE(GL_BOOL_VEC3, 3, GLboolean);
			CASE(GL_BOOL_VEC4, 4, GLboolean);
			CASE(GL_FLOAT_MAT2, 4, GLfloat);
			CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
			CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
			CASE(GL_FLOAT_MAT3, 9, GLfloat);
			CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
			CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
			CASE(GL_FLOAT_MAT4, 16, GLfloat);
			CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
			CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE
		default:
			printf("unknown type:%d\n", type);
			break;
		}

		return size;
	}

	void initUniform(GLuint program)
	{
		GLint myMatrix = glGetUniformLocation(program, "myMatrix");//获取translationMatrix的位置
		CHECKERR();
		//glProgramUniform3f(program, myLocation, 0.3, 0.6, 1.0);
#if 1
		static int i = 500;
		i += 30;
		float t = float(i & 0x1FFF) / float(0x1FFF);
		static float q = 0.0f;
		static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
		static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
		static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

		vmath::mat4 translateMatrix = vmath::translate(1.0f, 0.0f, 0.0f);//移动
		vmath::mat4 scaleMatrix = vmath::scale(0.4f, 0.8f, 1.0f);
		vmath::mat4 rotateMatrix = vmath::rotate(0.0f, 0.0f, 90.0f);//旋转
		vmath::mat4 standardMatrix = vmath::mat4(
			vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		//translateMatrix * rotateMatrix，先旋转，后平移
		float aspect = 1.0f; //height/width
		vmath::mat4 model_matrix(vmath::translate(0.0f, 0.0f, -5.0f) * vmath::rotate(t * 360.0f, Y) * vmath::rotate(t * 720.0f, Z));
		vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
		vmath::mat4 matrix = standardMatrix;
#else
		GLfloat matrix[16] = {
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.5, 0.0, 0.0, 1.0,
		};
#endif
		glProgramUniformMatrix4fv(program, myMatrix, 1, GL_FALSE, matrix);//使用glUniformMatrix4fv，必须先glUseProgram(program)
		CHECKERR();

		//获取uniform 块索引
		GLuint blockIndex = glGetUniformBlockIndex(program, "MyTest");

		//获取uniform块大小
		GLint uboSize = 0;
		glGetActiveUniformBlockiv(program, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
		//分配缓冲区
		GLvoid* buffer = malloc(uboSize);
		memset(buffer, 0, uboSize);

		const int NUM = 2;
		const char* ppNames[NUM] = { "isReverse", "isGradual" };
		GLuint itemIndexs[NUM] = { GL_INVALID_INDEX, GL_INVALID_INDEX };
		GLint size[NUM];
		GLint offset[NUM];
		GLint type[NUM];
		//获取每个item的index
		glGetUniformIndices(program, 2, ppNames, itemIndexs);
		//获取item的大小
		glGetActiveUniformsiv(program, NUM, itemIndexs, GL_UNIFORM_SIZE, size);
		//获取item的缓冲区偏移
		glGetActiveUniformsiv(program, NUM, itemIndexs, GL_UNIFORM_OFFSET, offset);
		//获取item类型
		glGetActiveUniformsiv(program, NUM, itemIndexs, GL_UNIFORM_TYPE, type);
		GLboolean values[NUM] = { GL_TRUE, GL_TRUE };
		for (int i = 0; i < NUM; i++)
		{
			memcpy((char*)buffer + offset[i], &values[i], size[i] * TypeSize(type[i]));
		}

		//生成一个UNIFORM buffer
		GLuint ubo = -1;
		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);
		//用uniform buffer来为uniform设值
		glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, ubo);
		free(buffer);

		glUseProgram(0);
	}

	//GLuint g_texture = 0;

	void init()
	{
		initBufferArray();
		initVertex();
		initProgram();

		//glEnable(GL_SAMPLE_SHADING);
		//glMinSampleShading(1.0);

		//启用剪切
		if (false) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(100, 100, 200, 200);
		}

		//启用反走样
		if (false)
		{
			glEnable(GL_POLYGON_SMOOTH);//启用多边形平滑
			glEnable(GL_BLEND);	//启用混合
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		}
		//charToTexture(L"Hello, world");

		//设置清除颜色
		glClearColor(1.0, 1.0, 1.0, 1.0);
	}

	typedef struct DrawArraysIndirectCommand {
		GLuint count;
		GLuint primCount;
		GLuint first;
		GLuint baseInstance;
	};

	void testdraw()
	{
#ifdef USE_PIPELINE
		initUniform(g_vprogram);
		glUseProgramStages(g_pipeline, GL_VERTEX_SHADER_BIT, g_vprogram);
		glUseProgramStages(g_pipeline, GL_FRAGMENT_SHADER_BIT, g_fprogram);
		glBindProgramPipeline(g_pipeline);
#else
		initUniform(g_program);
#endif

		//glEnable(GL_CULL_FACE);
		//glDisable(GL_DEPTH_TEST);

		glPointSize(15.0);//只对点生效
		glLineWidth(15.0);//只对线生效

		glBindVertexArray(g_vIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebIndex);
		glBindBuffer(GL_ARRAY_BUFFER, g_bIndex);

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(0xFFFF);

		int drawType = 1;
		switch (drawType) {
		case 0:
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
			break;
		case 1: {
			//如果有变量bind到GL_ELEMENT_ARRAY_BUFFER，则indices是offset bytes 缓冲区
			//否则是pointer to indices
#if 0
			if (0) {
				glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, BUFFER_OFFSET(sizeof(GLushort) * 1));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			else {
				glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, g_indices);
			}
#endif
			glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, 0);
		}
				break;
		case 2: {
			GLint basevertex = 1;
			//与glDrawElements类似，元素index为indices[i + basevertex];
			glDrawElementsBaseVertex(GL_LINES, 4, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0), basevertex);
		}
				break;
		case 3: {
			//glDrawRangeElements(GL_LINES, 3, 4, 2, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
		}break;
		case 4: {
			//绘制primcount次，GLSL中gl_InstanceID会依次递增
			GLsizei primcount = 4;
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 3, primcount);
		}break;
		case 5: {
			DrawArraysIndirectCommand cmd;
			cmd.count = 4;
			cmd.first = 1;
			cmd.primCount = 4;
			cmd.baseInstance = 0;
			GLuint buf;
			glGenBuffers(1, &buf);
			glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buf);
			glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd), &cmd, GL_STATIC_DRAW);
			glDrawArraysIndirect(GL_LINES, BUFFER_OFFSET(0));
			glDeleteBuffers(1, &buf);
		}break;
		case 6: {
			GLint firsts[] = { 0, 2 };
			GLint counts[] = { 3, 3 };
			GLsizei drawcount = _countof(firsts);
			glMultiDrawArrays(GL_LINE_STRIP, firsts, counts, drawcount);
		}break;
		default:
			break;
		}
		glFlush();
	}

	void myIdle() {
		static DWORD t = 0;
		DWORD tCur = GetTickCount();
		if (tCur - t > 30)
		{
			t = tCur;
			testdraw();
		}
	}
};