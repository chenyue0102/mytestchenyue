#include "MyTexture.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "OpenGLESHelper.h"
#include "png.h"

static struct {
	int loaded;
	void *handle;
	png_infop(*png_create_info_struct) (png_const_structrp png_ptr);
	png_structp(*png_create_read_struct) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
	void(*png_destroy_read_struct) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);
	png_uint_32(*png_get_IHDR) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method);
	png_voidp(*png_get_io_ptr) (png_const_structrp png_ptr);
	png_byte(*png_get_channels) (png_const_structrp png_ptr, png_const_inforp info_ptr);
	png_uint_32(*png_get_PLTE) (png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette);
	png_uint_32(*png_get_tRNS) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans, int *num_trans, png_color_16p *trans_values);
	png_uint_32(*png_get_valid) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag);
	void(*png_read_image) (png_structrp png_ptr, png_bytepp image);
	void(*png_read_info) (png_structrp png_ptr, png_inforp info_ptr);
	void(*png_read_update_info) (png_structrp png_ptr, png_inforp info_ptr);
	void(*png_set_expand) (png_structrp png_ptr);
	void(*png_set_gray_to_rgb) (png_structrp png_ptr);
	void(*png_set_packing) (png_structrp png_ptr);
	void(*png_set_read_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);
	void(*png_set_strip_16) (png_structrp png_ptr);
	int(*png_set_interlace_handling) (png_structrp png_ptr);
	int(*png_sig_cmp) (png_const_bytep sig, png_size_t start, png_size_t num_to_check);
//#ifndef LIBPNG_VERSION_12
	jmp_buf* (*png_set_longjmp_fn) (png_structrp, png_longjmp_ptr, size_t);
//#endif
	png_structp(*png_create_write_struct) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
	void(*png_destroy_write_struct) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr);
	void(*png_set_write_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn);
	void(*png_set_IHDR) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type);
	void(*png_write_info) (png_structrp png_ptr, png_const_inforp info_ptr);
	void(*png_set_rows) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers);
	void(*png_write_png) (png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params);
	void(*png_set_PLTE) (png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette);

	void(*png_set_sig_bytes)(png_structrp png_ptr, int num_bytes);
	void(*png_init_io)(png_structrp png_ptr, png_FILE_p fp);
	png_size_t(*png_get_rowbytes)(png_const_structrp png_ptr,
		png_const_inforp info_ptr);
	png_bytepp(*png_get_rows)(png_const_structrp png_ptr,
		png_const_inforp info_ptr);
	void(*png_read_png)(png_structrp png_ptr, png_inforp info_ptr,
		int transforms, png_voidp params);
} lib;

#define FUNCTION_LOADER(FUNC, SIG) \
    lib.FUNC = (SIG) GetProcAddress((HMODULE)lib.handle, #FUNC); \
    if (lib.FUNC == NULL) { FreeLibrary((HMODULE)lib.handle); return -1; }

int InitPNG() {
	if (0 == lib.loaded) {
		lib.handle = LoadLibraryA("libpng16-16.dll");

		FUNCTION_LOADER(png_create_info_struct, png_infop(*) (png_const_structrp png_ptr))
			FUNCTION_LOADER(png_create_read_struct, png_structp(*) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn))
			FUNCTION_LOADER(png_destroy_read_struct, void(*) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr))
			FUNCTION_LOADER(png_get_IHDR, png_uint_32(*) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method))
			FUNCTION_LOADER(png_get_io_ptr, png_voidp(*) (png_const_structrp png_ptr))
			FUNCTION_LOADER(png_get_channels, png_byte(*) (png_const_structrp png_ptr, png_const_inforp info_ptr))
			FUNCTION_LOADER(png_get_PLTE, png_uint_32(*) (png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette))
			FUNCTION_LOADER(png_get_tRNS, png_uint_32(*) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans, int *num_trans, png_color_16p *trans_values))
			FUNCTION_LOADER(png_get_valid, png_uint_32(*) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag))
			FUNCTION_LOADER(png_read_image, void(*) (png_structrp png_ptr, png_bytepp image))
			FUNCTION_LOADER(png_read_info, void(*) (png_structrp png_ptr, png_inforp info_ptr))
			FUNCTION_LOADER(png_read_update_info, void(*) (png_structrp png_ptr, png_inforp info_ptr))
			FUNCTION_LOADER(png_set_expand, void(*) (png_structrp png_ptr))
			FUNCTION_LOADER(png_set_gray_to_rgb, void(*) (png_structrp png_ptr))
			FUNCTION_LOADER(png_set_packing, void(*) (png_structrp png_ptr))
			FUNCTION_LOADER(png_set_read_fn, void(*) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn))
			FUNCTION_LOADER(png_set_strip_16, void(*) (png_structrp png_ptr))
			FUNCTION_LOADER(png_set_interlace_handling, int(*) (png_structrp png_ptr))
			FUNCTION_LOADER(png_sig_cmp, int(*) (png_const_bytep sig, png_size_t start, png_size_t num_to_check))
