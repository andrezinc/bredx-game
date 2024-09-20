uniform sampler2D texture;
uniform bool isShader;
uniform vec2 resolution;
uniform float time; // Tempo para animação

// Variáveis para iluminação
uniform vec3 lightPos;   // Posição da luz
uniform vec3 viewPos;    // Posição da câmera

// Variáveis para glitch
uniform float glitchAmount = 0.01; // Força do glitch

// Função de ruído simples
float noise(vec2 uv) {
    return fract(sin(dot(uv.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec2 offset = vec2(1.0) / resolution;

    // Distorção de textura com ruído
    float noiseValue = noise(texCoord * 5.0 + time) * glitchAmount;
    texCoord.x += noiseValue;

    // Desvio de cor (chromatic aberration)
    vec4 colorR = texture2D(texture, texCoord + vec2(0.005, 0.0)); // Vermelho
    vec4 colorG = texture2D(texture, texCoord); // Verde
    vec4 colorB = texture2D(texture, texCoord - vec2(0.005, 0.0)); // Azul

    // Combina as cores com um efeito de glitch
    vec4 glitchColor = vec4(colorR.r, colorG.g, colorB.b, 1.0);

    // Adiciona linhas de escaneamento
    if (mod(gl_FragCoord.y, 2.0) == 0.0) {
        glitchColor *= 0.9; // Escurece as linhas de escaneamento
    }

    vec4 originalColor = glitchColor; // Usa a cor do glitch como cor original

    // Detecta bordas para o efeito de neon
    vec4 edgeColor = vec4(0.0);
    for (float x = -1.0; x <= 1.0; x += 1.0) {
        for (float y = -1.0; y <= 1.0; y += 1.0) {
            vec2 sampleCoord = texCoord + vec2(x, y) * offset;
            edgeColor += texture2D(texture, sampleCoord);
        }
    }
    edgeColor /= 9.0;
    edgeColor = abs(originalColor - edgeColor) * 1.0; // Ajuste a intensidade aqui

    // Adiciona o efeito de neon nas bordas detectadas
    vec4 neonColor = edgeColor * vec4(0.0, 1.0, 1.0, 1.0); // Cor do neon (ciano)
    
    // Combina a cor original com o efeito de neon
    vec4 finalColor = originalColor + neonColor;

    // Cálculos de iluminação
    vec3 norm = normalize(vec3(1.0, 0.0, 1.0)); // Normal fictício, ajuste conforme necessário
    vec3 lightDir = normalize(lightPos - vec3(texCoord, 0.0)); // Direção da luz
    float diff = max(dot(norm, lightDir), 0.0); // Iluminação difusa
    vec3 diffuse = diff * vec3(1.0); // Cor da luz difusa (branca)

    // Aplica a iluminação e os efeitos
    if (isShader) {
        gl_FragColor = finalColor + vec4(diffuse, 0.0);
    } else {
        gl_FragColor = texture2D(texture, texCoord);
    }
}
