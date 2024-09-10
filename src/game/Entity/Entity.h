#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../../engine/Ente/Ente.h"
#include "../../engine/PhysicsComponent/PhysicsComponent.h"

/**
 * @class Entity
 * @brief Classe base para entidades no jogo.
 * 
 * Esta é uma classe abstrata que define a interface para todas as entidades no jogo.
 * As classes derivadas devem implementar os métodos puros virtuais `executar` e `salvar`.
 * @see Ente
 * @author Vitor-tml
 */
class Entity : public Ente {
protected:
    int x; ///< Coordenada x da entidade.
    int y; ///< Coordenada y da entidade.
    sf::RectangleShape caixaColisao;
    sf::Vector2f offSetColisao;

    sf::Vector2f velocidade;
    PhysicsComponent fisica;
    bool estaNoChao;
    bool ativo;
public:
    /**
     * @brief Construtor padrão da classe Entity.
     * Inicializa as coordenadas x e y para 0.
     */
    Entity(int xx = 0, int yy = 0);
    Entity(int xx, int yy, float offSetColisorX, float offSetColisorY, sf::Texture& textura);
    /**
     * @brief Destruidor da classe Entity.
     * O destruidor é virtual para garantir a destruição correta das classes derivadas, nessa classe coloca as coordenadas em -1.
     */
    virtual ~Entity() {};
    sf::RectangleShape getCaixaColisao() const;

    /**
     * @brief Método puramente virtual para executar a lógica da entidade.
     * e
     * Este método deve ser implementado pelas classes derivadas para definir o comportamento específico da entidade.
     */
    virtual void executar() = 0;
    virtual void executar(float deltaTime) = 0;
    /**
     * @brief Método puramente virtual para salvar o estado da entidade.
     * 
     * Este método deve ser implementado pelas classes derivadas para definir como o estado da entidade deve ser salvo e a lógica de permanência de objeto.
     */
    virtual nlohmann::json salvar() const = 0;

    void renderizarCaixaColisao();

    void inicializarCaixaColisao();
    void inicializarCaixaColisao(int largura, int altura);
    void atualizarCaixaColisao();

    sf::Vector2f getPosicao() const { return sf::Vector2f(x, y);}
    
    void setVelocidade(const sf::Vector2f& novaVelocidade);
    sf::Vector2f getVelocidade() const;

    void setNoChao(bool noChao);
    bool getNoChao() const;

    void setPosicao(int xx, int yy);
    void setPosicao(sf::Vector2f posicao);

    int getID() const { return id; }
    void verificarLimitesTela();
    int getExecutar() const { return ativo;}
    void setExecutar(bool r) { ativo = r;}
};

#endif
