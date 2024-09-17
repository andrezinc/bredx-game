#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H

#include "TileMap.h"
#include <string>

namespace TileEngine {

/**
 * @brief Carrega os dados do mapa a partir de um arquivo JSON.
 * 
 * Esta função abre o arquivo JSON especificado, lê os dados e preenche a
 * estrutura `MapData` com as informações do mapa, incluindo tamanho do tile, largura
 * e altura do mapa, e camadas com tiles.
 * 
 * @param filename Nome do arquivo JSON que contém os dados do mapa.
 * @param mapData Referência para a estrutura `MapData` onde os dados do mapa serão armazenados.
 * @return Retorna true se o carregamento foi bem-sucedido; caso contrário, retorna false.
 */
bool loadMapFromFile(const std::string& filename, MapData& mapData);
}
#endif // _MAP_LOADER_H