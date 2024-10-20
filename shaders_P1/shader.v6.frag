#version 330 core

uniform sampler2D colorTex;
out vec4 outColor;

in vec2 vtexcoord;

void main()
{
	//outColor = vec4 (vtexcoord.xy,1,1);
	outColor = texture(colorTex, vtexcoord.xy);

	if (outColor.g > 0.8) discard;

}
