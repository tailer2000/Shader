#version 450

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;
uniform sampler2D u_TexSampler1;
uniform sampler2D u_TexSampler2;
uniform sampler2D u_TexSampler3;

in vec2 v_Tex;

uniform float u_Time;

void main()
{
    // 반 접기 (데칼코마니)
    //vec2 new_Tex = fract(v_Tex*2 + vec2(u_Time, 0));
    //vec2 new_Tex = abs(v_Tex - vec2(0, 0.5)) + vec2(0, 0.5);
    //vec4 newColor = vec4(new_Tex, v_Tex);
    //newColor = texture(u_TexSampler,new_Tex);

   // default
   //vec2 new_Tex = v_Tex;
   //vec4 newColor = texture(u_TexSampler, new_Tex);
   //FragColor = newColor;

   // simple mean blurr
   //vec2 new_Tex[5];
   //new_Tex[0] = vec2(v_Tex.x, v_Tex.y);
   //new_Tex[1] = vec2(v_Tex.x-1.0/256.0, v_Tex.y);
   //new_Tex[2] = vec2(v_Tex.x+1.0/256.0, v_Tex.y);
   //new_Tex[3] = vec2(v_Tex.x, v_Tex.y-1.0/256.0);
   //new_Tex[4] = vec2(v_Tex.x, v_Tex.y+1.0/256.0);
   //vec4 newColor[5];
   //newColor[0] = texture(u_TexSampler, new_Tex[0]);
   //newColor[1] = texture(u_TexSampler, new_Tex[1]);
   //newColor[2] = texture(u_TexSampler, new_Tex[2]);
   //newColor[3] = texture(u_TexSampler, new_Tex[3]);
   //newColor[4] = texture(u_TexSampler, new_Tex[4]);
   //vec4 finalColor = newColor[0] + newColor[1] + newColor[2] + newColor[3] + newColor[4];
   //finalColor /= 5;
   //FragColor = finalColor;
  
   //vec2 new_Tex;
   //new_Tex.x = fract(v_Tex.x*3.0);
   //new_Tex.y = v_Tex.y/3;   // 0~1/3
   //new_Tex.y += floor(v_Tex.x*3.0)/3.0; // offset + 0~1/3
   //vec4 newColor = texture(u_TexSampler, new_Tex);
   //FragColor = newColor;

   //vec2 new_Tex;
   //new_Tex.x = fract(v_Tex.x*3.0);
   //new_Tex.y = v_Tex.y/3;   // 0~1/3
   //new_Tex.y += (2-floor(v_Tex.x*3.0))/3.0; // offset + 0~1/3
   //vec4 newColor = texture(u_TexSampler, new_Tex);
   //FragColor = newColor;
   //vec2 new_Tex;
   //new_Tex.x = v_Tex.x;
   //new_Tex.y = (2-floor(v_Tex.y*3.0))/3.0;
   //new_Tex.y += fract(v_Tex.y*3.0)/3.0;
   //vec4 newColor = texture(u_TexSampler, new_Tex);
   //FragColor = newColor;

   //***************************************** 시험
   //vec2 new_Tex = vec2(fract(v_Tex.x * 2) + floor(v_Tex.y * 2) / 2, fract(v_Tex.y * 2));
   //vec4 newColor = texture(u_TexSampler, new_Tex);
   //FragColor = newColor;

   // 왼쪽, 오른쪽 다른 텍스쳐
   // 1.0 - v_Tex.y : 텍스쳐가 반전될 때 해결.
   //vec2 new_Tex = vec2(v_Tex.x, fract(v_Tex.y));
   //vec4 newColor = texture(u_TexSampler, vec2(new_Tex.x*2, new_Tex.y*2));
   //vec4 newColor1 = texture(u_TexSampler1, vec2(fract(new_Tex.x*2), fract(new_Tex.y*2)));
   //vec4 newColor2 = texture(u_TexSampler2, vec2(new_Tex.x, fract(new_Tex.y*2)));
   //if(new_Tex.y > 0.5f)
   //{
   //  if(new_Tex.x > 0.5f)
   //   {
   //       FragColor = newColor;
   //   }
   //  else{
   //    FragColor = newColor1;
   //  }
   //}
   //else
   //FragColor = newColor2;

}
