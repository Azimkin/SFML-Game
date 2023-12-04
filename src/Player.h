//
// Created by Azimkin on 03.12.2023.
//

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Bullet.h"

using namespace sf;

class Player
{
private:
    Texture texture;
    short points;
    int health;
    bool isAlive;
    size_t scene;

public:
    std::vector<Bullet> bullets;
    bool
            isMovingUp,
            isMovingLeft,
            isMovingDown,
            isMovingRight,
            isSpace,
            isLeftPressed,
            isPause,
            isEscapePressed;
    CircleShape model;

    void addPoint();

    short getPoints();

    void damage(short damage);

    bool isDead();

    int getHealth();

    size_t getScene();

    void setScene(size_t scene_);

    Player();
};

#endif //SFMLGAME_PLAYER_H
