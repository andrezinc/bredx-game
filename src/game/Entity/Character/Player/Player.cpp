#include "Player.h"

Player::Player(sf::Texture& textura, int x, int y, int life, int atack, int points)
       :Character(textura, x, y,  life, atack)
{
    pontos = points;
    velocidadeHorizontal = 200.f;
    
    // ==== Caso precise mudar tamanho do sprite
    // setSize(sf::Vector2f(64, 64));
    // sf::FloatRect oldSize =  getHitBox().getGlobalBounds();
    // sf::Vector2f newSize(50, 64);

    // setHitBoxSize(newSize);
    // sf::Vector2f hitBoxOffset = sf::Vector2f((oldSize.width - newSize.x) / 2, oldSize.height - (newSize.y + 5));
    // setHitBoxOffset(hitBoxOffset);
}

void Player::executar(float deltaTime)
{
    velocidade.x = 0.f; // Reseta a velocidade horizontal para não ter aceleração infinita

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocidade.x -= velocidadeHorizontal; // Mover para a esquerda
        setSize(sf::Vector2f(-64, 64));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocidade.x += velocidadeHorizontal;  // Mover para a direita
        setSize(sf::Vector2f(64, 64));
    }

    // // Debug sem gravidade
    // velocidade.y = 0.f;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    //     velocidade.y -= velocidadeHorizontal;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    //     velocidade.y += velocidadeHorizontal;
    // }

    // Verifica a entrada do teclado para pular
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        pular(); // atualizar essa função
    }

    Character::executar(deltaTime); // Chama o executar da classe pai que aplica a movimentação
}

void Player::pular()
{
    fisica.pular();
}