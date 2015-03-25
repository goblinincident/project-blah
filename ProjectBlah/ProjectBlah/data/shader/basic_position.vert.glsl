#version 410

layout(location=1) in vec4 Position;


uniform mat4 MVP;


void main()
{
	gl_Position = MVP * Position;
	//gl_Position = Position;
}
