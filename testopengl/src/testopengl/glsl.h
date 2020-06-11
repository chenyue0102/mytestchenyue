#pragma once
const char* vString = R"(
#version 430 core
#pragma debug(on)
#pragma optimize(on)
#define USE_PIPELINE

layout(location=4) uniform mat4 myMatrix;
layout(location=1) in vec4 vPosition;
layout(location=2) in vec4 vColor;
layout(location=3) uniform mat4 projection_matrix;
layout(std140, column_major) uniform MyTest
{
bool isReverse;
bool isGradual;
};
out Param{
vec4 fcolor;
float fisReverse;
float fisGradual;
};
//pipeline形式,内置的gl_PerVertex必须重新声明
#ifdef USE_PIPELINE
out gl_PerVertex{
	vec4 gl_Position;
	float gl_PointSize;
};
#endif

void main()
{
	//mat4 tmp = mat4(1.0, 0.0, 0.0, 0.0,
	//	0.0, 1.0, 0.0, 0.0, 
	//	0.0, 0.0, 1.0, 0.0, 
	//	0.0, 0.0, 0.0, 1.0);
	gl_Position = myMatrix * vPosition;
	fcolor = vColor;
	fisReverse = isReverse ? 1.0 : 0.0;
	fisGradual = isGradual ? 1.0 : 0.0;
}
)";


const char *fString = R"(
#version 430 core
#pragma debug(on)
in Param{
vec4 fcolor;
float fisReverse;
float fisGradual;
};
out vec4 fColor;


void getPercent(inout float f)
{
	f = 0.8;
}
void main()
{
	fColor = vec4(fcolor.rgb, 1.0);//rgba
}
)";