#version 330 core

in vec3 Normal;
in vec2 TexCoord;

out vec4 outColor;

void main() {
    
    if (gl_PrimitiveID % 2 == 1) {
        vec3 normalColor = normalize(Normal);
        outColor = vec4(normalColor, 1.0f);
    } else {
        outColor = vec4(TexCoord, 0.0f, 1.0f);  
    }
}
