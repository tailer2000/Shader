#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_Temp;

uniform vec2 u_Points[5];   //적개수
const vec2 c_Points[2] = {vec2(0, 0), vec2(0.1)};   //적좌표

void main()
{
    vec2 newUV = v_Temp.xy - vec2(0.5); //중점 0.5

    float pointGrey = 0.f;  // 나중에 색상을 더해주려고

    for(int i=0; i < 2; i++)
    {
        vec2 newPoint = c_Points[i];
        vec2 newVec = newPoint - newUV; //자기위치
        float distance = sqrt(newVec.x*newVec.x+newVec.y*newVec.y);
        if(distance < 0.1)  // 적크기
        {
            pointGrey += 0.5;    //겹치면 1넘어서 흰색됨
        }
    }
    FragColor = vec4(pointGrey);    //회색조
}
