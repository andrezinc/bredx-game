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

    // Dimensões e offset personalizados da hitbox
    sf::Vector2f hitBoxSize;
    sf::Vector2f hitBoxOffset;
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
    virtual void executar(float deltaTime);

    sf::RectangleShape& getHitBox()  { return hitBox; };
    void setPosicao(int x, int y);
    void setPosicao(sf::Vector2f novaPosicao);
    sf::Vector2f getPosicao() const;
    void setOrigin();

     /**
     * @brief Cria e atualiza a hitbox da entidade com base na sprite ou hitbox personalizada.
     */
    void criarHitBox();

    /**
     * @brief Define o tamanho da hitbox.
     * @param size O tamanho da hitbox.
     */
    void setHitBoxSize(sf::Vector2f size);

    /**
     * @brief Define o offset da hitbox em relação à posição da entidade.
     * @param offset O offset da hitbox.
     */
    void setHitBoxOffset(sf::Vector2f offset);

    void atualizaHitBox();

    void setTexture(sf::Texture& textura);
    void setSize(const sf::Vector2f& size);

    virtual void colidiu(Entity* other){}; 
    virtual void colidiuComTile(Entity* e);

    void setNoChao(bool noChao);
    bool getNoChao() const;
};
#endif // _ENTITY_H_
