#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER
#include "raylib-cpp.hpp"
#include "gameWorld.h"

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
    const int window_width;
    const int window_height;
    bool quitGame;//use to control game window
    raylib::Color green;
    raylib::Color black;
    raylib::Color background;
    raylib::Color white;
    bool isSplashScreen; //flag to monitor if player is withing splash screen
    bool isPlaying;

    //variables to capture player input
    bool downArrowKeyPressed, upArrowKeyPressed, leftArrowKeyPressed, rightArrowKeyPressed;

    //Utility Functions
    void displaySplashScreen();
    void displayInGameScreen();
    void loadTextures();
    
    //Create Player objects
    std::shared_ptr<Player> player_obj = std::make_shared<Player>(); 
    raylib::Texture2D playerT;
    raylib::Image playerI;

    //Game objects
    std::shared_ptr<raylib::Window>window = std::make_shared<raylib::Window>();
    std::shared_ptr<GameWorld>game_world = std::make_shared<GameWorld>();
};
#endif //DISPLAYMANAGER