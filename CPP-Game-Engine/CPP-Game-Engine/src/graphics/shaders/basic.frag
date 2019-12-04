#version 450 core

layout (location = 0) out vec4 out_color;

uniform vec4 color;
uniform vec2 light_pos;

in DATA {

	vec4 position;
	vec4 color;

} data_in;

void main()
{
	float intensity = 1.0 / length(data_in.position.xy - light_pos);
	//out_color = color * intensity;
	out_color = data_in.color * intensity;
}