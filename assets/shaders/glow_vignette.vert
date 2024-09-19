#version 120

attribute vec2 a_position; // Posições dos vértices
attribute vec2 a_texCoord; // Coordenadas de textura

varying vec2 v_texCoord; // Coordenadas de textura passadas para o fragment shader

void main() {
    gl_Position = vec4(a_position, 0.0, 1.0); // Passa a posição dos vértices
    v_texCoord = a_texCoord; // Passa as coordenadas de textura
}
