//
// Created by hayav on 04.12.2023.
//

#include "Logger.h"

bool Logger::debug = false;

void Logger::logD(const char *text) {
    if(debug)
        cout << "[DEBUG] " << text << "\033[0m" << endl;
}

void Logger::log(const char *text) {
    cout << "[INFO] " << text << endl;
}

void Logger::logE(const char *text) {
    cout << "\033[91m[ERROR] " << text << "\033[0m" << endl;
}
