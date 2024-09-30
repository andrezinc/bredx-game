uniform sampler2D texture;
uniform bool isShader;
uniform vec2 resolution;
uniform float time; // Tempo para animação

// Variáveis para iluminação
uniform vec3 lightPos;   // Posição da luz

// Variáveis para controlar a intensidade dos efeitos
uniform float glitchAmount = 0.0005; // Força do glitch
uniform float chromaticAberrationAmount = 0.002; // Intensidade do desvio de cor
uniform float scanLineIntensity = 0.9; // Intensidade das linhas de escaneamento
uniform float neonIntensity = 1.0; // Intensidade do efeito de neon
uniform float bloomThreshold = 0.9; // Limite para o efeito bloom

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
    vec4 colorR = texture2D(texture, texCoord + vec2(chromaticAberrationAmount, 0.0)); // Vermelho
    vec4 colorG = texture2D(texture, texCoord); // Verde
    vec4 colorB = texture2D(texture, texCoord - vec2(chromaticAberrationAmount, 0.0)); // Azul

    // Combina as cores com um efeito de glitch
    vec4 glitchColor = vec4(colorR.r, colorG.g, colorB.b, 1.0);

    // Adiciona linhas de escaneamento
    if (mod(gl_FragCoord.y, 2.0) == 0.0) {
        glitchColor *= scanLineIntensity; // Escurece as linhas de escaneamento
    }

    // Detecta bordas para o efeito de neon
    vec4 edgeColor = vec4(0.0);
    for (float x = -1.0; x <= 1.0; x += 1.0) {
        for (float y = -1.0; y <= 1.0; y += 1.0) {
            vec2 sampleCoord = texCoord + vec2(x, y) * offset;
            edgeColor += texture2D(texture, sampleCoord);
        }
    }
    edgeColor /= 9.0; // Média dos valores amostrados
    edgeColor = abs(glitchColor - edgeColor); // Intensidade das bordas

    // Adiciona o efeito de neon nas bordas detectadas
    vec4 neonColor = edgeColor * vec4(0.0, neonIntensity, neonIntensity, 1.0); // Cor do neon (ciano)

    // Cálculos de iluminação
    vec3 norm = normalize(vec3(1.0, 0.0, 1.0)); // Normal fictício, ajuste conforme necessário
    vec3 lightDir = normalize(lightPos - vec3(texCoord, 0.0)); // Direção da luz
    float diff = max(dot(norm, lightDir), 0.0); // Iluminação difusa
    vec3 diffuse = diff * vec3(1.0); // Cor da luz difusa (branca)

    // Combina a cor original com o efeito de neon
    vec4 finalColor = glitchColor + neonColor; // Use glitchColor como base

    // Assegura que o canal alfa está sendo preservado
    finalColor.a = glitchColor.a; // Preserve o canal alfa de glitchColor

    // Aplica a iluminação e os efeitos
    if (isShader) {
        // Bloom effect
        vec4 bloomColor = (finalColor.r > bloomThreshold || finalColor.g > bloomThreshold || finalColor.b > bloomThreshold) 
            ? finalColor 
            : vec4(0.0);

        // Verifica se a cor original do pixel é transparente
        vec4 originalColor = texture2D(texture, texCoord);
        gl_FragColor = (originalColor.a == 0.0) 
            ? vec4(0.0) // Mantém o pixel transparente
            : finalColor + bloomColor; // Combina o efeito bloom
    } else {
        gl_FragColor = texture2D(texture, texCoord); // Sem efeitos
    }
}
