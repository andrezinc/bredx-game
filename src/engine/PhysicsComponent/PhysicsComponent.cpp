#include "PhysicsComponent.h"
#include <iostream>

float PhysicsComponent::gravidade = 980.f;
PhysicsComponent::PhysicsComponent(sf::Vector2f  *position, sf::Vector2f *speed)
{
    velocidade = speed;
    posicao = position;
}

void PhysicsComponent::aplicaFisica(float deltaTime) // mudar para x e y o move
{
    // Aplica a gravidade
    // if(posicao->y < 500){
    //     velocidade->y += gravidade * deltaTime;
    // }else{
    //     velocidade->y = 0;
    // }
    
    posicao->x += velocidade->x * deltaTime;
    posicao->y += velocidade->y * deltaTime;
}