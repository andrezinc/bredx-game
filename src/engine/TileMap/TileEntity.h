#ifndef TILEENTITY_H
#define TILEENTITY_H

#include "../../game/Entity/Entity.h"
#include <iostream>

class TileEntity : public Entity {
public:
    TileEntity(sf::Texture& textura, int tileSize, int spriteX, int spriteY, int x, int y)
    : Entity(textura, x * tileSize, y * tileSize)
    {
        sprite.setPosition(x * tileSize, y * tileSize);
        sprite.setTextureRect(sf::IntRect(spriteX * tileSize, spriteY * tileSize,  tileSize, tileSize));
        setHitBoxSize(sf::Vector2f(tileSize, tileSize));
        atualizaHitBox();
        // std::cout<< "Textura: "  << sprite.getGlobalBounds().width << "x" << sprite.getGlobalBounds().width
        //          << " Tile: "    << tileSize 
        //          << " HitBox: "    << getHitBox().getGlobalBounds().height << "x" <<  getHitBox().getGlobalBounds().width
        //          << std::endl;

    }

    void executar(float deltaTime) override {
        setPosicao(posicao);
    }

    void colidiu(Entity* other) override {
        other->colidiuComTile(this);
    }
    void colidiuComTile(Entity* e) override
    {
        // std::cout << "Colidiu com tile" << std::endl;
    }

};

#endif // TILEENTITY_H
