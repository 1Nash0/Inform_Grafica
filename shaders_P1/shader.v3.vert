#version 330 core

uniform mat4 modelViewProj;
in vec3 inColor;
in vec3 inPos;		

out vec3 vcolor;

void main()
{
	vcolor = inColor;
	gl_Position =  modelViewProj * vec4(inPos, 1.);
}
