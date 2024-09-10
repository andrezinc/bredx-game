#include "engine/Renderer/Renderer.h"

int main()
{
    Gerenciador::Renderer* janela = Gerenciador::Renderer::getRenderer(800, 600, "Prodislexos Game");
    
    while(janela->isOpen())
    {
        sf::Event evento;
        while(janela->pollEvent(evento))
        {
            if(evento.type == sf::Event::Closed)
                janela->close();    
        }
    }
}