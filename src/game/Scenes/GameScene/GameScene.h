#ifndef _GAMESCENE_H
#define _GAMESCENE_H

#include "../../../engine/CollisionManager/CollisionManager.h"
#include "../../../engine/TileMap/TileMap.h"
#include "../../../engine/TileMap/MapLoader.h"
#include "../../../engine/SceneManager/Scene.h"
#include "../../../engine/SceneManager/Scene.h"
#include "../../../engine/SceneManager/SceneManager.h"
#include "../MenuScene/MenuScene.h"
#include "../../Entity/Entity.h" 

class GameScene : public Scene {
private:
    Gerenciador::CollisionManager gColisao; ///< Instância do gerenciador de colisões
    TileEngine::MapData mapData;            ///< Dados do mapa carregados
    TileEngine::TileMap map;                ///< Instância do mapa de tiles
    Player* player;
    std::vector<Entity*> lEntidades;
    sf::Sound musica;
public:
    GameScene();
    ~GameScene();
    void inicializar();
    void executar();
    void renderizar();
    void finalizar();
    void processarEventos(const sf::Event &evento);
};
#endif