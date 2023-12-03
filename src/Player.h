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

public:
    std::vector<Bullet> bullets;
    bool
            isMovingUp,
            isMovingLeft,
            isMovingDown,
            isMovingRight,
            isSpace,
            isLeftPressed;
    CircleShape model;

    Player();
};
#endif //SFMLGAME_PLAYER_H
