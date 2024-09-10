#include "Entity.h"

Entity::Entity(int xx, int yy): 
    Ente(),
    offSetColisao(0.f, 0.f),
    caixaColisao(sf::Vector2f(0.f, 0.f))
{
    x = xx;
    y = yy;
    sprite.setPosition(x, y);
}
Entity::Entity(int xx, int yy, sf::Texture& textura):
    Ente(textura),
    caixaColisao(sf::Vector2f(0.f, 0.f))
{
    x = xx;
    y = yy;
    sprite.setPosition(x, y);
}

sf::RectangleShape Entity::getCaixaColisao() const
{
    return caixaColisao;
}

void Entity::renderizarCaixaColisao()
{
    gGrafico->addDrawable(caixaColisao, 3);
}

void Entity::inicializarCaixaColisao()
{
    sf::FloatRect caixa = sprite.getGlobalBounds();
    sf::Vector2f tamanho(caixa.width - offSetColisao.x, caixa.height - offSetColisao.y);
    caixaColisao.setSize(tamanho);
    caixaColisao.setOrigin(sprite.getOrigin());
    
    caixaColisao.setOutlineColor(sf::Color::Red);
    caixaColisao.setOutlineThickness(2);
    caixaColisao.setFillColor(sf::Color::Transparent);
    atualizarCaixaColisao();
}
void Entity::inicializarCaixaColisao(int largura, int altura)
{
    sf::Vector2f tamanho(largura - 4, altura - 4); // retirando bordas!
    caixaColisao.setSize(tamanho);
    caixaColisao.setOrigin(sprite.getOrigin());
    caixaColisao.setOutlineColor(sf::Color::Red);
    caixaColisao.setOutlineThickness(2);
    caixaColisao.setFillColor(sf::Color::Transparent);
    atualizarCaixaColisao();
}

void Entity::atualizarCaixaColisao()
{
    // Considera a origem do sprite e a posição ao ajustar a hitbox
    sf::Vector2f pos = sprite.getPosition();
    caixaColisao.setPosition(pos.x + offSetColisao.x/2, pos.y + offSetColisao.y);
}

void Entity::setVelocidade(const sf::Vector2f& novaVelocidade)
{
    this->velocidade = novaVelocidade;
}

sf::Vector2f Entity::getVelocidade() const 
{
    return this->velocidade;
}


void Entity::setNoChao(bool noChao)
{
    estaNoChao = noChao;
}

bool Entity::getNoChao() const
{
    return estaNoChao;
}

void Entity::setPosicao(int xx, int yy)
{
    x = xx;
    y = yy;
    sprite.setPosition(x, y);
}
void Entity::setPosicao(sf::Vector2f posicao)
{   
    x = posicao.x;
    y = posicao.y;
    sprite.setPosition(posicao);
}

void Entity::verificarLimitesTela() {
    int larguraTela = gGrafico->getTamanho().x;
    int alturaTela = gGrafico->getTamanho().y;

    sf::FloatRect hitBox = caixaColisao.getGlobalBounds();
    
    // Verifica se a entidade está saindo pela esquerda da tela
    int xx = x;
    int yy = y;

    if (sprite.getPosition().x < 0) {
        xx = 0; // Define a coordenada x para 0 para manter a entidade dentro da tela
    }
    // Verifica se a entidade está saindo pela direita da tela
    if (sprite.getPosition().x > larguraTela) {
        xx = larguraTela; // Reposiciona a entidade dentro da tela
    }
    // Verifica se a entidade está saindo pelo topo da tela
    if (sprite.getPosition().y < 0) {
        yy = 0; // Define a coordenada y para 0 para manter a entidade dentro da tela
    }
    // Verifica se a entidade está saindo pelo fundo da tela
    if(hitBox.top + hitBox.height > alturaTela)
    {
        yy = alturaTela - (hitBox.height);
    }
    // if (sprite.getPosition().y + caixaColisao.getSize().y/2 > alturaTela) {
    //     yy = alturaTela - caixaColisao.getSize().y/2; // Reposiciona a entidade dentro da tela
    // }
    setPosicao(xx, yy);
}