#include "SceneManager.h"

SceneManager* SceneManager::singleton = nullptr;
SceneManager* SceneManager::getInstance()
{
    if(singleton == nullptr)
        singleton = new SceneManager;
    return singleton;
}
SceneManager::~SceneManager()
{
    delete singleton;
}
void SceneManager::mudarCena(std::unique_ptr<Scene> novaCena)
{
    if(!cenas.empty()){
        cenas.top()->finalizar();
        cenas.pop();
    }
    cenas.push(std::move(novaCena));
    cenas.top()->inicializar();
}
void SceneManager::empilharCena(std::unique_ptr<Scene> novaCena)
{
    if(!cenas.empty()){
        cenas.top()->pausar();
    }
    cenas.push(std::move(novaCena));
    cenas.top()->inicializar();
}
void SceneManager::desempilharCena()
{
    if(!cenas.empty()){
        cenas.top()->finalizar();
        cenas.pop();
    }
    if(!cenas.empty()){
        cenas.top()->retomar();
    }
}

void SceneManager::atualizarCenaAtual()
{
    if(!cenas.empty()){
        cenas.top()->executar();
    }
}

void SceneManager::renderizarCenaAtual()
{
    if(!cenas.empty()){
        cenas.top()->renderizar();
    }
}
void SceneManager::processarEventosCenaAtual(const sf::Event& evento)
{
    if(!cenas.empty()){
        cenas.top()->processarEventos(evento);
    }
}