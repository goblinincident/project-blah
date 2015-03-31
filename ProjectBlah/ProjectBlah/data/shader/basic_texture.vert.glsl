#version 410

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 uv;

out vec2 v_uv;

uniform mat4 pvm;


void main()
{
	//todo see if you can output the same name
	v_uv = uv;


	gl_Position = pvm * position;
}