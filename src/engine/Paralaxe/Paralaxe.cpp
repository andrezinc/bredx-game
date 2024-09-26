#include "Paralaxe.h"

Parallax::Parallax(){}
Parallax::~Parallax(){}

void Parallax::addLayer(sf::Texture& textura, float velocidade)
{
    sf::Sprite* novaCamada = new sf::Sprite;
    novaCamada->setTexture(textura);
    novaCamada->setOrigin(0, novaCamada->getGlobalBounds().height);
    layers.push_back(novaCamada);
    speed.push_back(velocidade);
}

void Parallax::setPosition(sf::Vector2f origem)
{
    for(sf::Sprite* s : layers){
        s->setPosition(origem);
    }
}
void Parallax::atualizar(sf::View& camera)
{
    for (int i = 0; i < layers.size(); i++){
        sf::Vector2f coordCam = camera.getCenter();
        layers[i]->setPosition(coordCam.x * speed[i], layers[i]->getPosition().y);
    }
}

void Parallax::renderizar()
{
    for (int i = 0; i < layers.size(); i++){
        gGrafico->addDrawable(*layers.at(i), i);
    }
}