//
// Created by Azimkin on 03.12.2023.
//

#include "Bullet.h"

Bullet::Bullet(float x, float y, float rotation) : angle(rotation),
                                                   velocity(), speed(1000)
{
    setSize(sf::Vector2f(10, 20));
    setFillColor(sf::Color::Green);
    setOrigin(5, 10);
    setRotation(rotation);
    setPosition(x, y);
    float radAngle = (rotation - 90) * 3.14159265 / 180;

    velocity.x = cos(radAngle) * speed;
    velocity.y = sin(radAngle) * speed;
}

