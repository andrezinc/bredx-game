#include "MapLoader.h"
#include <json.hpp>
using namespace nlohmann;
#include <fstream>
#include <iostream>

bool loadMapFromFile(const std::string& filename, MapData& mapData) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "O arquivo " << filename << " nao pode ser aberto." << std::endl;
        return false;
    }

    json j;
    file >> j;

    mapData.tileSize = j["tileSize"];
    mapData.mapWidth = j["mapWidth"];
    mapData.mapHeight = j["mapHeight"];

    for (const auto& layer : j["layers"]) {
        Layer l;
        l.name = layer["name"];
        l.collider = layer["collider"];
        for (const auto& tile : layer["tiles"]) {
            Tile t;
            t.id = std::stoi(tile["id"].get<std::string>());
            t.x = tile["x"];
            t.y = tile["y"];
            l.tiles.push_back(t);
        }
        mapData.layers.push_back(l);
    }

    return true;
}