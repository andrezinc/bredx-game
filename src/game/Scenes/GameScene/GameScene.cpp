#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
    delete player;
}

void GameScene::inicializar()
{
    gRecursos->loadSons("game", "../assets/musics/musicaMenu.mp3");
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

    musica.setBuffer(gRecursos->getSom("game"));
    musica.play();
    musica.setLoop(true);
}

void GameScene::executar()
{
    deltaTime = tempo.restart().asSeconds();

    gColisao.tratarColisoes();
    for(Entity* e : lEntidades)
    {
        e->executar(deltaTime);
    }
}

void GameScene::renderizar()
{
    for(Entity* e : lEntidades)
    {
        e->renderizar();
        // janela->addDrawable(e->getHitBox(), 3);
    }

    janela->setCentroCamera(player->getPosicao().x, player->getPosicao().y);
    // janela->addDrawable(map);
    janela->render();
}

void GameScene::processarEventos(const sf::Event &evento)
{
    
}

void GameScene::finalizar(){}