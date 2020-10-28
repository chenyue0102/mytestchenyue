#include "StructDefine.h"
#include <spine/MathUtil.h>

MySize::MySize() :width(), height() {

}

MySize::MySize(int _w, int _h) : width(_w), height(_h) {

}

MyColor::MyColor() : r(0), g(0), b(0), a(0) {
}

MyColor::MyColor(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {
	clamp();
}

MyColor &MyColor::set(const MyColor &other) {
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
	clamp();
	return *this;
}

MyColor &MyColor::set(float _r, float _g, float _b, float _a) {
	r = _r;
	b = _b;
	g = _g;
	a = _a;
	clamp();
	return *this;
}

MyColor &MyColor::clamp() {
	r = spine::MathUtil::clamp(this->r, 0, 1);
	g = spine::MathUtil::clamp(this->g, 0, 1);
	b = spine::MathUtil::clamp(this->b, 0, 1);
	a = spine::MathUtil::clamp(this->a, 0, 1);
	return *this;
}

MyPoint::MyPoint(float _x, float _y) :x(_x), y(_y) {

}

MyPoint::MyPoint() : x(0.0f), y(0.0f) {

}

MyRect::MyRect(float _x, float _y, float _w, float _h)
	: x(_x)
	, y(_y)
	, w(_w)
	, h(_h)
{

}

MyRect::MyRect() :x(1.0f), y(1.0f), w(1.0f), h(1.0f){
}

MyMargins::MyMargins() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f){

}

MyMargins::MyMargins(float _left, float _top, float _right, float _bottom) :left(_left), top(_top), right(_right), bottom(_bottom){

}