#include "Game.h"
#include <iostream>

Game::Game():
janela(Gerenciador::Renderer::getInstance()),
gRecursos(Gerenciador::ResourceManager::getInstance())
{
    gRecursos->loadSons("menu", "../assets/musics/musicaMenu.mp3");
    gRecursos->loadTexture("jogador", "../assets/textures/protagonista.png");
    janela->setTamanhoCamera(640, 320);
    if (!TileEngine::loadMapFromFile("../assets/map/map.json", mapData)) {
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
    player = new Player(gRecursos->getTexture("jogador"), 0, 0, 10, 2, 10);
    // player->setHitBoxOffset(sf::Vector2f(5, 5));
    // player->setHitBoxSize(sf::Vector2f(16, 16));
    player->setSize(sf::Vector2f(32, 32));
    player->setPosicao(0, 0);
    lEntidades.push_back(player);
    
    for(Entity* entidade : lEntidades){
        gColisao.addEntity(entidade);
    }
}

Game::~Game()
{
    delete player;
}

void Game::executar()
{
    sf::Sound musica;
    musica.setBuffer(gRecursos->getSom("menu"));
    musica.play();
    musica.setLoop(true);
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
