#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 mvp;

out DATA{

	vec4 position;
	vec4 color;

} out_data;

void main(){

	gl_Position = mvp * position;
	out_data.position = position;
	out_data.color = color;

}