#pragma once
#include "../engine/Renderer/Renderer.h"
#include "../engine/CollisionManager/CollisionManager.h"
#include "./Entity/Entity.h"
#include "./Entity/Character/Player/Player.h"
#include "../engine/TileMap/TileMap.h"
#include "../engine/TileMap/MapLoader.h"
#include <vector>
class Game
{
private:
    Gerenciador::Renderer* janela; // Testar se essa é a primeira instância
    Gerenciador::CollisionManager gColisao;
    MapData mapData;
    TileMap map;
    sf::Clock clock;
    float deltaTime;

    Player *player;
    std::vector<Entity*> lEntidades;    
public:
    Game();
    ~Game();
    void executar();
};
