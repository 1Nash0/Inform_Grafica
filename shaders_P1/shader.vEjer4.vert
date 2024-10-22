#version 330 core

in vec3 inPos;
in vec3 inNormal;
in vec2 inTexCoord;

uniform mat4 modelViewProj;   
uniform mat4 normal;          

out vec3 fNormal;
out vec2 fTexCoord;

void main() {
    gl_Position = modelViewProj * vec4(inPos, 1.0);

    fNormal = mat3(normal) * inNormal;

    fTexCoord = inTexCoord;
}

