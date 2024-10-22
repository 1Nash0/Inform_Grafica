
#version 330 core

// Atributos recibidos desde el vertex shader
in vec3 fragNormal;
in vec2 fragTexCoord;

// Color de salida
out vec4 outColor;

void main() {
    // Si el índice de la primitiva es impar, usar las normales para colorear
    if (gl_PrimitiveID % 2 == 1) {
        // Normalizamos la normal y la mapeamos a [0, 1] para ser usada como color
        vec3 normalColor = normalize(fragNormal) * 0.5 + 0.5;
        outColor = vec4(normalColor, 1.0);
    } else {
        // Si es par, pintar las coordenadas de textura como color
        outColor = vec4(fragTexCoord, 0.0, 1.0);  // R: s, G: t, B: 0, A: 1
    }
}
