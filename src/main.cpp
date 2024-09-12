#include "engine/Renderer/Renderer.h"
#include "game/Entity/Entity.h"
#include "engine/TileMap/TileMap.h"
#include  "engine/TileMap/MapLoader.h"

// 38 x 14 tiles
int main()
{

    Gerenciador::Renderer* janela = Gerenciador::Renderer::getInstance(800, 600, "Prodislexos Game");
    janela->setTamanhoCamera(400, 300);

    // Define os tiles do mapa (0, 1, 2, ...)
    std::vector<int> level = {
    1,0,
    0,1
    };

    MapData mapData;
    if (!loadMapFromFile("../assets/map/map.json", mapData)) {
        return -1;
    }

    TileMap map;
    if (!map.loadFromMapData("../assets/map/spritesheet.png", mapData)) {
        return -1;
    }

    sf::Image playerImage;
    playerImage.create(16, 16, sf::Color::Blue);
    sf::Texture playerTextura;
    playerTextura.loadFromImage(playerImage);
    Entity player(playerTextura, 400, 300);
    sf::Clock clock;    
    float deltaTime;
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
        player.renderizar(1);
        janela->setCentroCamera(player.getPosicao().x, player.getPosicao().y);
        janela->addDrawable(map);
        janela->render();
    }
}