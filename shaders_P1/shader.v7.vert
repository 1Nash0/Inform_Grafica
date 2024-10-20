#version 330 core

uniform mat4 modelViewProj;
uniform mat4 modelView;
uniform mat4 normal;

in vec3 inPos;
in vec3 inNormal;

out vec3 vpos;
out vec3 vnorm;

void main()
{
	
	vpos = (modelView * vec4(inPos, 1)).xyz;
	//vnorm = inverse(transpose(modelView)) * vec4(inNormal, 0);
	vnorm = (normal * vec4(inNormal, 0)).xyz;

	gl_Position =  modelViewProj * vec4(inPos, 1.);
}
