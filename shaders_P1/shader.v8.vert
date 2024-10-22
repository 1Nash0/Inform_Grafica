#version 330 core

// Atributos
in vec3 inPos;
in vec3 inNormal;
in vec2 inTexCoord;

// Uniformes
uniform mat4 modelViewProj;   // Matriz combinada de transformación
uniform mat4 normal;          // Matriz para transformar las normales

// Salidas hacia el fragment shader
out vec3 fragNormal;
out vec2 fragTexCoord;

void main() {
    // Transformar la posición del vértice usando la matriz modelViewProj
    gl_Position = modelViewProj * vec4(inPos, 1.0);

    // Transformar la normal usando la matriz de normales
    fragNormal = mat3(normal) * inNormal;

    // Pasar las coordenadas de textura al fragment shader
    fragTexCoord = inTexCoord;
}

