//
// Created by hayav on 04.12.2023.
//

#include "MainMenu.h"

float getXPosition(const Text& text_, const RenderWindow& window)
{
    return window.getSize().x /2 - text_.getLocalBounds().width/2;
}

MainMenu::MainMenu(Font& font, RenderWindow& window): font(font),
title("SHOOTING GAME", font, 64),
play("PLAY", font, 60),
exit("EXIT", font, 60),
high_score("Highest score: ", font, 50),
blue(Color(0, 9, 179, 255)),
dark_blue(Color(0, 4, 82, 255)),
nRendered(true) {}

void MainMenu::update(Player& player, RenderWindow& window) {
    Vector2f mousePos = static_cast<Vector2f>(Mouse::getPosition(window));
    if(play.getGlobalBounds().contains(mousePos))
    {
        play.setFillColor(dark_blue);
        if (player.isLeftPressed)
        {
            player.setScene(1);
            player.isPause = false;
            player.isLeftPressed = false;
        }
    }
    else
        play.setFillColor(blue);
    if(exit.getGlobalBounds().contains(mousePos))
    {
        exit.setFillColor(dark_blue);
        if (player.isLeftPressed)
            window.close();
    }
    else
        exit.setFillColor(blue);
}

void MainMenu::render(RenderWindow &window) {
    if(nRendered)
    {
        nRendered = false;
        title.setFillColor(Color(255, 170, 0, 255));
        title.setPosition(getXPosition(title, window), 2);

        play.setFillColor(blue);
        play.setPosition(getXPosition(play, window), 200);

        exit.setFillColor(blue);
        exit.setPosition(getXPosition(exit, window), 300);

    }
    window.clear(Color::Yellow);
    window.draw(title);
    window.draw(play);
    window.draw(exit);
    //window.draw(high_score);
}
