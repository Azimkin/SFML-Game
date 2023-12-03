//
// Created by Azimkin on 03.12.2023.
//

#include "Enemy.h"

void Enemy::attack() {

}

void Enemy::damage(short damage) {
    health -= damage;
    if (health <= 0)
        isDead = true;
}

Enemy::Enemy(short x, short y): health(100), cooldown(), isDead(false) {
    setFillColor(sf::Color::Red);
    setRadius(32);
    setOrigin(32, 32);
    setPosition(x, y);
}

int Enemy::getHealth() {
    return health;
}
