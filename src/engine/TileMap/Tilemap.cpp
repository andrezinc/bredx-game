#include "TileMap.h"

TileMap::TileMap() {}
TileMap::~TileMap() {}

bool TileMap::loadFromMapData(const std::string& tileset, const MapData& mapData) 
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(mapData.mapWidth * mapData.mapHeight * 4);

    for (const auto& layer : mapData.layers) {
        for (const auto& tile : layer.tiles) {
            int tileNumber = tile.id;

            int tu = tileNumber % (m_tileset.getSize().x / mapData.tileSize);
            int tv = tileNumber / (m_tileset.getSize().x / mapData.tileSize);

            sf::Vertex* quad = &m_vertices[(tile.x + tile.y * mapData.mapWidth) * 4];

            quad[0].position = sf::Vector2f(tile.x * mapData.tileSize, tile.y * mapData.tileSize);
            quad[1].position = sf::Vector2f((tile.x + 1) * mapData.tileSize, tile.y * mapData.tileSize);
            quad[2].position = sf::Vector2f((tile.x + 1) * mapData.tileSize, (tile.y + 1) * mapData.tileSize);
            quad[3].position = sf::Vector2f(tile.x * mapData.tileSize, (tile.y + 1) * mapData.tileSize);

            quad[0].texCoords = sf::Vector2f(tu * mapData.tileSize, tv * mapData.tileSize);
            quad[1].texCoords = sf::Vector2f((tu + 1) * mapData.tileSize, tv * mapData.tileSize);
            quad[2].texCoords = sf::Vector2f((tu + 1) * mapData.tileSize, (tv + 1) * mapData.tileSize);
            quad[3].texCoords = sf::Vector2f(tu * mapData.tileSize, (tv + 1) * mapData.tileSize);
        }
    }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Aplica a transformação
    states.transform *= getTransform();

    // Aplica a textura dos tiles
    states.texture = &m_tileset;

    // Desenha o vertex array
    target.draw(m_vertices, states);
}
