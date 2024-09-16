#ifndef _COLLISIONMANAGER_H
#define _COLLISIONMANAGER_H
#include "../../game/Entity/Entity.h"
#include "../../game/Entity/Character/Player/Player.h"
#include <unordered_set>

namespace Gerenciador{
class CollisionManager{
private:
    Player *player;
    std::unordered_set<Entity*> entidades; 
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