#version 450

in vec3 a_Position;
in vec3 a_Vel;
in vec2 a_StartLife;

const vec3 c_Gravity = vec3(0, -5, 0);

uniform float u_Time;
uniform bool u_Repeat = false;

void main()
{
	vec3 newPos = a_Position.xyz;
	float startTime = a_StartLife.x;
	float lifeTime = a_StartLife.y;

	float newTime = u_Time - startTime;

	if(newTime > 0)
	{
		//newPos += a_Vel* newTime + 0.5 * c_Gravity * newTime * newTime;
		float life = newTime;
		float remainingLife = lifeTime - life;
		
		if(u_Repeat == true)
		{
			remainingLife = 1.f;
			newTime = mod(newTime, lifeTime);
		}
		
		if(remainingLife < 0)
		{
			newPos = vec3(100000, 100000, 100000);
		}
		else
		{
			newPos += a_Vel* newTime + 0.5 * c_Gravity * newTime * newTime;
		}
	}
	else
	{
		newPos = vec3(100000, 100000, 100000);
	}

	gl_Position = vec4(newPos, 1);
}