#include "MapLoader.h"
#include <json.hpp>
using namespace nlohmann;
#include <fstream>
#include <iostream>

namespace TileEngine {
bool loadMapFromFile(const std::string& filename, MapData& mapData) {

    std::ifstream file(filename); // Abre o arquivo com o nome fornecido
    if (!file.is_open()) { // Verifica se o arquivo foi aberto com sucesso
        std::cout << "O arquivo " << filename << " nao pode ser aberto." << std::endl; // Mensagem de erro se não conseguir abrir o arquivo
        return false; // Retorna falso para indicar falha na abertura do arquivo
    }

    json j; // Cria um objeto JSON para armazenar os dados lidos do arquivo
    file >> j; // Lê o conteúdo do arquivo JSON para o objeto JSON

    // Preenche os dados do mapa a partir do JSON
    mapData.tileSize = j["tileSize"]; // Define o tamanho do tile
    mapData.mapWidth = j["mapWidth"]; // Define a largura do mapa
    mapData.mapHeight = j["mapHeight"]; // Define a altura do mapa

    // Processa cada camada do mapa
    for (const auto& layer : j["layers"]) {
        Layer l; // Cria uma nova camada
        l.name = layer["name"]; // Define o nome da camada
        l.collider = layer["collider"]; // Define se a camada tem colisor

        // Processa cada tile da camada
        for (const auto& tile : layer["tiles"]) {
            Tile t; // Cria um novo tile
            t.id = std::stoi(tile["id"].get<std::string>()); // Define o ID do tile convertendo de string para inteiro
            t.x = tile["x"]; // Define a coordenada x do tile
            t.y = tile["y"]; // Define a coordenada y do tile
            l.tiles.push_back(t); // Adiciona o tile à lista de tiles da camada
        }
        mapData.layers.push_back(l); // Adiciona a camada à lista de camadas do mapa
    }

    return true; // Retorna verdadeiro para indicar sucesso no carregamento do mapa
}
}