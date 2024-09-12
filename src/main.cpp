#include "engine/Renderer/Renderer.h"
#include "game/Entity/Entity.h"
int main()
{
    Gerenciador::Renderer* janela = Gerenciador::Renderer::getInstance(800, 600, "Prodislexos Game");

    sf::Image playerImage;
    playerImage.create(50, 50, sf::Color::Blue);
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
        player.renderizar();
        player.executar(deltaTime);
        janela->render();
    }
}