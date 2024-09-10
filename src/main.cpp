#include "engine/Renderer/Renderer.h"
#include "game/Entity/Entity.h"
int main()
{
    Gerenciador::Renderer* janela = Gerenciador::Renderer::getInstance(800, 600, "Prodislexos Game");

    sf::Image playerImage;
    playerImage.create(50, 50, sf::Color::Blue);
    sf::Texture playerTextura;
    playerTextura.loadFromImage(playerImage);
    Entity player(400, 300, playerTextura);

    while(janela->isOpen())
    {
        sf::Event evento;
        while(janela->pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)
                janela->close();
        }
        player.renderizar();
        janela->render();
    }
}