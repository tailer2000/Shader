#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;

in vec2 v_Tex;

uniform int u_Sprite;
uniform int u_ResolX;
uniform int u_ResolY;

void main()
{
   // 스프라이트 시트
   
   int x_index = int(floor(fract(float(u_Sprite)/float(u_ResolX))*float(u_ResolX)));
   int y_index = int(floor(floor(u_Sprite/u_ResolX)));

   vec2 new_Tex = v_Tex;
   new_Tex.x = v_Tex.x/u_ResolX + x_index /float(u_ResolX);
   new_Tex.y = v_Tex.y/u_ResolY + y_index/float(u_ResolY);

   vec4 newColor = texture(u_TexSampler, new_Tex);
   FragColor = newColor;
}
