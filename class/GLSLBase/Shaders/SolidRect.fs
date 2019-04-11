#version 450

layout(location=0) out vec4 FragColor;

in vec4 v_Temp;

uniform vec2 u_Points[5];   //������
const vec2 c_Points[2] = {vec2(0, 0), vec2(0.1)};   //����ǥ

void main()
{
    vec2 newUV = v_Temp.xy - vec2(0.5); //���� 0.5

    float pointGrey = 0.f;  // ���߿� ������ �����ַ���

    for(int i=0; i < 2; i++)
    {
        vec2 newPoint = c_Points[i];
        vec2 newVec = newPoint - newUV; //�ڱ���ġ
        float distance = sqrt(newVec.x*newVec.x+newVec.y*newVec.y);
        if(distance < 0.1)  // ��ũ��
        {
            pointGrey += 0.5;    //��ġ�� 1�Ѿ �����
        }
    }
    FragColor = vec4(pointGrey);    //ȸ����
}
