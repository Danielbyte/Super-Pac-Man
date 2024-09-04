#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include <raylib-cpp.hpp>
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
    raylib::Color black;
    raylib::Color background;
    bool isSplashScreen; //flag to monitor if player is withing splash screen
    bool isPlaying;

    void displaySplashScreen();
    void displayInGameScreen();
};
#endif //DISPLAYMANAGER