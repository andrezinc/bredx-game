#ifndef _GERENCIADOR_DE_CENAS_H
#define _GERENCIADOR_DE_CENAS_H

#include <stack>
#include <memory>
#include "Scene.h"

/**
 * @brief Classe SceneManager é responsável por gerenciar as cenas do jogo.
 * Utiliza o padrão Singleton para garantir que apenas uma instância do gerenciador de cenas exista.
 * As cenas são armazenadas em uma pilha, permitindo empilhar, desempilhar e trocar de cenas.
 */
class SceneManager{
private:
    static SceneManager *singleton; ///< Ponteiro para a instância singleton
    SceneManager(){};               ///< Construtora privada para implementação do singleton
    std::stack<std::unique_ptr<Scene>> cenas; ///< Pilha para armazenar as cenas
public:
    void operator=(const SceneManager&) = delete; ///< Evitando atribuições do objeto
    SceneManager(const SceneManager&) = delete;   ///< Evitando cópias do objeto
    ~SceneManager();
    /**
     * @brief Retorna a instância do gerenciador de cenas
     * @throw Na primeira chamada aloca o gerenciador
     * @return Ponteiro para o singleton da classe
     */
    static SceneManager* getInstance();
    /**
     * @brief Adiciona cena a fila finalizando cena atual
     */
    void mudarCena(std::unique_ptr<Scene> novaCena);
    /**
     * @brief Adiciona cena a fila pausando cena atual
     */
    void empilharCena(std::unique_ptr<Scene> novaCena);
    /**
     * @brief Finaliza cena atual e retoma próxima cena na pilha
     */
    void desempilharCena();
    /**
     * @brief Chama método da atualizar da cena
     */
    void atualizarCenaAtual();
    /**
     * @brief Chama método da renderizar da cena
     */
    void renderizarCenaAtual();
    /**
     * @brief Chama método da processar eventos da cena
     */
    void processarEventosCenaAtual(const sf::Event& evento);
};
#endif