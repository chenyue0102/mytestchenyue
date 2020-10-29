#version 300 es
precision mediump float;
in mediump vec4 v_color;

out vec4 fColor;
void main() {
    fColor = v_color;
}
