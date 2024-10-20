#version 330 core

in vec3 inPos;		

void main()
{
	mat4 model = mat4(1.0);
	mat4 view = mat4(1.0);
	mat4 proj = mat4(0.0);

	view[3].z= -3.;

	float n = 1.;
	float f = 10.;

	proj[0][0] =  1.732; //proj[0].x
	proj[1][1] = 1.732; //proj[1].y
	//proj[2][2] = (f+n)/(n-f);
	//proj[2][3] = -1.;
	proj[2].zw = vec2((f+n)/(n-f), -1.);
	proj[3][2] = 2.*f*n/(n-f); 


	gl_Position =  proj* view * model* vec4(inPos, 1.);
}
