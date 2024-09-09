#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "gameWorld.h"
#include "collisionsManager.h"
#include "gameWorldResources.h"

//using namespace raylib;
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
    void drawGameWorld();
    void InitGameWorldTextures();
    void processTileTexture(const char element, int tilePosX, int tilePosY);
    void setWallProperties(int tilePosX, int tilePosY);
    void rightCornerDown(int tilePosX, int tilePosY);
    void leftCornerDown(int tilePosX, int tilePosY);
    void leftCornerUp(int tilePosX, int tilePosY);
    void rightCornerUp(int tilePosX, int tilePosY);
    void verticalWall(int tilePosX, int tilePosY);
    void horizontalWall(int tilePosX, int tilePosY);
    void drawMaze();
    void loadTextures();
    
    //Create Player objects
    std::shared_ptr<Player> player_obj = std::make_shared<Player>(); 
    raylib::Texture2D playerT;
    raylib::Image playerI;

    raylib::Texture2D horizontalWallPieceT;
    raylib::Image horizontalWallPieceI;
    raylib::Texture2D verticalWallPieceT;
    raylib::Image verticalWallPieceI;

    //Game objects
    std::shared_ptr<raylib::Window>window = std::make_shared<raylib::Window>();
    std::shared_ptr<GameWorld>game_world = std::make_shared<GameWorld>();
    std::vector<std::shared_ptr<GameWorldResources>>maze_resources = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>game_world_textures = {};
};
#endif //DISPLAYMANAGER