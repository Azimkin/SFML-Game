//
// Created by Azimkin on 03.12.2023.
//

#ifndef SFMLGAME_ENEMY_H
#define SFMLGAME_ENEMY_H

#include "SFML/Graphics.hpp"
#include "vector"

class Enemy : public sf::CircleShape
        {
private:
    int health;
    sf::Clock cooldown;
    bool isDead;
public:
    Enemy(short x, short y);

    void attack();

    int getHealth();

    void damage(short damage);
};


#endif //SFMLGAME_ENEMY_H
