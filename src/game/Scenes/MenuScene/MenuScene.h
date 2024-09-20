#ifndef _MENUSCENE_H
#define _MENUSCENE_H

#include "../../../engine/CollisionManager/CollisionManager.h"
#include "../../../engine/TileMap/TileMap.h"
#include "../../../engine/TileMap/MapLoader.h"
#include "../../../engine/SceneManager/Scene.h"
#include "../../Entity/Entity.h" 

class MenuScene : public Scene {
private:
    sf::Sprite background;
    sf::Sprite button[2];
    sf::Sprite select[2];
    sf::Sound music;
    int selectedButton; // Variável para controlar qual botão está selecionado
    void selecionarBotao(int index); // Método para selecionar um botão

public:
    MenuScene();
    ~MenuScene();
    void inicializar() override;
    void executar() override;
    void renderizar() override;
    void processarEventos(const sf::Event &evento) override;
    void finalizar() override;
};
#endif