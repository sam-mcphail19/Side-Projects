#version 450 core

in vec3 position;
in vec4 color;
in vec2 textureCoord;

out vec4 passColor;
out vec2 passTextureCoord;

void main(void){

    gl_Position = vec4(position, 1.0);
    passColor = color;
    passTextureCoord = textureCoord;

}