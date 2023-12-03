//
// Created by Azimkin on 03.12.2023.
//

#include "Player.h"
#define PLAYER_RADIUS 32

Player::Player() :
        model(),
        isMovingDown(false),
        isMovingLeft(false),
        isMovingRight(false),
        isMovingUp(false),
        isSpace(false),
        isLeftPressed(false),
        texture(),
        points(0),
        health(100),
        isAlive(true)
{
    model.setRadius(PLAYER_RADIUS);
    model.setPosition(100.f, 100.f);
    model.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
    if (!texture.loadFromFile("assets/textures/player.png"))
    {
        std::cout << "[ERROR] Can't load player texture!" << std::endl;
        model.setFillColor(Color::Cyan);
    }
    else
        model.setTexture(&texture);

}

void Player::addPoint() {
    points++;
}

short Player::getPoints() {
    return points;
}

void Player::damage(short damage) {
    health = health - damage;

    if (health <= 0)
        isAlive = false;
    std::cout << "Player taked damage!" << std::endl;
}

bool Player::isDead() {
    return !isAlive;
}

int Player::getHealth() {
    return health;
}
