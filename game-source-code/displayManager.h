#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER
#include "raylib-cpp.hpp"

using namespace raylib;
#include <iostream>
#include <memory>
#include "player.h"

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
    raylib::Color white;
    bool isSplashScreen; //flag to monitor if player is withing splash screen
    bool isPlaying;

    //Utility Functions
    void displaySplashScreen();
    void displayInGameScreen();
    void loadTextures();
    
    //Create Player objects
    std::shared_ptr<Player> player_obj = std::make_shared<Player>(); 
    raylib::Texture2D playerT;
    raylib::Image playerI;
    //Texture objects
    std::shared_ptr<raylib::Window>window = std::make_shared<raylib::Window>();
};
#endif //DISPLAYMANAGER