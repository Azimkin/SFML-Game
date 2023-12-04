//
// Created by hayav on 04.12.2023.
//

#ifndef SFMLGAME_LOGGER_H
#define SFMLGAME_LOGGER_H

#include <iostream>
#include <string>

using namespace std;

class Logger {
private:
    static bool debug;

public:
    static void log(const char* text);

    static void logD(const char* text);

    static void logE(const char * text);
};


#endif //SFMLGAME_LOGGER_H
