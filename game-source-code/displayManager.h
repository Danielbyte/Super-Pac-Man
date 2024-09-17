#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "collisionsManager.h"
#include "gameWorldResources.h"
#include "stopwatch.h"
#include "key.h"

//using namespace raylib;
#include <iostream>
#include <memory>
#include "player.h"

class DisplayManager
{
    public:
    DisplayManager();
    void startGame();
    void handleUserInput(const float dt);
    
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
    void updateGame();
    void displaySplashScreen();
    void displayInGameScreen();
    void drawGameWorld();
    void InitGameWorldTextures();
    void processTileTexture(const std::string element, int tilePosX, int tilePosY);
    void verticalWall(int tilePosX, int tilePosY,const float xOffset,const float yOffset);
    void horizontalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset);
    void topRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset);
    void topLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset);
    void bottomLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset);
    void bottomRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset);
    void longerVerticalWall(int tilePosX, int tilePosY,const float xOffset, const float yOffset);
    void longerVerticalWall_l(int tilePosX, int tilePosY, const float xOffset, const float yOffset);
    void drawMaze();
    void loadTextures();
    
    //Create Player objects
    std::shared_ptr<Player> player_obj = std::make_shared<Player>(); 
    raylib::Texture2D pacmanRight1_T;
    raylib::Texture2D pacmanLeft1_T;
    raylib::Texture2D pacmanDown1_T;
    raylib::Texture2D pacmanUp1_T;
    raylib::Image pacmanRight1_I;
    raylib::Image pacmanLeft1_I;
    raylib::Image pacmanUp1_I;
    raylib::Image pacmanDown1_I;

    raylib::Texture2D horizontalWallPieceT;
    raylib::Image horizontalWallPieceI;
    raylib::Texture2D verticalWallPieceT;
    raylib::Image verticalWallPieceI;

    //Game objects
    std::shared_ptr<raylib::Window>window = std::make_shared<raylib::Window>();
    std::shared_ptr<GameWorld>game_world = std::make_shared<GameWorld>();
    std::vector<std::shared_ptr<GameWorldResources>>maze_resources = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>game_world_textures = {};
    std::unique_ptr<CollisionsManager>collision_manager = std::make_unique<CollisionsManager>();

    StopWatch stop_watch;
};
#endif //DISPLAYMANAGER