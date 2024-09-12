#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y) : 
        Ente(),
        fisica(&posicao, &velocidade)
{
    setOrigin();
    posicao = sf::Vector2f(x, y);
}

Entity::Entity(sf::Texture &textura, int x, int y) : 
        Ente(textura),
        hitBox(sf::Vector2f(0.f, 0.f)),
        fisica(&posicao, &velocidade)
{
    setOrigin();
    posicao = sf::Vector2f(x, y);
}

void Entity::setOrigin()
{
    // Origem embaixo no meio
    sf::FloatRect tamanho = sprite.getGlobalBounds();
    sprite.setOrigin(tamanho.width/2, tamanho.height);
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
    // Movimentação básica para testes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocidade.y = -100.f; // Mover para cima
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocidade.y = 100.f;  // Mover para baixo
    else
        velocidade.y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocidade.x = -100.f; // Mover para a esquerda
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocidade.x = 100.f;  // Mover para a direita
    else
        velocidade.x = 0.f;

    fisica.aplicaFisica(deltaTime);
    sprite.setPosition(posicao);
}