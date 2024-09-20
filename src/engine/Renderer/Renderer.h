#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
/**
 * @brief Componentes de funções básicas do jogo como renderização, carregamento de recursos, etc
 */
namespace Gerenciador{
/**
 * @class Renderer
 * 
 * @brief Gerencia a renderização de elementos gráficos.
 * 
 * A classe Renderer é responsável por controlar a janela de renderização, 
 * gerenciar a fila de elementos desenháveis e controlar a câmera. Implementa o 
 * padrão Singleton para garantir que apenas uma instância exista durante a execução.
 * 
 * @details Esta classe utiliza o SFML para renderizar sprites, textos e outros 
 * objetos gráficos. Além disso, permite manipular a câmera para mover a visão 
 * sobre a cena renderizada.
 * 
 * @author Vitor-tml
*/
class Renderer {
private:
    static int camadaJanela;
    static Renderer* singleton;
    sf::RenderWindow janela;
    sf::View camera;
    std::vector<std::pair<const sf::Drawable*, int>> drawables; ///< vetor de pares de int e drawable
    sf::Shader shader;
    bool shaderCarregado; // Adicione esta linha no início da classe
    Renderer(int largura, int altura, const std::string& titulo);
    ~Renderer();
public:
    // Apagando operações
    void operator=(const Renderer&) = delete;
    Renderer(const Renderer&) = delete;

    /**
     * @brief Retorna uma instância para o gerenciador gráfico.
     * @throw Na primeira chamada aloca o grenciador.
     * @param largura valor padrao: 800px
     * @param altura valor padrao: 800px
     * @param titulo valora padrao: "Nova Janela"
     * @return ponteiro singleton do gerenciador.
    */
    static Renderer *getInstance(int largura = 1280, int altura = 720, const std::string& titulo =  "Prodilexos Game");
    /**
     * @brief Adiciona elementos na fila de renderização.
     * @param drawable qualquer objeto desenhável do SFML (sprite, texto, etc)
     * @param camada ordem em que vai ser renderizado, os últimos são os que aparecem por cima
     * @todo Inserir um método para colocar a camada por ordem de inserção.
     */
    void addDrawable(const sf::Drawable& drawable, int camada = 0); // Adiciona um elemento para ser desenhado
    /**
     * @brief Limpa a fila de rendeziração
     */
    void clearDrawables();
    /**
     * @brief Limpa a tela atual e rendezira os elementos da lista drawables
     */
    void render();
    /**
     * @brief Retorna estado da janela
     * @return true para janela fechada false para aberta
     */
    bool isOpen();
    /**
     * @brief Fecha a janela de execução
     */
    void close();
    /**
     * @brief Move o que a janela mostra para o usuário
     * @param x coordenada x do centro da view/câmera
     * @param y coordenada y do centro da view/câmera
     */
    void moveCamera(float x, float y);
    /**
     * @brief Muda o a origem da câmera em relação ao que vai ser mostrado
     * @param x coordenada x do centro da view/câmera
     * @param y coordenada y do centro da view/câmera
     */
    void setCentroCamera(float x, float y);
    /**
     * @brief Muda o que vai ser mostrado em relação ao que vai ser renderizado.
     * @note Adequa a view à janela de renderização, pode distorcer a imagem.
     */
    void setTamanhoCamera(float largura, float altura);
    /**
     * @brief Lê os eventos do jogo (interações com a janela)
     * @return True caso tenha ocorrido algum evento, false se todos os eventos já foram tratados
     * @param evento objeto do tipo Event passado por parâmetro para receber os eventos não tratados
     */
    bool pollEvent(sf::Event &evento);
    /**
     * @brief Retorna o tamanho da janela
     * 
     * @return sf::Vector2u (.x e .y)
     */
    sf::Vector2u getTamanho() const;

    void carregarShaders();
};
// }
}
#endif