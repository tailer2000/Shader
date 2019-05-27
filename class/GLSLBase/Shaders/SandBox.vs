#version 450

in vec3 a_Position;

const float PI = 3.141592;
uniform float u_Time;
uniform vec2 u_Points[5]; 

out float v_Grey;
out vec2 v_Tex;


void Flag()
{
	vec3 newPos = a_Position;
	// newPos.y = newPos.y * n   Æø Á¶Àý 

	// 0~1
	float additionalValueX = newPos.x + 0.5;
	float additionalValueY = newPos.y + 0.5;

	float periodX = 1.0 + (1.0 - additionalValueY) * 0.5;
	float periodY = 1.0 + additionalValueX * 0.5;

	// x : -0.5~0.5, 0~1 0~2PI
	float valueX = (additionalValueY*2*PI*periodX) - u_Time;
	float valueY = (additionalValueX*2*PI*periodY) - u_Time;

	float sinValueX = sin(valueX)*0.1;
	float sinValueY = sin(valueY)*0.2;

	// y scale
	newPos.y = newPos.y * ((1.0 - additionalValueX)*0.5 + 0.5);

	newPos.x = newPos.x - sinValueX * additionalValueX;
	newPos.y = newPos.y + sinValueY * additionalValueX;
	gl_Position = vec4(newPos.xyz, 1);

	v_Grey = sinValueY + 0.5;
	v_Tex = vec2(0.5,0.5) + a_Position.xy;
}

void Wave()
{
	float grey = 0;

	vec2 target;
	vec2 source;
	target = a_Position.xy;
	source = vec2(0.0, 0.0);
	float dis = length(target - source) * 4 *PI;;	// 0~0.5 --> 0~2PI
	grey = sin(dis - u_Time);

	gl_Position = vec4(a_Position.xyx, 1);

	v_Grey = (grey+1)/2.0;
	v_Tex = vec2(0.5, 0.5) + a_Position.xy;
}

void SphereMapping()
{
	
	
	float r = 0.5;
	float beta = (a_Position.x+0.5) * 2 * PI;
	float theta = (a_Position.y+0.5) * PI;

	vec3 spherePos = vec3(
	r*sin(theta) * cos(beta),
	r*sin(theta) * sin(beta),
	r*cos(theta)
	);

	vec3 originPos = a_Position.xyz;

	float interpol = fract(u_Time);

	vec3 newPos = mix(originPos, spherePos, interpol);

	gl_Position = vec4(newPos.xyz, 1);
	v_Grey = newPos.x;
}

void main()
{
	//Flag();
	//Wave();
	SphereMapping();
}