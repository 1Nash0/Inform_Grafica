#version 330 core

//uniform mat4 proj;
//uniform mat4 view;
//uniform mat4 model;
uniform mat4 modelViewProj;

in vec3 inPos;		

void main()
{
	//gl_Position =  proj* view * model* vec4(inPos, 1.);
	gl_Position =  modelViewProj * vec4(inPos, 1.);
}
