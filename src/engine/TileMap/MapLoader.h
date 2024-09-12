#ifndef _MAP_LOADER_H
#define _MAP_LOADER_H
#include "TileMap.h"
#include <string>

bool loadMapFromFile(const std::string& filename, MapData& mapData);

#endif