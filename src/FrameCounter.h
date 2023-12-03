//
// Created by Azimkin on 03.12.2023.
//

#ifndef SFMLGAME_FRAMECOUNTER_H
#define SFMLGAME_FRAMECOUNTER_H

#include <SFML/System.hpp>
#include <cmath>

using namespace sf;

class FrameCounter
{
private:
    Clock clock;
    short count, fps;
    Time elapsedTime;
public:
    FrameCounter();
    void update();

    short get();
};
#endif //SFMLGAME_FRAMECOUNTER_H
