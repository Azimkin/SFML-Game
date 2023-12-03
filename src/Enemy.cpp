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

Enemy::Enemy(short x, short y): health(100), cooldown(), isDead(false), speed(50) {
    setFillColor(sf::Color::Red);
    setRadius(16);
    setOrigin(16, 16);
    setPosition(x, y);
}

int Enemy::getHealth() {
    return health;
}

void Enemy::moveToPlayer(sf::Vector2f playerPosition, sf::Time deltaTime) {
    sf::Vector2f direction = sf::Vector2f(playerPosition) - getPosition();

    // Нормализуем вектор направления (приводим к единичной длине)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;

        // Передвигаем врага в направлении игрока с учетом скорости
        move(direction * deltaTime.asSeconds() * speed);
    }

}

void Enemy::damagePlayer(Player& player) {
    if (damageCooldown.getElapsedTime().asSeconds() >=3.0f)
    {
        player.damage(10);
        std::cout << "Player damaged!" << std::endl;
        damageCooldown.restart();
    }
}
