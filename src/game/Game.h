#pragma once
#include "../engine/Renderer/Renderer.h"
#include "./Entity/Entity.h"
#include "../engine/TileMap/TileMap.h"
#include "../engine/TileMap/MapLoader.h"
class Game
{
private:
    Gerenciador::Renderer* janela = Gerenciador::Renderer::getInstance(); // Testar se essa é a primeira instância
    MapData mapData;
    TileMap map;
    sf::Clock clock;
    float deltaTime;

    Entity player;
public:
    Game();
    ~Game();
    void executar();
};
