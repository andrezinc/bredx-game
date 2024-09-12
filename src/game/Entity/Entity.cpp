#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y) : 
        Ente(),
        fisica(&posicao, &velocidade)
{
    // Origem embaixo no meio
    sf::FloatRect tamanho = sprite.getGlobalBounds();
    sprite.setOrigin(tamanho.width/2, tamanho.height);
    
    posicao = sf::Vector2f(x, y);
}

Entity::Entity(sf::Texture &textura, int x, int y) : 
        Ente(textura),
        hitBox(sf::Vector2f(0.f, 0.f)),
        fisica(&posicao, &velocidade)
{
    posicao = sf::Vector2f(x, y);
}

void Entity::setPosicao(int x, int y)
{
    posicao = sf::Vector2f(x, y);
}

void Entity::setPosicao(sf::Vector2f novaPosicao)
{
    posicao = novaPosicao;
}

sf::Vector2f Entity::getPosicao() const
{
    return posicao;
}

void Entity::executar(float deltaTime)
{
    std::cout << posicao.x  << " " << posicao.y << std::endl;

    fisica.aplicaFisica(deltaTime);
    sprite.setPosition(posicao);
}