#include "CollisionManager.h"
#include <iostream>

namespace Gerenciador{
CollisionManager::CollisionManager()
{
    entidades.clear();
}
CollisionManager::~CollisionManager()
{
    entidades.clear();
}

void CollisionManager::addEntity(Entity* entity)
{
    if(entity == nullptr){
        std::cout << "Ponteiro nulo, nao foi possivel adicionar entidade!" << std::endl;
    } 
    entidades.push_back(entity);
}


void CollisionManager::removeEntity(Entity* entity)
{
    if(entity == nullptr){
        std::cout << "Ponteiro nulo, nao foi possivel remover entidade!" << std::endl;
        return;
    }

    for (std::vector<Entity*>::iterator it = entidades.begin(); it != entidades.end(); ++it) {
        if (*it == entity) {
            entidades.erase(it);
            return;
        }
    }

    std::cout << "Entidade nao encontrada!" << std::endl;
}

void CollisionManager::tratarColisoes()
{
    for(int i = 0; i < entidades.size(); i++)
        for(int j = i + 1; i < entidades.size(); i++){
            if(verificaColisao(entidades[i], entidades[j]))
            {
                entidades[i]->colidiu(entidades[j]);
                entidades[j]->colidiu(entidades[i]);
            }
        }

}

bool CollisionManager::verificaColisao(Entity* a, Entity* b)
{
    return a->getHitBox().getGlobalBounds().intersects(b->getHitBox().getGlobalBounds());
}

}