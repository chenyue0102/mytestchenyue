#version 300 es
in vec3 vertexPosition;
in vec2 texturePosition;
out vec2 esTexturePosition;
void main(){
    gl_Position = vec4(vertexPosition, 1.0f);
    esTexturePosition = texturePosition;
}