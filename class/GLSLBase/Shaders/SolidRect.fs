#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_Temp;

uniform float u_Time;
uniform vec2 u_Points[5];   //적개수
const vec2 c_Points[2] = {vec2(0, 0), vec2(0.1)};   //적좌표

void main()
{
    vec2 newUV = v_Temp.xy - vec2(0.5); //중점 0.5

    float pointGrey = 0.f;  // 나중에 색상을 더해주려고
    float distance = 0.f;
    vec2 newVec = vec2(0);
    float newTime = fract(u_Time);

    for(int i=0; i < 5; i++)
    {
        vec2 newPoint = u_Points[i];
        newVec = newPoint - newUV; //자기위치
        distance = length(newVec);

        if(distance < 0.02)  // 적크기
        {
            pointGrey += 0.5;    //겹치면 1넘어서 흰색됨
        }
    }
    distance = length(newVec);
    newTime = fract(u_Time);
    float ringwidth = 0.1;

    if(distance <  newTime && distance > newTime - ringwidth)
    {
        float temp = (distance - newTime)/ringwidth;
        pointGrey = temp;

        
    }

    FragColor = vec4(pointGrey);    //회색조
}
