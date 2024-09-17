#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp> 
#include <vector> 
#include <string> 
#include "TileEntity.h"

/**
 * @brief Componentes responsáveis pelo carregamento, gerenciamento e renderização do mapa
 */
namespace TileEngine {

/**
 * @struct Tile
 * @brief Estrutura que representa um tile no mapa.
 * 
 * Esta estrutura armazena informações sobre um tile individual, incluindo seu ID e
 * suas coordenadas no mapa.
 */
struct Tile {
    int id; ///< ID do tile
    int x;  ///< Coordenada X do tile no mapa
    int y;  ///< Coordenada Y do tile no mapa
};

/**
 * @struct Layer
 * @brief Estrutura que representa uma camada no mapa.
 * 
 * Esta estrutura armazena informações sobre uma camada de tiles, incluindo o nome da
 * camada, a lista de tiles e se a camada possui colisores.
 */
struct Layer {
    std::string name;        ///< Nome da camada
    std::vector<Tile> tiles; ///< Lista de tiles na camada
    bool collider;           ///< Indica se a camada tem colisor
};

/**
 * @struct MapData
 * @brief Estrutura que armazena os dados do mapa.
 * 
 * Esta estrutura contém informações sobre o mapa, incluindo o tamanho dos tiles, a
 * largura e a altura do mapa, e as camadas que compõem o mapa.
 */
struct MapData {
    int tileSize;              ///< Tamanho do tile em pixels
    int mapWidth;              ///< Largura do mapa em tiles
    int mapHeight;             ///< Altura do mapa em tiles
    std::vector<Layer> layers; ///< Lista de camadas no mapa
};

/*
 * @class TileMap
 * @brief Classe para gerenciar e renderizar tilemaps.
 * 
 * A classe `TileMap` carrega uma textura de tiles e organiza esses tiles em um mapa.
 * Utiliza `sf::VertexArray` para armazenar os vértices dos tiles e `sf::Texture` para
 * a textura dos tiles. É responsável pela renderização e gerenciamento dos tiles no mapa.
 */
class TileMap : public sf::Drawable, public sf::Transformable {
private:
    std::vector<Entity*> entidades; ///< Lista de entidades associadas ao mapa
    sf::VertexArray m_vertices; ///< Vértices dos tiles para renderização
    sf::Texture m_tileset; ///< Textura dos tiles
    /**
     * @brief Método para desenhar o TileMap.
     * Este método é chamado internamente pelo SFML para desenhar o TileMap na tela.
     * @param target Destino de renderização.
     * @param states Estados de renderização.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    /**
     * @brief Construtor da classe TileMap.
     * Inicializa uma nova instância da classe `TileMap`.
     */
    TileMap();

    /**
     * @brief Destruidor da classe TileMap.
     * Limpa os recursos utilizados pela instância da classe `TileMap`.
     */
    ~TileMap();

    /**
     * @brief Carrega o tileset e cria o mapa.
     * Este método carrega a textura dos tiles e utiliza os dados do mapa para criar
     * o mapa no TileMap.
     * @param tileset Caminho para a textura dos tiles.
     * @param mapData Dados pré-carregados do mapa.
     * @return Retorna true se o tileset foi carregado com sucesso, false caso contrário.
     */
    bool loadFromMapData(const std::string& tileset, const MapData& mapData);

    /**
     * @brief Obtém a lista de entidades associadas ao mapa.
     * Este método retorna uma lista de ponteiros para entidades que estão associadas
     * ao mapa.
     * @return Vetor de ponteiros para as entidades.
     */
    std::vector<Entity*> getTiles() const;
};
}

#endif // TILEMAP_H