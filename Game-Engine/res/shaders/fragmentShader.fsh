#version 450 core

in vec4 passColor;
in vec2 passTextureCoord;

out vec4 outColor;

uniform sampler2D tex;

void main(void){

    vec4 textureColor = texture(tex, passTextureCoord);
    outColor = passColor * textureColor;

}