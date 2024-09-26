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
    gRecursos->loadTexture("cenario1", "../assets/textures/cenario1.png");    
    gRecursos->loadTexture("cenario2", "../assets/textures/cenario2.png");
    gRecursos->loadTexture("cenario3", "../assets/textures/cenario3.png");
    gRecursos->loadTexture("tilesheet", "../assets/newmap/sheets.png");
    
    map.loadMapFromFile("../assets/newmap/mapa.tmj");
    map.loadSheet(gRecursos->getTexture("tilesheet"));
    cenario.addLayer(gRecursos->getTexture("cenario3"), 0.5);
    cenario.addLayer(gRecursos->getTexture("cenario2"), 0.75);
    cenario.addLayer(gRecursos->getTexture("cenario1"), 1);

    cenario.setPosition(map.getOrigem());
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
        if(entidade->getColisao())
            gColisao.addEntity(entidade);
    }

    musica.setBuffer(gRecursos->getSom("game"));
    musica.play();
    musica.setLoop(true);

    janela->setMoveBounds(sf::FloatRect(200, 200, 100, 300)); // Exemplo de retângulo de 200x200
    // janela->carregarShaders();
}

void GameScene::executar()
{
    deltaTime = tempo.restart().asSeconds();

    // cenario.atualizar(janela->getView());

    if (deltaTime > 0.1f) {
        deltaTime = 0.1f;
    }
    gColisao.tratarColisoes();
    for(Entity* e : lEntidades)
    {
        e->executar(deltaTime);
    }
    janela->updateCamera(player->getPosicao());
}

void GameScene::renderizar()
{
    cenario.renderizar();

    for(Entity* e : lEntidades)
    {
        e->renderizar(5);
        // janela->addDrawable(e->getHitBox(), 3);
    }
    // std::cout << player->getPosicao().y << std::endl;
    // janela->setCentroCamera(player->getPosicao().x, player->getPosicao().y);

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