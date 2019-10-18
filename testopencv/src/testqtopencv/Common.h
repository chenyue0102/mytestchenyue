#pragma once

typedef unsigned char uchar8;
void rgb2yuv(uchar8 r, uchar8 g, uchar8 b, uchar8 *y, uchar8 *u, uchar8 *v);
void yuv2rgb(uchar8 y, uchar8 u, uchar8 v, uchar8 *r, uchar8 *g, uchar8 *b);



