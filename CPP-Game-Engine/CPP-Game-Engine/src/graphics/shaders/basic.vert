#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 proj_matrix;
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA{

	vec4 position;
	vec4 color;

} out_data;

void main(){

    gl_Position = proj_matrix * view_matrix * model_matrix * position;
	out_data.position = model_matrix * position;
	out_data.color = color;

}