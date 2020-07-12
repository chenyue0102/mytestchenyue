#pragma once
#include <stdio.h>
#include <assert.h>
#include <string>
#include "jpeg/jpeglib.h"
#include "TestFrameBuffer.h"

namespace TestJpeg {

	struct my_error_mgr {
		struct jpeg_error_mgr pub;	/* "public" fields */

		jmp_buf setjmp_buffer;	/* for return to caller */
	};
	typedef struct my_error_mgr * my_error_ptr;
	METHODDEF(void)
		my_error_exit(j_common_ptr cinfo)
	{
		/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
		my_error_ptr myerr = (my_error_ptr)cinfo->err;

		/* Always display the message. */
		/* We could postpone this until after returning, if we chose. */
		(*cinfo->err->output_message) (cinfo);

		/* Return control to the setjmp point */
		longjmp(myerr->setjmp_buffer, 1);
	}

	static bool getJpgInfo(const char* filePath, int* width, int* height, int* channelCount) {
		jpeg_decompress_struct cinfo;
		my_error_mgr jerr;
		bool cleanJpeg = false;
		FILE* f = NULL;
		bool success = false;

		do
		{
			if (NULL == (f = fopen(filePath, "rb"))) {
				assert(false);
				break;
			}
			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = &my_error_exit;
			if (0 != setjmp(jerr.setjmp_buffer)) {
				break;
			}
			jpeg_create_decompress(&cinfo);
			cleanJpeg = true;

			jpeg_stdio_src(&cinfo, f);
			jpeg_read_header(&cinfo, TRUE);
			if (NULL != width) {
				*width = cinfo.image_width;
			}
			if (NULL != height) {
				*height = cinfo.image_height;
			}
			if (NULL != channelCount) {
				*channelCount = cinfo.num_components;
			}
			success = true;
		} while (false);

		if (NULL != f) {
			fclose(f);
			f = NULL;
		}
		if (cleanJpeg) {
			jpeg_destroy_decompress(&cinfo);
		}
		return success;
	}

	static bool loadJpgImage(const char* filePath, bool startBottom, void* buffer, int bufferLen, int* width, int* height, int* channelCount) {
		jpeg_decompress_struct cinfo;
		my_error_mgr jerr;
		bool cleanJpeg = false;
		FILE* f = NULL;
		bool success = false;

		do
		{
			if (NULL == (f = fopen(filePath, "rb"))) {
				assert(false);
				break;
			}
			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = &my_error_exit;
			if (0 != setjmp(jerr.setjmp_buffer)) {
				break;
			}
			jpeg_create_decompress(&cinfo);
			cleanJpeg = true;

			jpeg_stdio_src(&cinfo, f);
			jpeg_read_header(&cinfo, TRUE);
			jpeg_start_decompress(&cinfo);

			int row_stride = cinfo.output_width * cinfo.output_components;//per row buffer
			if (NULL != width) {
				*width = cinfo.output_width;
			}
			if (NULL != height) {
				*height = cinfo.output_height;
			}
			if (NULL != channelCount) {
				*channelCount = cinfo.output_components;
			}
			if (bufferLen < static_cast<int>(row_stride * cinfo.output_height)) {
				break;
			}
			if (nullptr == buffer) {
				break;
			}
			if (JCS_RGB == cinfo.out_color_space) {
				while (cinfo.output_scanline < cinfo.output_height) {
					unsigned char* tmpBuffer = NULL;
					if (startBottom) {
						tmpBuffer = (unsigned char*)buffer + row_stride * cinfo.output_scanline;
					}
					else {
						tmpBuffer = (unsigned char*)buffer + row_stride * (cinfo.output_height - cinfo.output_scanline - 1);
					}
					//opengl起始为左下角,jpg从右上角开始
					jpeg_read_scanlines(&cinfo, &tmpBuffer, 1);
				}
			}
			jpeg_finish_decompress(&cinfo);
			success = true;
		} while (false);

		if (NULL != f) {
			fclose(f);
			f = NULL;
		}
		if (cleanJpeg) {
			jpeg_destroy_decompress(&cinfo);
		}
		return success;
	}

	static void* loadJpgImage(const char* filePath, bool startBottom, int* width, int* height, int* channelCount) {
		void* mapBuffer = NULL;
		bool success = false;
		int tmpWidth = 0, tmpHeight = 0, tmpChannelCount = 0;

		do
		{
			if (!getJpgInfo(filePath, &tmpWidth, &tmpHeight, &tmpChannelCount)) {
				assert(false);
				break;
			}
			int len = tmpWidth * tmpHeight * tmpChannelCount;
			if (NULL == (mapBuffer = malloc(len))) {
				assert(false);
				break;
			}
			if (!loadJpgImage(filePath, startBottom, mapBuffer, len, width, height, channelCount)) {
				assert(false);
				break;
			}
			success = true;
		} while (false);
		if (!success && NULL != mapBuffer) {
			free(mapBuffer);
			mapBuffer = NULL;
		}
		return mapBuffer;
	}

	static void freeImage(void* buffer) {
		free(buffer);
	}

