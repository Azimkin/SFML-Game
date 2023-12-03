//
// Created by Azimkin on 03.12.2023.
//

#include "Game.h"
#define PI 3.1415926535

Game::Game() :
        window(VideoMode(800, 600), "Game", Style::Close | Style::Titlebar),
        player(),
        scene(0),
        isEscapePressed(false),
        isPause(true),
        playButton(),
        fpsCounter(),
        enemies(),
        font(),
        pauseText(),
        mobSpawnCooldown(),
        mobCD(5.0f),
        points(),
        playButtonText()
{
    window.setVerticalSyncEnabled(true);
    playButton.setFillColor(Color::White);
    playButton.setSize(Vector2f(200, 50));
    playButton.setOrigin(100, 25);
    playButton.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    if (!font.loadFromFile("assets/font/Aguante-Regular.otf")) {
        cout << "Can't load font!" << endl;
    }
    pauseText.setFont(font);
    pauseText.setFillColor(Color::Cyan);
    pauseText.setCharacterSize(40);
    pauseText.setPosition(window.getPosition().x/2, window.getPosition().y/2);
    pauseText.setString("Pause");

    points.setFont(font);
    points.setFillColor(Color::Red);
    points.setCharacterSize(30);

    playButtonText.setPosition(playButton.getPosition());
    playButtonText.setFont(font);
    playButtonText.setFillColor(Color::Black);
    playButtonText.setString("Play");
    playButtonText.setCharacterSize(20);
}

void Game::run()
{
    Clock clock;
    cout << "Window opened\n";
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
                cout << "Window closed\n";
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
    switch (scene)
    {
        case 0:
            if (player.isLeftPressed)
            {
                player.isLeftPressed = false;
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                {
                    // Ваш код для обработки клика на объекте
                    std::cout << "Play button clicked!" << std::endl;
                    scene = 1;
                    isPause = false;
                }
            }
            break;
        case 1:
            if (!isPause) {
                if (player.isDead())
                {
                    scene = 2;
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
                    cout << "Enemy spawned!" << endl;
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
                                cout << "Enemy " << " destroyed!" << endl;
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
            if (isEscapePressed && !isPause)
            {
                isEscapePressed = false;
                isPause = true;
            }
            else if (isPause && isEscapePressed)
            {
                isPause = false;
                isEscapePressed = false;
            }
            break;
        default:
            scene = 0;
    }
}

void Game::render()
{

    switch (scene)
    {
        case 0:
            window.clear(Color::Blue);
            window.draw(playButton);
            window.draw(playButtonText);
            break;
        case 1:
            window.clear();
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
            if (isPause) {
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
        isEscapePressed = isPressed;
}

void Game::handleMouseInput(Mouse::Button button, bool isPressed)
{
    if (button == Mouse::Left)
        player.isLeftPressed = isPressed;
}




