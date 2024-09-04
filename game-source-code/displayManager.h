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
    
    private:
    const int screen_width = 1600;
    const int screen_height = 900;
};
#endif //DISPLAYMANAGER