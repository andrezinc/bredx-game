#pragma once
#include "../engine/Renderer/Renderer.h"
#include "./Entity/Entity.h"
#include "../engine/TileMap/TileMap.h"
#include "../engine/TileMap/MapLoader.h"
#include <vector>
class Game
{
private:
    Gerenciador::Renderer* janela = Gerenciador::Renderer::getInstance(); // Testar se essa é a primeira instância
    MapData mapData;
    TileMap map;
    sf::Clock clock;
    float deltaTime;

    Entity player;
    std::vector<Entity*> lEntidades;    
public:
    Game();
    ~Game();
    void executar();
};
