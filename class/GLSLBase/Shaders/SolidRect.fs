#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_Temp;

uniform float u_Time;
uniform vec2 u_Points[5];   //������
const vec2 c_Points[2] = {vec2(0, 0), vec2(0.1)};   //����ǥ

void main()
{
    vec2 newUV = v_Temp.xy - vec2(0.5); //���� 0.5

    float pointGrey = 0.f;  // ���߿� ������ �����ַ���
    float distance = 0.f;
    vec2 newVec = vec2(0);
    float newTime = fract(u_Time);

    for(int i=0; i < 5; i++)
    {
        vec2 newPoint = u_Points[i];
        newVec = newPoint - newUV; //�ڱ���ġ
        distance = length(newVec);

        if(distance < 0.02)  // ��ũ��
        {
            pointGrey += 0.5;    //��ġ�� 1�Ѿ �����
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

    FragColor = vec4(pointGrey);    //ȸ����
}
