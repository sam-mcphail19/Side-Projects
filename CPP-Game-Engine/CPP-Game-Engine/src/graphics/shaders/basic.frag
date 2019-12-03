#version 450 core

layout (location = 0) out vec4 outColor;

in vec4 pos;

uniform vec4 color = vec4(1.0, 0.6, 1.0, 1.0);

void main(){

    outColor = color;

}