#include "PhysicsComponent.h"
#include <iostream>
PhysicsComponent::PhysicsComponent(float gravity, float jumpHeight)
    : gravidade(gravity), alturaPulo(jumpHeight){}

void PhysicsComponent::aplicaFisica(sf::Sprite& entidade, sf::Vector2f& velocidade, float deltaTime, bool& estaNoChao) // mudar para x e y o move
{
    // Aplica a gravidade
    velocidade.y += gravidade * deltaTime;
    // Verifica colisão com o chão ou outras plataformas
    if (estaNoChao || entidade.getPosition().y >= 700)
    {
        // Apenas aplicando a gravidade se não estiver no chão
        velocidade.y = 0;
    }
    // Atualiza a posição
    entidade.move(velocidade * deltaTime);
    
    
}

float PhysicsComponent::getPulo()const
{
    return alturaPulo; 
}