#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H
#include "../../game/Entity/Entity.h"
#include <vector>

namespace Gerenciador{
class CollisionManager{
private:
    std::vector<Entity*> entidades; 
public:
    CollisionManager();
    ~CollisionManager();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void tratarColisoes();
    bool verificaColisao(Entity* a, Entity* b);
};
} // namespace Gerenciador
#endif