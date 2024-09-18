#include "Game.h"
#include <iostream>

Game::Game():
    janela(Gerenciador::Renderer::getInstance()),
    gCenas(SceneManager::getInstance())
{
    // cenaJogo = new GameScene;
    // cenaJogo->inicializar();

}

Game::~Game()
{
    
}

void Game::executar()
{
    gCenas->empilharCena(std::make_unique<GameScene>());
    while(janela->isOpen())
    {
        sf::Event evento;
        if(evento.type == sf::Event::Closed)
            janela->close();
        else
            gCenas->processarEventosCenaAtual(evento);
        gCenas->atualizarCenaAtual();
        gCenas->renderizarCenaAtual();
    }
}

