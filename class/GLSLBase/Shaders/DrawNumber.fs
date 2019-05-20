#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;

in vec2 v_Tex;

uniform int u_Number[3];

void main()
{
   // 단일 텍스쳐 숫자 바꾸기
   //vec2 new_Tex = v_Tex;
   //float newy = 9.0 - float(u_Number);
   //new_Tex.y = new_Tex.y/10.0 + newy/10.0;
   //vec4 newColor = texture(u_TexSampler, new_Tex);
   //FragColor = newColor;

   // 단일 텍스쳐 3칸으로 쪼개기
   vec2 new_Tex = v_Tex;
   new_Tex.x = fract(v_Tex.x * 3.0 );
   int newIndex  = int(floor(v_Tex.x*3.0));
   float newy = 9.0 - float(u_Number[newIndex]);
   new_Tex.y = new_Tex.y/10.0 + newy/10.0;
   vec4 newColor = texture(u_TexSampler, new_Tex);
   FragColor = newColor;
}