//#ifndef LIBPNG_VERSION_12
			FUNCTION_LOADER(png_set_longjmp_fn, jmp_buf* (*) (png_structrp, png_longjmp_ptr, size_t))
//#endif
			FUNCTION_LOADER(png_create_write_struct, png_structp(*) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn))
			FUNCTION_LOADER(png_destroy_write_struct, void(*) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr))
			FUNCTION_LOADER(png_set_write_fn, void(*) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn))
			FUNCTION_LOADER(png_set_IHDR, void(*) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type))
			FUNCTION_LOADER(png_write_info, void(*) (png_structrp png_ptr, png_const_inforp info_ptr))
			FUNCTION_LOADER(png_set_rows, void(*) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers))
			FUNCTION_LOADER(png_write_png, void(*) (png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params))
			FUNCTION_LOADER(png_set_PLTE, void(*) (png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette))

			FUNCTION_LOADER(png_set_sig_bytes, void(*) (png_structrp png_ptr, int num_bytes))
			FUNCTION_LOADER(png_init_io, void(*) (png_structrp png_ptr, png_FILE_p fp))
			FUNCTION_LOADER(png_get_rowbytes, png_size_t(*) (png_const_structrp png_ptr,
				png_const_inforp info_ptr))
			FUNCTION_LOADER(png_get_rows, png_bytepp(*) (png_const_structrp png_ptr,
				png_const_inforp info_ptr))
			FUNCTION_LOADER(png_read_png, void(*) (png_structrp png_ptr, png_inforp info_ptr,
				int transforms, png_voidp params))
			
	}
	return 0;
}

bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
	InitPNG();

	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL)
		return false;

	/* Create and initialize the png_struct
	 * with the desired error handler
	 * functions.  If you want to use the
	 * default stderr and longjump method,
	 * you can supply NULL for the last
	 * three parameters.  We also supply the
	 * the compiler header file version, so
	 * that we know if the application
	 * was compiled with a compatible version
	 * of the library.  REQUIRED
	 */
	png_ptr = lib.png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	/* Allocate/initialize the memory
	 * for image information.  REQUIRED. */
	info_ptr = lib.png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		lib.png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	/* Set error handling if you are
	 * using the setjmp/longjmp method
	 * (this is the normal method of
	 * doing things with libpng).
	 * REQUIRED unless you  set up
	 * your own error handlers in
	 * the png_create_read_struct()
	 * earlier.
	 */
	if (setjmp(*lib.png_set_longjmp_fn(png_ptr, longjmp, (sizeof(jmp_buf))))) {
		/* Free all of the memory associated
		 * with the png_ptr and info_ptr */
		lib.png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		 * problem reading the file */
		return false;
	}

	/* Set up the output control if
	 * you are using standard C streams */
	lib.png_init_io(png_ptr, fp);

	/* If we have already
	 * read some of the signature */
	lib.png_set_sig_bytes(png_ptr, sig_read);

	/*
	 * If you have enough memory to read
	 * in the entire image at once, and
	 * you need to specify only
	 * transforms that can be controlled
	 * with one of the PNG_TRANSFORM_*
	 * bits (this presently excludes
	 * dithering, filling, setting
	 * background, and doing gamma
	 * adjustment), then you can read the
	 * entire image (including pixels)
	 * into the info structure with this
	 * call
	 *
	 * PNG_TRANSFORM_STRIP_16 |
	 * PNG_TRANSFORM_PACKING  forces 8 bit
	 * PNG_TRANSFORM_EXPAND forces to
	 *  expand a palette into RGB
	 */
	lib.png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	lib.png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		&interlace_type, NULL, NULL);
	outWidth = width;
	outHeight = height;

	unsigned int row_bytes = lib.png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*)malloc(row_bytes * outHeight);

	png_bytepp row_pointers = lib.png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < outHeight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
	}

	/* Clean up after the read,
	 * and free any memory allocated */
	lib.png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	/* Close the file */
	fclose(fp);

	/* That's it */
	return true;
}

MyTexture::MyTexture(const char *fileName)
	: mFileName(fileName)
	, mTexture(0)
{

}

MyTexture::~MyTexture() {

}

void MyTexture::bind(GLuint program) {
	if (0 == mTexture) {
		int width = 0, height = 0;
		bool hasAlpha = false;
		GLubyte *textureImage = nullptr;
		bool success = loadPngImage(mFileName.c_str(), width, height, hasAlpha, &textureImage);
		if (!success) {
			assert(false);
			return;
		}
		glGenTextures(1, &mTexture); CHECKERR();
		glBindTexture(GL_TEXTURE_2D, mTexture);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
			height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
			textureImage);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, mTexture);
}