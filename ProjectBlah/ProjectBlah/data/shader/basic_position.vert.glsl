#version 410

layout(location=0) in vec4 position;


uniform mat4 pvm;

void main()
{
	gl_Position = pvm * position;
	//gl_Position = Position;
}
