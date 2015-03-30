#version 410

layout(location=1) in vec4 Position;


uniform mat4 PVM;

void main()
{
	gl_Position = PVM * Position;
	//gl_Position = Position;
}
