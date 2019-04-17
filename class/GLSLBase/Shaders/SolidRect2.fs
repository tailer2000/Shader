#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
	FragColor = vec4(0,0,0,1);
}
