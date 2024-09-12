#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../../engine/Ente/Ente.h"
#include "../../engine/PhysicsComponent/PhysicsComponent.h"

/**
 * @class Entity
 * @brief Classe base para entidades no jogo.
 * 
 * Esta é uma classe abstrata que define a interface para todas as entidades no jogo.
 * As classes derivadas devem implementar os métodos puros virtuais `executar`.
 * @see Ente
 * @author Vitor-tml
 */
class Entity : public Ente {
protected:
    sf::Vector2f posicao;
    sf::Vector2f velocidade;
    sf::RectangleShape hitBox;
    PhysicsComponent fisica;
public:
    /**
     * @brief Construtor padrão da classe Entity.
     * Inicializa as coordenadas x e y para 0.
     */
    Entity(int x = 0, int y = 0);

    /**
     * @brief Construtora com parâmetro de posição e textura.
     * @param x coordenada no eixo x 
     * @param y coordenada no eixo y
     * @param textura objeto textura do SFML
     */
    Entity(sf::Texture &textura,  int x = 0, int y = 0);

    /**
     * @brief Destruidor da classe Entity.
     * O destruidor é virtual para garantir a destruição correta das classes derivadas.
     */
    virtual ~Entity() {}

    /**
     * @brief Método para executar a lógica da entidade.
     * Este método deve ser implementado pelas classes derivadas para definir o comportamento específico da entidade.
     */
    void executar(float deltaTime);

    void setPosicao(int x, int y);
    void setPosicao(sf::Vector2f novaPosicao);
    sf::Vector2f getPosicao() const;
};

#endif // _ENTITY_H_
