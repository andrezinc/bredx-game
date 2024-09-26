#ifndef _PARALLAX_H
#define _PARALLAX_H

#include "../Ente/Ente.h"
#include <vector>

class Parallax : public Ente{
private:
    std::vector<sf::Sprite*> layers;
    std::vector<float> speed;
public:
    Parallax();
    ~Parallax();
    void addLayer(sf::Texture& textura, float speed);
    void atualizar(sf::View& camera);
    void renderizar();
    void setPosition(sf::Vector2f origem);
};

#endif // _PARALLAX_H