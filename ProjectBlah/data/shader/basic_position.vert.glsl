#version 410

layout(location=0) in vec3 Position;


uniform mat4 MVP;


void main()
{
	gl_Position= PVM * Position;
}
