#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TileEntity.h"

struct  Tile {
    int id;
    int x;
    int y;
};

struct Layer {
    std::string name;
    std::vector<Tile> tiles;
    bool collider;
};

struct MapData {
    int tileSize;
    int mapWidth;
    int mapHeight;
    std::vector<Layer> layers;
};

/**
 * @class Tilemap
 * @brief Classe para gerenciar e renderizar tilemaps.
 * 
 * A classe Tilemap carrega uma textura de tiles e organiza esses tiles em um mapa.
 * Utiliza sf::VertexArray para armazenar os vértices dos tiles e sf::Texture para a textura dos tiles.
 */
class TileMap : public sf::Drawable, public sf::Transformable {
private:
    std::vector<Entity*> entidades;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    TileMap();
    ~TileMap();
    /**
     * @brief Carrega o tileset e cria o mapa.
     * @param tileset Caminho para a textura dos tiles.
     * @param mapData Dados pré-carregados do mapa
     * @return true se o tileset foi carregado com sucesso, false caso contrário.
     */
    bool loadFromMapData(const std::string& tileset, const MapData& mapData);

    std::vector<Entity*> getTiles() const;

};

#endif // TILEMAP_H
