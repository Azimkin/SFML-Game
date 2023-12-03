//
// Created by Azimkin on 03.12.2023.
//

#ifndef SFMLGAME_GAME_H
#define SFMLGAME_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "FrameCounter.h"

using namespace std;
using namespace sf;

class Game
{
private:
    RenderWindow window;
    Player player;
    bool isEscapePressed, isPause;
    size_t scene;
    RectangleShape playButton;
    FrameCounter fpsCounter;


    void processEvents();

    void update(Time deltaTime);

    void render();

    void handlePlayerInput(Keyboard::Key key, bool isPressed);

    void handleMouseInput(Mouse::Button button, bool isPressed);

public:
    Game();

    void run();
};

#endif //SFMLGAME_GAME_H
