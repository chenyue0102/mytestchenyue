#version 300 es
uniform highp mat4 u_matrix;

in highp vec2 a_position;
in mediump vec2 a_texCoord;
in lowp vec4 a_color;

out lowp vec4 v_color;
out mediump vec2 v_texCoord;

void main() {
   gl_Position = u_matrix * vec4(a_position.xy, 0.0, 1.0);
   v_color = a_color;
   v_texCoord = a_texCoord;
}
