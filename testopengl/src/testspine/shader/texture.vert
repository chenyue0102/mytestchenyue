#version 430 core
uniform highp mat4 u_matrix;
uniform highp mat4 model;

varying lowp vec4 v_color;
varying mediump vec2 v_texCoord;

attribute highp vec2 a_position;
attribute mediump vec2 a_texCoord;
attribute lowp vec4 a_color;

void main() {
   vec4 tmp = u_matrix * vec4(a_position.xy, 0.0, 1.0) ;
   //if (tmp.x < 100.f)
	//gl_Position = vec4(gl_Position.x / 2, gl_Position.y / 2, 0.99, 1.0) ;
	gl_Position = tmp;
   v_color = a_color;
   v_texCoord = a_texCoord;
}
