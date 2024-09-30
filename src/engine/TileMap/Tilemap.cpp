#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <iomanip>
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
    coordenadas.resize(height, std::vector<sf::Vector2f>(width));
    // Convertendo matriz linear para quadrada
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrizTiles[i][j] =  vetorTiles[i * width + j];
            coordenadas[i][j] = sf::Vector2f(j * tileSize, i * tileSize);
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

sf::Vector2f TileMap::getOrigem() const
{
    return sf::Vector2f( 0 * tileSize, height * tileSize);
}

void TileMap::atualizaMapa(sf::View& view)
{

    // Dentro de TileMap::atualizaMapa
    std::cout << std::fixed << std::setprecision(4); // Define a precisão para 4 casas decimais

    // Obter as coordenadas da view atual
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    sf::FloatRect viewRect(
        viewCenter.x - viewSize.x / 2.f, // left
        viewCenter.y - viewSize.y / 2.f, // top
        viewSize.x, // width
        viewSize.y  // height
    );

    sf::FloatRect  mapRect(
        coordenadas[0][0].x,
        coordenadas[0][0].y,
        tileSize * width,
        tileSize * height
    );


    // std::cout << "Direita  - View: " << viewRect.left + viewRect.width << " Map: " << mapRect.left << std::endl;

    if (viewRect.left < mapRect.left) // Condição para atualizar o mapa para a direita
    {
        std::cout << "Atualizando mapa" << std::endl;
        std::vector<sf::Vector2f> coordenadasNovas;
        coordenadasNovas.resize(height);

        for (int i = 0; i < height; i++)
        {
            coordenadas[i][width - 1] = coordenadas[i][0] - sf::Vector2f(tileSize, 0); // Atualiza a nova posição da coluna à direita
            coordenadasNovas[i] = coordenadas[i][width - 1];
        }

        for (int i = 0; i < height; i++)
        {
            for (int j = width - 1; j > 0; j--)
            {
                coordenadas[i][j] = coordenadas[i][j - 1]; // Move a coluna para a direita
            }
            coordenadas[i][0] = coordenadasNovas[i]; // Define a nova posição da primeira coluna
        }
    }
    // std::cout << "Esquerda - View: " << viewRect.left + viewRect.width << " Map: " << mapRect.left +  mapRect.width << std::endl;
    if(viewRect.left + viewRect.width >  mapRect.left +  mapRect.width)
    {
        std::cout << "Atualizando mapa" << std::endl;
        std::vector<sf::Vector2f>  coordenadasNovas;
        coordenadasNovas.resize(height);
        for(int i = 0; i < height; i++)
        {
            coordenadas[i][0] = coordenadas[i][width - 1] + sf::Vector2f(tileSize, 0);
            coordenadasNovas[i] = coordenadas[i][0];
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width - 1; j++) {
                coordenadas[i][j] = coordenadas[i][j + 1]; // Move a coluna para a esquerda
            }
            coordenadas[i][width - 1] = coordenadasNovas[i];
        }
    }

}
}