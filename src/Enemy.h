//
// Created by Azimkin on 03.12.2023.
//

#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include "SFML/Graphics.hpp"
#include "vector"
#include <cmath>

#include "Player.h"

class Enemy : public sf::CircleShape
        {
private:
    int health;
    sf::Clock cooldown;
    bool isDead;
    float speed;
    sf::Clock damageCooldown;

public:
    Enemy(short x, short y);

    void attack();

    int getHealth();

    void moveToPlayer(sf::Vector2f playerPosition, sf::Time deltaTime);

    void damage(short damage);

    void damagePlayer(Player& player);
};


#endif //SFMLGAME_ENEMY_H
