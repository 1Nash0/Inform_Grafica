#version 330 core

uniform sampler2D colorTex;
out vec4 outColor;

in vec3 vpos;
in vec3 vnorm;

void main()
{
	//outColor = vec4(vpos.xy, 0, 0 );
	outColor = vec4(vnorm, 0 );

}
