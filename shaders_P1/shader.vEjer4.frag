#version 330 core

in vec3 fNormal;
in vec2 fTexCoord;

out vec4 outColor;

void main() {
    
    if (gl_PrimitiveID % 2 == 1) {
        vec3 normalColor = normalize(fNormal) * 0.5 + 0.5;
        outColor = vec4(normalColor, 1.0);
    } else {
        outColor = vec4(fTexCoord, 0.0, 1.0);  
    }
}
