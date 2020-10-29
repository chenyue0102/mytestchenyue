#version 300 es

uniform mediump vec4 u_color;
uniform highp mat4 u_matrix;

in highp vec2 a_position;

out mediump vec4 v_color;

void main() {
   gl_Position = u_matrix * vec4(a_position.xy, 0.0, 1.0);
   v_color = u_color;
}
