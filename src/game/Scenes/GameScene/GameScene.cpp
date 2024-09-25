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
    gRecursos->loadTexture("tilesheet", "../assets/newmap/sheets.png");
    
    map.loadMapFromFile("../assets/newmap/mapa.tmj");
    map.loadSheet(gRecursos->getTexture("tilesheet"));
    
    // janela->setTamanhoCamera(640, 320);
    std::vector<Entity*> lTiles = map.getEntitys();
    for(Entity* e :  lTiles) {
        lEntidades.push_back(e);
    }

    sf::Image playerImage;
    playerImage.create(16, 16, sf::Color::Blue);
    sf::Texture playerTextura;
    playerTextura.loadFromImage(playerImage);
    
    // Arrumar essas gambiarras depois =============================================================
    player = new Player(gRecursos->getTexture("jogador"), 0, 0, 10, 2, 10);
    player->setPosicao(0, 0);
    lEntidades.push_back(player);
    
    for(Entity* entidade : lEntidades){
        gColisao.addEntity(entidade);
    }

    musica.setBuffer(gRecursos->getSom("game"));
    // musica.play();
    musica.setLoop(true);

    // janela->carregarShaders();
}

void GameScene::executar()
{
    deltaTime = tempo.restart().asSeconds();

    if (deltaTime > 0.1f) {
        deltaTime = 0.1f;
    }
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
        janela->addDrawable(e->getHitBox(), 3);
    }

    janela->setCentroCamera(player->getPosicao().x, player->getPosicao().y);
    // janela->addDrawable(map);
    janela->render();
}

void GameScene::processarEventos(const sf::Event &evento)
{
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        // Voltar para o menu ou outra cena quando a tecla Escape for pressionada
        SceneManager::getInstance()->mudarCena(std::make_unique<MenuScene>());
    }
}

void GameScene::finalizar(){}