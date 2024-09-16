#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "../Entity.h"

class Character : public Entity {
private:
    int vida;
    int ataque;
public:
    Character(sf::Texture &textura, int x = 0, int y = 0,  int life = -1 , int atack = -1);
    ~Character();
    virtual void executar(float deltaTime) override;
    // virtual void colidiu(Entity* other) = 0;
    // virtual void colidiuComTile(Entity* e) = 0;

};
#endif