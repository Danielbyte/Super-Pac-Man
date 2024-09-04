#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "raylib-cpp.hpp"
//using namespace raylib;
#include <iostream>

class DisplayManager
{
    public:
    DisplayManager();
    void startGame();
    void handleUserInput();
    
    private:
    const int screen_width = 1600;
    const int screen_height = 900;
    bool quitGame;//use to control game window
    raylib::Color green;
};
#endif //DISPLAYMANAGER