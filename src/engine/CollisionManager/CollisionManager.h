#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H
#include "../../game/Entity/Entity.h"
#include <vector>

class CollisionManager{
public:
    std::vector<Entity*> entidades; 
private:
    CollisionManager();
    ~CollisionManager();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void tratarColisoes();
    bool verificaColisao(Entity* a, Entity* b);
};
#endif