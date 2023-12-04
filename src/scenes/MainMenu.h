//
// Created by Azimkin on 04.12.2023.
//

#ifndef SFMLGAME_MAINMENU_H
#define SFMLGAME_MAINMENU_H

#include "iostream"
#include "SFML/Graphics.hpp"
#include "../Player.h"

using namespace sf;

class MainMenu {
private:
    Font font;
    Text title, play, exit, high_score;
    Color blue, dark_blue;
    bool nRendered; // shit

public:
    MainMenu(Font& font, RenderWindow& window);

    void render(RenderWindow& window);

    void update(Player& player, RenderWindow& window);
};


#endif //SFMLGAME_MAINMENU_H
