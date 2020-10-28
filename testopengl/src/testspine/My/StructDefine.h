#ifndef StructDefine_h_
#define StructDefine_h_
#include <string>
#include <GL/glew.h>

struct MySize {
	MySize();
	MySize(int _w, int _h);

	int width, height;
};

struct MyColor {
	MyColor();
	MyColor(float _r, float _g, float _b, float _a);

	MyColor &set(const MyColor &other);
	MyColor &set(float _r, float _g, float _b, float _a);
	MyColor &clamp();

	float r, g, b, a;
};

struct MyPoint
{
	MyPoint(float _x, float _y);
	MyPoint();
	GLfloat x;
	GLfloat y;
};

struct SpineVertex {
	float x, y;

	float u, v;

	MyColor color;
};

struct MyRect {
	MyRect(float _x, float _y, float _w, float _h);
	MyRect();
	float x, y, w, h;
	float left() { return x; }
	float right() { return x + w; }
	float top() { return y; }
	float bottom() { return y + h; }
	float width() { return w; }
	float height() { return h; }
};

struct MyMargins {
	MyMargins();
	MyMargins(float _left, float _top, float _right, float _bottom);

	float left, top, right, bottom;
};

typedef std::string MyString;

#endif