#ifndef TILEENTITY_H
#define TILEENTITY_H

#include "../../game/Entity/Entity.h"

class TileEntity : public Entity {
public:
    TileEntity(int x, int y, int width, int height) {
        hitBox.setPosition(x, y);
        hitBox.setSize(sf::Vector2f(width, height));
        hitBox.setFillColor(sf::Color::Transparent);
    }

    void executar(float deltaTime) override {
        // Tiles geralmente não têm lógica de execução
    }

    void colidiu(Entity* other) override {
        // Tratamento de colisão com outros objetos
    }
};

#endif // TILEENTITY_H