	//startBottom结果图片从左下角开始,否则从左上角开始
	static bool loadJpg2Texture(const char *filePath, bool startBottom, GLenum internalformat, GLuint *tex, GLsizei *width, GLsizei *height) {
		bool success = false;
		jpeg_decompress_struct cinfo;
		my_error_mgr jerr;
		bool cleanJpeg = false, cleanTex = false, cleanUnpackBuffer = false;;
		FILE *f = NULL;
		GLenum ret = GL_NO_ERROR;
		GLuint unpackBuffer = 0;

		do
		{
			if (NULL == tex) {
				assert(false);
				break;
			}
			if (NULL == (f = fopen(filePath, "rb"))) {
				assert(false);
				break;
			}
			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = &my_error_exit;
			if (0 != setjmp(jerr.setjmp_buffer)) {
				break;
			}
			jpeg_create_decompress(&cinfo);
			cleanJpeg = true;

			jpeg_stdio_src(&cinfo, f);
			jpeg_read_header(&cinfo, TRUE);
			jpeg_start_decompress(&cinfo);

			int row_stride = cinfo.output_width * cinfo.output_components;//per row buffer
			if (NULL != width) {
				*width = cinfo.output_width;
			}
			if (NULL != height) {
				*height = cinfo.output_height;
			}
			if (JCS_RGB == cinfo.out_color_space) {
				glGenBuffers(1, &unpackBuffer); CHECK_BREAK;
				cleanUnpackBuffer = true;
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, unpackBuffer); CHECK_BREAK;
				glBufferData(GL_PIXEL_UNPACK_BUFFER, row_stride * cinfo.output_height, nullptr, GL_STATIC_DRAW); CHECK_BREAK;
				unsigned char *mapBuffer = (unsigned char*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY); CHECK_BREAK;
				if (nullptr == mapBuffer) {
					break;
				}
				while (cinfo.output_scanline < cinfo.output_height){
					unsigned char* buffer = NULL;
					if (startBottom) {
						buffer = mapBuffer + row_stride * cinfo.output_scanline;
					}
					else {
						buffer = mapBuffer + row_stride * (cinfo.output_height - cinfo.output_scanline - 1);
					}
					//opengl起始为左下角,jpg从右上角开始
					jpeg_read_scanlines(&cinfo, &buffer, 1);
				}
				GLboolean isOk = glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
				if (isOk != GL_TRUE) {
					break;
				}
				
				glGenTextures(1, tex); CHECK_BREAK;
				cleanTex = true;
				glBindTexture(GL_TEXTURE_2D, *tex); CHECK_BREAK;
				glTexImage2D(GL_TEXTURE_2D, 0, internalformat, cinfo.output_width, cinfo.output_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr); CHECK_BREAK;
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, cinfo.output_width, cinfo.output_height, GL_RGB, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			jpeg_finish_decompress(&cinfo);
			if (ret != GL_NO_ERROR) {
				break;
			}
			success = true;
		} while (false);

		if (NULL != f) {
			fclose(f);
			f = NULL;
		}
		if (cleanJpeg) {
			jpeg_destroy_decompress(&cinfo);
		}
		if (ret != GL_NO_ERROR && cleanTex) {
			glDeleteTextures(1, tex);
		}
		if (cleanUnpackBuffer) {
			glDeleteBuffers(1, &unpackBuffer);
		}
		return success;
	}

	static void testload() {
		jpeg_decompress_struct cinfo;
		my_error_mgr jerr;
		FILE *f = NULL;
		bool cleanJpeg = false;
		std::string data;
		do
		{
			if (NULL == (f = fopen("d:/1.jpg", "rb"))) {
				assert(false);
				break;
			}
			cinfo.err = jpeg_std_error(&jerr.pub);
			jerr.pub.error_exit = &my_error_exit;
			if (0 != setjmp(jerr.setjmp_buffer)) {
				break;
			}
			jpeg_create_decompress(&cinfo);
			cleanJpeg = true;
			jpeg_stdio_src(&cinfo, f);
			jpeg_read_header(&cinfo, TRUE);
			jpeg_start_decompress(&cinfo);
			int row_stride = cinfo.output_width * cinfo.output_components;//per row buffer
			//data.resize(row_stride * info.output_height);
			//jpeg_read_scanlines(&info, (JSAMPARRAY)&data[0], info.output_height);
			JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
				((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
			//JSAMPARRAY buffer = (JSAMPARRAY)malloc(row_stride);
			//std::string tmpBuffer;
			//tmpBuffer.resize(row_stride);
			//unsigned char *buffer = (unsigned char *)tmpBuffer.data();
			data.resize(row_stride * cinfo.output_height);
			while (cinfo.output_scanline < cinfo.output_height) {
				char *poffset = &data[0] + (row_stride * (cinfo.output_height - cinfo.output_scanline - 1));
				jpeg_read_scanlines(&cinfo, buffer, 1);
				switch (cinfo.out_color_space) {
				case JCS_RGB: {
					for (int i = 0; i < row_stride; i += 3) {
						//BMP为BGR顺序，这里解出来是RGB顺序
						unsigned char r = buffer[0][i];
						unsigned char g = buffer[0][i + 1];
						unsigned char b = buffer[0][i + 2];
						buffer[0][i + 2] = r;
						buffer[0][i] = b;
					}
					//BMP存储为：图片的左下角起始，右上角结束
					//这里为左上角起始，右下角结束，
					//需要转换下
					memcpy(poffset, buffer[0], row_stride);
				}
					break;
				case JCS_GRAYSCALE:
					break;
				case JCS_CMYK:
					break;
				default:
					printf("out_color_space not support:%d\n", cinfo.out_color_space);
					break;
				}
			}
			OpenGLHelper::SaveBitmap("d:/1.bmp", cinfo.output_width, cinfo.output_height, cinfo.output_components * 8, data.data(), data.size());
			jpeg_finish_decompress(&cinfo);
		} while (false);
		
		if (NULL != f) {
			fclose(f);
			f = nullptr;
		}
		if (cleanJpeg) {
			jpeg_destroy_decompress(&cinfo);
		}

	}
}