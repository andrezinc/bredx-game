#version 120

uniform sampler2D u_texture; // Textura a ser aplicada
uniform vec2 u_resolution; // Resolução da tela
uniform float u_time; // Tempo para efeitos dinâmicos

varying vec2 v_texCoord; // Coordenadas de textura

void main() {
    vec2 uv = v_texCoord;

    // Efeito de glow
    vec3 color = texture2D(u_texture, uv).rgb;
    float dist = length(uv - vec2(0.5)); // Distância do centro da tela
    float glow = smoothstep(0.4, 0.5, dist); // Efeito de glow baseado na distância
    color += glow * vec3(0.0, 1.0, 1.0); // Adiciona um brilho ciano (azul claro)

    // Efeito de vignette
    float vignette = smoothstep(0.6, 1.0, dist);
    color *= vignette;

    gl_FragColor = vec4(color, 1.0); // Define a cor final do fragmento
}
