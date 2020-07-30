#version 300 es
precision mediump float;
in vec2 esTexturePosition;
uniform sample2D y_texture;//r
uniform sample2D uv_texture;//rg
out vec4 fColor;
void main() {
    vec3 yuv;
    yuv.x = texture2D(y_texture, esTexturePosition).r;
    vec3 uv = texture2D(uv_texture, esTexturePosition);
    yuv.y = uv.r - 0.5f;
    yuv.z = uv.g - 0.5f;
    vec3 rgb = mat3(1.0, 1.0, 1.0,
    0.0, -0.39465, 2.03211,
    1.13983, -0.58060, 0.0) * yuv;
    fColor = vec4(rgb.rgb, 1.0f);
}
