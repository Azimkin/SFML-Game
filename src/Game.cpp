//
// Created by Azimkin on 03.12.2023.
//

#include "Game.h"
#define PI 3,1415926535

Game::Game() :
        window(VideoMode(800, 800), "Game"),
        player(),
        scene(0),
        isEscapePressed(false),
        isPause(true),
        playButton(),
        fpsCounter()
{
    window.setVerticalSyncEnabled(true);
    playButton.setFillColor(Color::White);
    playButton.setSize(Vector2f(200, 100));
    playButton.setOrigin(100, 50);
    playButton.setPosition(window.getSize().x / 2, window.getSize().y / 2);
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
                }
            }
            break;
        case 1:
            int speed = 500;
            Vector2f movement(0.f, 0.f);
            if (player.isMovingUp)
            {
                if (player.model.getPosition().y > 0 + player.model.getRadius())
                {
                    movement.y -= speed;
                }
            }
            if (player.isMovingDown)
            {
                if (player.model.getPosition().y < window.getSize().y - player.model.getRadius())
                {
                    movement.y += speed;
                }
            }
            if (player.isMovingLeft)
            {
                if (player.model.getPosition().x > 0 + player.model.getRadius())
                {
                    movement.x -= speed;
                }
            }
            if (player.isMovingRight)
            {
                if (player.model.getPosition().x < window.getSize().x - player.model.getRadius())
                {
                    movement.x += speed;
                }
            }

            player.model.move(movement * deltaTime.asSeconds());

            Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
            Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

            float dX = pos.x - player.model.getPosition().x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
            float dY = pos.y - player.model.getPosition().y;//он же, координата y
            float rotation = (atan2(dY, dX)) * 180 / 3.14159265 + 90;//получаем угол в радианах и переводим его в градусы
            player.model.setRotation(rotation);//поворачиваем спрайт на эти градусы

            if (player.isLeftPressed)
            {
                player.isLeftPressed = false;
                player.bullets.push_back(Bullet(player.model.getPosition().x,
                                                player.model.getPosition().y, rotation));
                cout << "Bullet spawned!\n";
            }

            for (int i = 0; i < player.bullets.size(); i++)
            {
                player.bullets[i].move(player.bullets[i].velocity * deltaTime.asSeconds());
            }
            break;
    }


}

void Game::render()
{

    switch (scene)
    {
        case 0:
            window.clear(Color::Blue);
            window.draw(playButton);
            break;
        case 1:
            window.clear();
            window.draw(player.model);
            for (int i = 0; i < player.bullets.size(); i++)
            {
                window.draw(player.bullets[i]);
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
    isEscapePressed = isPressed;
}

void Game::handleMouseInput(Mouse::Button button, bool isPressed)
{
    if (button == Mouse::Left)
        player.isLeftPressed = isPressed;
}




