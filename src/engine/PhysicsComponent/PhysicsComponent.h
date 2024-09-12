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
class PhysicsComponent {
private:
    static float gravidade;
    sf::Vector2f *velocidade;
    sf::Vector2f *posicao;
public:
    /**
     * @brief Construtora do componente de física
     */
    PhysicsComponent(sf::Vector2f  *position = nullptr, sf::Vector2f *speed = nullptr);

    /**
     * @brief Destrutora vazia
     */
    ~PhysicsComponent() {}

    /**
     * @brief Aplica física a entidade
     * @param deltaTime tempo passado a chamada
     */
    void aplicaFisica(float deltaTime);

};
#endif // _FISICA_H
