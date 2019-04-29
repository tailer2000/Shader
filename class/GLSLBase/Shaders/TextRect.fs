#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;
in vec2 v_Tex;

uniform float u_Time;

void main()
{
    //vec2 new_Tex = fract(v_Tex*2 + vec2(u_Time, 0));
    vec2 new_Tex = abs(v_Tex - vec2(0, 0.5)) + vec2(0, 0.5);

    vec4 newColor = texture(u_TexSampler, v_Tex);
    newColor = vec4(new_Tex, 0, 1);
   
    

	FragColor = newColor;
}
