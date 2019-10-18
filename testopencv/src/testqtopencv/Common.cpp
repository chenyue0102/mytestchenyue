#include "Common.h"

void rgb2yuv(uchar8 r, uchar8 g, uchar8 b, uchar8 *y, uchar8 *u, uchar8 *v)
{
	*y = 0.299f * r + 0.587f * g + 0.114f * b;
	*u = -0.169f * r - 0.331f * g + 0.5f * b + 128;
	*v = 0.5f * r - 0.419f * g - 0.081f * b + 128;
}
static uchar8 clamp(int v)
{
	if (v > 255)
	{
		return 255;
	}
	else if (v < 0)
	{
		return 0;
	}
	else
	{
		return v;
	}
}

void yuv2rgb(uchar8 y, uchar8 u, uchar8 v, uchar8 * r, uchar8 * g, uchar8 * b)
{
	int tmp = y + 1.13983 * (v - 128);
	*r = clamp(tmp);

	tmp = y - 0.39465 * (u - 128) - 0.58060 * (v - 128);
	*g = clamp(tmp);

	tmp = y + 2.03211 * (u - 128);
	*b = clamp(tmp);
}
