#include "Game.h"
#include <iostream>
Game::Game():
janela(Gerenciador::Renderer::getInstance())
{
    janela->setTamanhoCamera(640, 320);
    if (!loadMapFromFile("../assets/map/map.json", mapData)) {
        std::cout << "Erro ao carregar mapa" << std::endl;
    }

    if (!map.loadFromMapData("../assets/map/spritesheet.png", mapData)) {
        std::cout << "Erro ao carregar Tilemap" << std::endl;
    }

    std::vector<Entity*> lTiles = map.getTiles();
    for(Entity* e :  lTiles) {
        lEntidades.push_back(e);
    }

    sf::Image playerImage;
    playerImage.create(16, 16, sf::Color::Blue);
    sf::Texture playerTextura;
    playerTextura.loadFromImage(playerImage);
    
    // Arrumar essas gambiarras depois =============================================================
    player = new Player(playerTextura, 0, 0, 10, 2, 10);
    
    lEntidades.push_back(player);
    
    for(Entity* entidade : lEntidades){
        gColisao.addEntity(entidade);
    }
}

Game::~Game()
{
}

void Game::executar()
{

    while(janela->isOpen())
    {
        sf::Event evento;
        while(janela->pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)
                janela->close();
        }
        deltaTime = clock.restart().asSeconds();

        gColisao.tratarColisoes();
        for(Entity* e : lEntidades)
        {
            e->executar(deltaTime);
            e->renderizar();
            // janela->addDrawable(e->getHitBox(), 3);
        }
        janela->setCentroCamera(player->getPosicao().x, player->getPosicao().y);
        // janela->addDrawable(map);
        janela->render();
    }
}
