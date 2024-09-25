#include "TileMap.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
using namespace nlohmann;

namespace TileEngine{
    
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

    std::vector<int> vetorTiles = j["layers"][0]["data"].get<std::vector<int>>();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << "Elemento [" << i << "][" << j << "] = " 
                      << vetor1D[i * n + j] << std::endl;
        }
    }

}

TileEntity::TileEntity(sf::Texture &textura, int x, int y, int xTile, int yTile, int tileSize)
           :Entity(textura, x, y)
{
    sprite.setTextureRect(sf::IntRect(xTile, yTile, tileSize, tileSize));
}
}