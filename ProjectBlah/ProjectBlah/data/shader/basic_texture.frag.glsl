#version 410

in vec2 v_uv;
out vec4 colour;

uniform sampler2D texture_0_diffuse;

void main()
{
	colour = texture(texture_0_diffuse, v_uv);
};
