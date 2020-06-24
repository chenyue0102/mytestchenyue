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

	static GLenum loadJpg2Texture(const char *filePath, GLuint &tex) {
		GLenum ret = GL_NO_ERROR;
		jpeg_decompress_struct cinfo;
		my_error_mgr jerr;
		bool cleanJpeg = false;
		FILE *f = NULL;
		std::string buffer;

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
			buffer.resize(row_stride);
			unsigned char *buffer = (unsigned char *)buffer.data();

		} while (false);

		if (NULL != f) {
			fclose(f);
			f = NULL;
		}
		if (cleanJpeg) {
			jpeg_destroy_decompress(&cinfo);
		}
		return ret;
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
			TestFrameBuffer::SaveBitmap("d:/1.bmp", cinfo.output_width, cinfo.output_height, cinfo.output_components * 8, data.data(), data.size());
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