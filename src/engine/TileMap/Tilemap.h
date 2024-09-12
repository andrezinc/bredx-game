#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @class Tilemap
 * @brief Classe para gerenciar e renderizar tilemaps.
 * 
 * A classe Tilemap carrega uma textura de tiles e organiza esses tiles em um mapa.
 * Utiliza sf::VertexArray para armazenar os vértices dos tiles e sf::Texture para a textura dos tiles.
 */
class Tilemap : public sf::Drawable, public sf::Transformable {
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Tilemap();
    ~Tilemap();
    /**
     * @brief Carrega o tileset e cria o mapa.
     * @param tileset Caminho para a textura dos tiles.
     * @param tileSize Tamanho de cada tile (largura e altura).
     * @param tiles Vetor de inteiros representando o índice dos tiles no tileset.
     * @param width Largura do mapa em número de tiles.
     * @param height Altura do mapa em número de tiles.
     * @return true se o tileset foi carregado com sucesso, false caso contrário.
     */
    bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height);

};

#endif // TILEMAP_H
