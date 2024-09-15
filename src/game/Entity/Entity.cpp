#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y) : 
        Ente(),
        fisica(&posicao, &velocidade),
        hitBoxSize(sf::Vector2f(0.f, 0.f)),
        hitBoxOffset(sf::Vector2f(0.f, 0.f))
{
    setOrigin();    // Isso serve para todas as entidades? ou só para as que se movem?
    posicao = sf::Vector2f(x, y);
    criarHitBox();  // Inicializa a hitbox
}

Entity::Entity(sf::Texture &textura, int x, int y) : 
        Ente(textura),
        hitBox(sf::Vector2f(0.f, 0.f)),
        fisica(&posicao, &velocidade)
{
    setOrigin();
    posicao = sf::Vector2f(x, y);
    criarHitBox();  // Inicializa a hitbox
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
    sprite.setPosition(posicao);
}

sf::Vector2f Entity::getPosicao() const
{
    return posicao;
}

void Entity::executar(float deltaTime)
{
    float speed  = 200.f; // pixels per second

    // Movimentação básica para testes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocidade.y = -speed; // Mover para cima
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocidade.y = speed;  // Mover para baixo
    else
        velocidade.y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocidade.x = -speed; // Mover para a esquerda
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocidade.x = speed;  // Mover para a direita
    else
        velocidade.x = 0.f;

    fisica.aplicaFisica(deltaTime);
    sprite.setPosition(posicao);
    atualizaHitBox();
}

void Entity::criarHitBox()
{
    hitBox.setFillColor(sf::Color::Transparent); // Tornar a hitbox visível sem preenchimento
    hitBox.setOutlineColor(sf::Color::Red); // Cor da borda da hitbox
    hitBox.setOutlineThickness(1.f); // Espessura da borda  
    
    // Se a hitbox personalizada não for definida, use o tamanho da sprite
    if (hitBoxSize == sf::Vector2f(0.f, 0.f))
    {
        hitBoxSize = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    }

    // Atualiza o tamanho e a posição da hitbox com base na sprite e offset
    hitBox.setSize(hitBoxSize);
}

void Entity::setHitBoxSize(sf::Vector2f size)
{
    hitBoxSize = size;
    criarHitBox();  // Atualiza a hitbox ao mudar o tamanho
}

void Entity::setHitBoxOffset(sf::Vector2f offset)
{
    hitBoxOffset = offset;
    criarHitBox();  // Atualiza a hitbox ao mudar o offset
}

void Entity::atualizaHitBox()
{
    // Ajustar a posição da hitbox para alinhar corretamente com a sprite
    hitBox.setPosition(sprite.getPosition() - sprite.getOrigin() + hitBoxOffset);
}

void Entity::setTexture(sf::Texture& textura)
{
    std::cout << "Configurando textura!" << std::endl;
    sprite.setTexture(textura);
}

void Entity::setSize(const sf::Vector2f& size) {
    sf::Vector2f currentSize(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
    sf::Vector2f scale(size.x / currentSize.x, size.y / currentSize.y);
    sprite.setScale(scale);
}

void Entity::colidiuComTile(Entity* tile) // Mudar depois para não usar métodos da sprite
{
    // Obtém as bounding boxes das entidades
    sf::FloatRect entidadeBounds = this->getHitBox().getGlobalBounds();
    sf::FloatRect tileBounds = tile->getHitBox().getGlobalBounds();

    // Calcula a interseção entre as bounding boxes
    sf::FloatRect interseccao;
    if (entidadeBounds.intersects(tileBounds, interseccao))
    {
        // Determina o eixo de menor interseção
        if (interseccao.width < interseccao.height)
        {
            // Colisão horizontal
            if (entidadeBounds.left < tileBounds.left)
            {
                // Colisão pela esquerda do tile
                this->posicao.x = (tileBounds.left - entidadeBounds.width / 2.0f) + ( this->sprite.getOrigin().x - entidadeBounds.width/ 2.0f);
            }
            else
            {
                // Colisão pela direita do tile
                this->posicao.x = ( tileBounds.left + tileBounds.width + entidadeBounds.width / 2.0f) - (this->sprite.getOrigin().x - entidadeBounds.width/ 2.0f);
            }
            this->velocidade.x = 0; // Para a velocidade horizontal
        }
        else
        {
            // Colisão vertical
            if (entidadeBounds.top < tileBounds.top)
            {
                // Colisão pelo topo do tile
                this->posicao.y = tileBounds.top - entidadeBounds.height + this->sprite.getOrigin().y;
            }
            else
            {
                // Colisão pela base do tile
                // this->posicao.y = tileBounds.top + tileBounds.height + entidadeBounds.height - this->sprite.getOrigin().y;
                this->posicao.y = (tileBounds.top + tileBounds.height) + entidadeBounds.height; 
            }
            this->velocidade.y = 0; // Para a velocidade vertical
        }

        // Atualiza a posição da sprite e da hitbox
        this->sprite.setPosition(this->posicao);
        this->atualizaHitBox();
    }
}
