#version 450

in vec3 a_Position;
in vec4 a_Color;
in vec4 a_Uv;

out vec4 v_Temp;

void main()
{
	gl_Position = vec4(a_Position.xyz, 1);
	v_Temp = vec4(a_Uv.xy, 1, 1);
}
