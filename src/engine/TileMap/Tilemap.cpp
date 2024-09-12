#include "Tilemap.h"

Tilemap::Tilemap() {}
Tilemap::~Tilemap() {}

bool Tilemap::load(const std::string &tileset, sf::Vector2u tileSize, const std::vector<int> &tiles, unsigned int width, unsigned int height)
{
    // Carrega a textura do tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // Redimensiona o vertex array para o tamanho do mapa
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // Popula o vertex array com um quad para cada tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // Obtem o índice atual do tile
            int tileNumber = tiles[i + j * width];

            // Encontra sua posição no tileset 
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // Obtem um ponteiro para o quad atual no vertex array
            sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

            // Define suas quatro posições
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // Define suas quatro coordenadas de textura
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Aplica a transformação
    states.transform *= getTransform();

    // Aplica a textura dos tiles
    states.texture = &m_tileset;

    // Desenha o vertex array
    target.draw(m_vertices, states);
}
