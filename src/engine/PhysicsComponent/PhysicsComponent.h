#ifndef _FISICA_H
#define _FISICA_H
#include <SFML/Graphics.hpp>

/**
 * @class PhysicsComponent
 * @brief Gerencia a física aplicada a entidades no jogo.
 * 
 * A classe de Componente de Física lida com a aplicação de física básica a entidades, 
 * como a gravidade e o impulso do pulo. 
 * 
 * @author Vitor-tml
 */
class PhysicsComponent{
private:
    // static float gravidade; -> mudar para estático
    float gravidade;
    float alturaPulo;
public:
    /**
     * @brief Construtora do componente de física
     * @param gravity aceleração da gravidae no jogo
     * @param jumpHeigth altura do pula da entidade referência
     */
    PhysicsComponent(float gravity = 980.f, float jumpHeight = 300.f);
    ~PhysicsComponent(){};
    /**
     * @brief Aplica física a entidade/sprite referenciada
     * @param velocidade velocidade horizontal e vertical da entidade
     * @param deltaTime tempo passado a chamada
     * @param estaNoChao flag para evitar pulos infinitos
     */
    void aplicaFisica(sf::Sprite& entidade, sf::Vector2f& velocidade, float deltaTime, bool& estaNoChao);
    /**
     * @brief Contem a altura do pulo da entidade a que pertence
     * @return Altura do pulo da entidade
     */
    float getPulo()const;
};
#endif