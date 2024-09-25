#include "TileMap.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
using namespace nlohmann;

/**
 * @brief Componente responsável pelo carregamento do mapa no jogo
 */
namespace TileEngine{
// Tilemap
TileMap::TileMap(){}
TileMap::~TileMap(){}

void TileMap::loadMapFromFile(const std::string& filename)
{
    std::fstream arquivo(filename);

    if(!arquivo.is_open()){
        std::cout << "ERRO::TILEMAP::LOADMAPFROMFILE::Arquivo nao pode ser aberto: " << filename << std::endl;
        return;
    }

    json j;
    arquivo >> j;
    
    arquivo.close();

    tileSize = j["tilewidth"];
    height = j["height"];
    width = j["width"];

    // Matriz linearizada
    std::vector<int> vetorTiles = j["layers"][0]["data"].get<std::vector<int>>();
    // Matriz quadrada
    matrizTiles.resize(height, std::vector<int>(width));
    // Convertendo matriz linear para quadrada
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrizTiles[i][j] =  vetorTiles[i * width + j];
\
            if(matrizTiles[i][j]){
                bool tipo = (matrizTiles[i][j] == 3 || matrizTiles[i][j] == 4)? 1 : 0;
                TileEntity* novoTile = new TileEntity(sheet, j, i, matrizTiles[i][j] - 1, 0, tileSize, tipo);
                lTiles.push_back(novoTile);
            }
        }
    }
}
std::vector<Entity*> TileMap::getEntitys()
{
    std::vector<Entity*> tiles;
    for(TileEntity *t : lTiles)
        tiles.push_back(t);
    return tiles;
}
void TileMap::loadSheet(sf::Texture& textura)
{
    sheet = textura;
}

// Tile entity
TileEntity::TileEntity(sf::Texture &textura, int x, int y, int xTile, int yTile, int tileSize, bool colide)
           :Entity(textura, x * tileSize, y * tileSize, colide)
{
    sprite.setTextureRect(sf::IntRect(xTile * tileSize, yTile * tileSize, tileSize, tileSize));
    criarHitBox();
    atualizaHitBox();
}
}