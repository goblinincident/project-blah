#version 410

in vec2 v_uv;
out vec4 colour;

uniform sampler2D texture_diffuse;

void main()
{
	colour = texture(texture_diffuse, v_uv);
};
