#ifndef TILEENTITY_H
#define TILEENTITY_H

#include "../../game/Entity/Entity.h"
#include <iostream>

namespace TileEngine {

/**
 * @class TileEntity
 * @brief Representa uma entidade de tile no jogo, usado para compor o cenário.
 * 
 * A classe `TileEntity` herda da classe `Entity` e adiciona funcionalidades específicas
 * para tiles, como definir a posição do sprite e a caixa de colisão. Também implementa
 * métodos para lidar com colisões.
 */
class TileEntity : public Entity {
public:
    /**
     * @brief Construtor da classe TileEntity.
     * Inicializa uma nova instância de `TileEntity` com a textura fornecida, o tamanho do tile,
     * e as coordenadas do sprite e posição do tile.
     * @param textura Referência para a textura a ser utilizada pelo tile.
     * @param tileSize Tamanho do tile em pixels.
     * @param spriteX Coordenada X do sprite na textura.
     * @param spriteY Coordenada Y do sprite na textura.
     * @param x Coordenada X da posição do tile no mundo.
     * @param y Coordenada Y da posição do tile no mundo.
     */
    TileEntity(sf::Texture& textura, int tileSize, int spriteX, int spriteY, int x, int y)
    : Entity(textura, x * tileSize, y * tileSize)
    {
        sprite.setPosition(x * tileSize, y * tileSize); // Define a posição do sprite
        sprite.setTextureRect(sf::IntRect(spriteX * tileSize, spriteY * tileSize, tileSize, tileSize)); // Define a área da textura a ser usada
        setHitBoxSize(sf::Vector2f(tileSize, tileSize));
        atualizaHitBox();
    }

    /**
     * @brief Atualiza a posição da entidade.
     * Este método é chamado a cada frame para atualizar a posição da entidade com base
     * no tempo decorrido.
     * @param deltaTime Tempo decorrido desde o último frame.
     */
    void executar(float deltaTime) override {
        setPosicao(posicao); // Atualiza a posição com base na posição atual
    }

    /**
     * @brief Método chamado quando ocorre uma colisão com outra entidade.
     * Este método é chamado quando a entidade colide com outra entidade. Ele redireciona
     * a colisão para o método específico para colisão com tiles.
     * @param other Ponteiro para a outra entidade com a qual ocorreu a colisão.
     */
    void colidiu(Entity* other) override {
        other->colidiuComTile(this); // Redireciona a colisão para o método específico
    }

    /**
     * @brief Método específico para lidar com colisões com tiles.
     * Este método é chamado quando a entidade colide com um tile. No momento, ele não faz nada.
     * @param e Ponteiro para a entidade que é o tile com o qual ocorreu a colisão.
     */
    void colidiuComTile(Entity* e) override
    {
        // Implementação específica para colisão com tiles pode ser adicionada aqui
        // Precisa ser sobreescrita para não aplicar a lógica de colisão à esse tipo de entidade
    }
};

#endif // TILEENTITY_H
}