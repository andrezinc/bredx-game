#ifndef _PLAYER_H
#define _PLAYER_H

#include "../Character.h"

class Player : public Character{
private:
    int pontos;
public:
    Player(sf::Texture& textura, int x = 0, int y = 0, int life = -1, int atack = -1, int points = 0);
    ~Player();
    void executar(float deltaTime) override;
};
#endif