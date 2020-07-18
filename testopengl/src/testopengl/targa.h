#pragma once
#include <GL\glew.h>

namespace vtarga {
unsigned char * load_targa(const char * filename, GLenum &format, int &width, int &height);
void free_targa_buffer(unsigned char *buf);
}