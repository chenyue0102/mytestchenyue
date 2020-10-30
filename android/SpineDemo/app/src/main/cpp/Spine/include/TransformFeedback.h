#ifndef TransformFeedback_h_
#define TransformFeedback_h_
#include <stdint.h>
#include <assert.h>
#include <vector>
#ifdef WIN32
#include <GL/glew.h>
#else
#include <OpenGLES/ES3/gl.h>
#endif
#include "OpenGLESHelper.h"

class TransformFeedback {
public:
	TransformFeedback()
		: mBuffer(0)
		, mFeedbackObject(0)
		, mBufferBytes(0)
	{
		
	}
	~TransformFeedback() {
		destroy();
	}
public:
	bool init(GLuint program, const char *paramNames[], int count) {
		glTransformFeedbackVaryings(program, count, paramNames, GL_INTERLEAVED_ATTRIBS); 
		GLenum err = glGetError();
		assert(GL_NO_ERROR == err);
		return GL_NO_ERROR == err;
	}
	bool initBuffer(int bufferBytes) {
		GLenum err = GL_NO_ERROR;
		bool ret = false;
		do
		{
			mBufferBytes = bufferBytes;
			glGenBuffers(1, &mBuffer); CHECK_BREAK;
			glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, mBuffer); CHECK_BREAK;
			glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, bufferBytes, NULL, GL_STATIC_READ); CHECK_BREAK;
			glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0); CHECK_BREAK;

			glGenTransformFeedbacks(1, &mFeedbackObject); CHECK_BREAK;
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mFeedbackObject); CHECK_BREAK;
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mBuffer); CHECK_BREAK;
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
			glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
			ret = true;
		} while (false);
		return ret;
	}

	bool beginFeedback(GLenum drawType) {
		bool ret = false;
		GLenum err = GL_NO_ERROR;
		do
		{
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, mFeedbackObject); CHECK_BREAK;
			glBeginTransformFeedback(drawType); CHECK_BREAK;

			ret = true;
		} while (false);
		return ret;
	}

	bool endFeedBack() {
		bool ret = false;
		GLenum err = GL_NO_ERROR;
		do
		{
			glEndTransformFeedback(); CHECK_BREAK;
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0); CHECK_BREAK;
			ret = true;
		} while (false);
		return ret;
	}


	uint8_t* getTransformFeedback(int *size) {
		GLenum err = GL_NO_ERROR;
		uint8_t *retData = nullptr;
		do
		{
			glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, mBuffer); CHECK_BREAK;
			void *data = glMapBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mBufferBytes, GL_MAP_READ_BIT); CHECK_BREAK;
			if (nullptr == data) {
				assert(false);
				break;
			}
			mDataBuffer.resize(mBufferBytes);
			memcpy(mDataBuffer.data(), data, mBufferBytes);
			glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);
			glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0); CHECK_BREAK;
			retData = mDataBuffer.data();
			if (nullptr != size) {
				*size = mBufferBytes;
			}
		} while (false);
		return retData;
	}

	void destroy() {
		if (0 != mBuffer) {
			glDeleteBuffers(1, &mBuffer);
			mBuffer = 0;
		}
		if (0 != mFeedbackObject) {
			glDeleteTransformFeedbacks(1, &mFeedbackObject);
			mFeedbackObject = 0;
		}
	}
private:
	GLuint mBuffer;
	GLuint mFeedbackObject;
	int mBufferBytes;
	std::vector<uint8_t> mDataBuffer;
};

#endif
