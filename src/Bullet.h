//
// Created by Azimkin on 03.12.2023.
//

#ifndef SFMLGAME_BULLET_H
#define SFMLGAME_BULLET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Bullet : public sf::RectangleShape
{
private:
    float angle;
    float speed;

public:
    sf::Vector2f velocity;
    Bullet(float x, float y, float rotation);
};
#endif //SFMLGAME_BULLET_H
