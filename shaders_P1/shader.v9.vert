#version 330 core

uniform mat4 modelViewProj;

in vec2 inTexCoord;
in vec3 inPos;

out vec2 vtexcoord;

void main()
{
    vtexcoord = inTexCoord;

    gl_Position =  modelViewProj * vec4(inPos, 1.);
}

