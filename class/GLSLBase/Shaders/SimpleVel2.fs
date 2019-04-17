#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_Color;
in vec2 v_OriPos;
in vec2 v_TexPos;
in float v_Radius;

void main()
{
     vec4 newColor;
     float dis = sqrt(v_OriPos.x*v_OriPos.x + v_OriPos.y* v_OriPos.y);
    if( dis < v_Radius)
    {
        newColor = v_Color;
        newColor.a = dis / v_Radius;
    }
    else{
        newColor = vec4(0);
    }

	FragColor = newColor;
}
