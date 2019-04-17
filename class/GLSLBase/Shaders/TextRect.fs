#version 450

layout(location=0) out vec4 FragColor;

in vec2 v_Tex;

uniform float u_Time;
const float PI = 3.141952;

void main()
{
    vec4 newColor = vec4(0);
    float x = (sin(v_Tex.x *PI*2 + u_Time)+1)/2;

    if(v_Tex.y < x && x - 0.01 < v_Tex.y)
    {
        newColor = vec4(1);
    }


	FragColor = newColor;
}
