//
// Created by Azimkin on 03.12.2023.
//

#include "Game.h"
#define PI 3.1415926535

Game::Game() :
        window(VideoMode(800, 600), "Game", Style::Close | Style::Titlebar),
        player(),
        fpsCounter(),
        enemies(),
        font(),
        pauseText(),
        mobSpawnCooldown(),
        mobCD(5.0f),
        points(),
        mainMenu(font, window)
{
    window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile("assets/font/Aguante-Regular.otf")) {
        Logger::logE("Can't load font!");
    }
    pauseText.setFont(font);
    pauseText.setFillColor(Color::Cyan);
    pauseText.setCharacterSize(40);
    pauseText.setPosition(window.getPosition().x/2, window.getPosition().y/2);
    pauseText.setString("Pause");

    points.setFont(font);
    points.setFillColor(Color::Red);
    points.setCharacterSize(30);
}

void Game::run()
{
    Clock clock;
    Logger::log("Window opened");
    while (window.isOpen())
    {
        Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case Event::Closed:
                Logger::log("Window closed");
                window.close();
                break;
            case Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;
            case Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;
        }
    }
}

void Game::update(Time deltaTime)
{
    switch (player.getScene())
    {
        case 0:
            mainMenu.update(player, window);
            break;
        case 1:
            if (!player.isPause) {
                if (player.isDead())
                {
                    player.setScene(2);
                    break;
                }
                int speed = 500;
                Vector2f movement(0.f, 0.f);
                if (player.isMovingUp) {
                    if (player.model.getPosition().y > 0 + player.model.getRadius()) {
                        movement.y -= speed;
                    }
                }
                if (player.isMovingDown) {
                    if (player.model.getPosition().y < window.getSize().y - player.model.getRadius()) {
                        movement.y += speed;
                    }
                }
                if (player.isMovingLeft) {
                    if (player.model.getPosition().x > 0 + player.model.getRadius()) {
                        movement.x -= speed;
                    }
                }
                if (player.isMovingRight) {
                    if (player.model.getPosition().x < window.getSize().x - player.model.getRadius()) {
                        movement.x += speed;
                    }
                }
                player.model.move(movement * deltaTime.asSeconds());


                Vector2f pos = window.mapPixelToCoords(Mouse::getPosition(window));
                float rotation = (atan2(pos.y - player.model.getPosition().y,
                                        pos.x - player.model.getPosition().x)) * 180 / PI + 90;
                player.model.setRotation(rotation);


                if (mobSpawnCooldown.getElapsedTime().asSeconds() >= mobCD)
                {
                    short x = rand() % 800, y = rand() % 600;
                    enemies.push_back(Enemy(x, y));
                    Logger::logD("Enemy spawned");
                    mobSpawnCooldown.restart();
                }


                if (player.isLeftPressed) {
                    player.isLeftPressed = false;
                    player.bullets.emplace_back(player.model.getPosition().x, player.model.getPosition().y, rotation);
                }

                for (int i = 0; i < player.bullets.size(); i++) {
                    player.bullets[i].move(player.bullets[i].velocity * deltaTime.asSeconds());
                    if (player.bullets[i].getPosition().x < 0
                        || player.bullets[i].getPosition().y < 0
                        || player.bullets[i].getPosition().x > window.getSize().x
                        || player.bullets[i].getPosition().y > window.getSize().y)
                        player.bullets.erase(player.bullets.begin() + i);
                }

                for (int i = 0; i < enemies.size(); i++) {
                    enemies[i].moveToPlayer(player.model.getPosition(), deltaTime);
                    if (player.model.getGlobalBounds().contains(enemies[i].getPosition()))
                        enemies[i].damagePlayer(player);
                    for (int j = 0; j < player.bullets.size(); j++) {
                        if (enemies[i].getGlobalBounds().contains(player.bullets[j].getPosition())) {
                            enemies[i].damage(50);
                            player.bullets.erase(player.bullets.begin() + j);
                            if (enemies[i].getHealth() <= 0) {
                                enemies.erase(enemies.begin() + i);
                                Logger::logD("Enemy destroyed!");
                                player.addPoint();
                                if (mobCD > 0.6f) {
                                    mobCD -= 0.1f;
                                }
                            }
                        }
                    }
                }

                points.setString("P: " + to_string(player.getPoints()) + "  Health: " + to_string(player.getHealth()));
            }
            if (player.isEscapePressed && !player.isPause)
            {
                player.isEscapePressed = false;
                player.isPause = true;
            }
            else if (player.isPause && player.isEscapePressed)
            {
                player.isPause = false;
                player.isEscapePressed = false;
            }
            break;
        default:
            player.setScene(0);
    }
}

void Game::render()
{
    switch (player.getScene())
    {
        case 0:
            mainMenu.render(window);
            break;
        case 1:
            window.clear(Color::Cyan);
            window.draw(player.model);
            window.draw(points);
            for (int i = 0; i < player.bullets.size(); i++)
            {
                window.draw(player.bullets[i]);
            }
            for (int i = 0; i < enemies.size(); i++)
            {
                window.draw(enemies[i]);
            }
            if (player.isPause) {
                window.draw(pauseText);
            }
    }

    window.display();
    fpsCounter.update();
    window.setTitle("Game (" + to_string(fpsCounter.get()) + "fps)");
}

void Game::handlePlayerInput(Keyboard::Key key, bool isPressed)
{
    if (key == Keyboard::W)
        player.isMovingUp = isPressed;
    else if (key == Keyboard::A)
        player.isMovingLeft = isPressed;
    else if (key == Keyboard::S)
        player.isMovingDown = isPressed;
    else if (key == Keyboard::D)
        player.isMovingRight = isPressed;
    else if (key == Keyboard::Escape)
        player.isEscapePressed = isPressed;
}

void Game::handleMouseInput(Mouse::Button button, bool isPressed)
{
    if (button == Mouse::Left)
        player.isLeftPressed = isPressed;
}




