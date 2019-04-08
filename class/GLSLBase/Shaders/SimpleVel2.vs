#version 450

// Attributes
in vec3 a_Position;
in vec3 a_Vel;
in vec4 a_StartLifeRatioAmp;
in float a_Value;
in vec4 a_Color;

// Varying --> fragment shader input
out vec4 v_Color;
out vec2 v_OriPos;
out float v_Radius;

uniform float u_Time;
const float PI = 3.141952;
const mat3 c_RP = mat3(0,-1,0,-1,0,0,0,0,0);
const vec3 c_Gravity = vec3(0, -1 ,0);

void main()
{
	vec3 newPos = a_Position.xyz;
	v_OriPos = a_Position.xy;
	v_Radius = abs(a_Position.x);
	vec3 newVel = a_Vel.xyz;

	float start = a_StartLifeRatioAmp.x;
	float lifeTime = a_StartLifeRatioAmp.y;
	float ratio = a_StartLifeRatioAmp.z;
	float amp = a_StartLifeRatioAmp.w;
	float newAlpha = a_Color.w;
	float newVPos;

	float newTime = u_Time - start;

	if(newTime > 0)
	{
		newPos.x += sin(a_Value*2*PI);
		newPos.y += cos(a_Value*2*PI);

		newTime = mod(newTime, lifeTime);
		newVel = newVel*c_Gravity*newTime;
		newPos = newPos + 0.5*c_Gravity*newTime*newTime;

		newAlpha = pow(1 - newTime/lifeTime, 2);
		//vec3 vSin = a_Vel*c_RP;
		//newPos = newPos + vSin*sin(newTime*PI*2*ratio)*amp;

	}
	else
	{
		newPos = vec3(100000,100000,100000);
		newAlpha = 0;
	}

	gl_Position = vec4(newPos.xyz, 1);
	v_Color = vec4(a_Color.xyz, newAlpha);
	
}