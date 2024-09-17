#pragma once

#include "../engine/Renderer/Renderer.h"
#include "../engine/CollisionManager/CollisionManager.h"
#include "./Entity/Entity.h" 
#include "./Entity/Character/Player/Player.h" 
#include "../engine/TileMap/TileMap.h"
#include "../engine/TileMap/MapLoader.h"
#include <vector> 

/**
 * @class Game
 * @brief Gerencia o fluxo principal do jogo.
 * 
 * A classe `Game` é responsável por coordenar a renderização, o gerenciamento de colisões,
 * e a manipulação de entidades e mapas. Ela controla a execução do jogo e gerencia o
 * estado e as interações entre diferentes componentes do jogo.
 */
class Game
{
private:
    Gerenciador::Renderer* janela;          ///< Ponteiro para o renderizador (Renderer)
    Gerenciador::CollisionManager gColisao; ///< Instância do gerenciador de colisões
    TileEngine::MapData mapData;            ///< Dados do mapa carregados
    TileEngine::TileMap map;                ///< Instância do mapa de tiles
    sf::Clock clock;                        ///< Relógio para medir o tempo decorrido
    float deltaTime;                        ///< Tempo decorrido desde o último frame

    Player* player;                         ///< Ponteiro para o jogador (Player)
    std::vector<Entity*> lEntidades;        ///< Lista de entidades no jogo
    
public:
    /**
     * @brief Construtor da classe Game.
     * 
     * Inicializa uma nova instância da classe `Game`, configurando os componentes
     * principais do jogo, incluindo o renderizador, o gerenciador de colisões, o mapa,
     * e o jogador.
     */
    Game();

    /**
     * @brief Destruidor da classe Game.
     * 
     * Limpa os recursos utilizados pela instância da classe `Game`, incluindo a
     * destruição de entidades e outros componentes.
     */
    ~Game();

    /**
     * @brief Executa o loop principal do jogo.
     * 
     * Este método gerencia o ciclo de vida do jogo, incluindo a atualização do estado
     * do jogo, a detecção e tratamento de colisões, e a renderização dos elementos
     * gráficos na tela.
     */
    void executar();
};
