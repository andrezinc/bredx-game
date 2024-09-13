#include "Game.h"
#include <iostream>
Game::Game()
{
    janela->setTamanhoCamera(640, 320);
    if (!loadMapFromFile("../assets/map/map.json", mapData)) {
        std::cout << "Erro ao carregar mapa" << std::endl;
    }

    if (!map.loadFromMapData("../assets/map/spritesheet.png", mapData)) {
        std::cout << "Erro ao carregar Tilemap" << std::endl;
    }

    sf::Image playerImage;
    playerImage.create(2, 2, sf::Color::Blue);
    sf::Texture* playerTextura = new  sf::Texture();
    playerTextura->loadFromImage(playerImage);
    
    // Arrumar essas gambiarras depois =============================================================
    player.setTexture(*playerTextura);
    player.setSize(sf::Vector2f(16, 16));
    player.setHitBoxSize(sf::Vector2f(16, 16));
    player.setPosicao(0, 0);

    lEntidades.push_back(&player);
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
        player.executar(deltaTime);

        for(Entity* e : lEntidades)
        {
            e->executar(deltaTime);
            e->renderizar();
            janela->addDrawable(e->getHitBox(), 3);
        }
        janela->setCentroCamera(player.getPosicao().x, player.getPosicao().y);
        janela->addDrawable(map);
        janela->render();
    }
}
