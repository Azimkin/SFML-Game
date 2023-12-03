//
// Created by Azimkin on 03.12.2023.
//

#include "FrameCounter.h"

FrameCounter::FrameCounter(): clock(), count(0), fps(0), elapsedTime()
{
}

void FrameCounter::update()
{
    count++;
    elapsedTime += clock.restart();

    if (elapsedTime >= seconds(1.0f))
    {
        fps = std::ceil(count / elapsedTime.asSeconds());
        count = 0;
        elapsedTime = Time::Zero;
    }
}

short FrameCounter::get()
{
    return fps;
}

