#include "Player.h"

Player::Player(sf::Texture& textura, int x, int y, int life, int atack, int points)
       :Character(textura, x, y,  life, atack)
{
    pontos = points;
}
Player::~Player()
{}

void Player::executar(float deltaTime)
{
    // Movimentação básica para testes
    velocidade.x = 0.f; // Reseta a velocidade horizontal

    float speed  = 200.f; // pixels per second

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    //     velocidade.y -= speed; // Mover para cima
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    //     velocidade.y += speed;  // Mover para baixo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocidade.x -= speed; // Mover para a esquerda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocidade.x += speed;  // Mover para a direita

    // Verifica a entrada do teclado para pular
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        fisica.pular(300.f);
    }

    Character::executar(deltaTime);
}