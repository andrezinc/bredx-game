#ifndef _TILEMAP_H
#define _TILEMAP_H

#include <string>
#include <vector>
#include "../../game/Entity/Entity.h"
namespace TileEngine {

class TileEntity : public Entity {
private:
    bool colisao;
public:
    TileEntity(sf::Texture &textura, int x, int y, int xTile, int yTile, int tileSize);
    ~TileEntity(){};
    void executar(float deltaTime) override {};
    void colidiuComTile(Entity* e) override {};
    void colidiu(Entity* e) override {};
};
class TileMap {
private:
    int tileSize;
    int height;
    int width;
    std::vector<std::vector<int>> matrizTiles;
    std::vector<TileEntity*> lTiles;
    sf::Texture sheet;
public:
    TileMap();
    ~TileMap();
    void loadMapFromFile(const std::string& filename);
    void loadSheet(sf::Texture& textura);
    std::vector<Entity*> getEntitys();
};
}
#endif