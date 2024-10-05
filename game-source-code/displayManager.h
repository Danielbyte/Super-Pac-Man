#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include "collisionsManager.h"
#include "gameWorldResources.h"
#include "stopwatch.h"
#include "key.h"
#include "fruit.h"
#include "lock.h"
#include "ghostManager.h"
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
    raylib::Color red;
    bool isSplashScreen; //flag to monitor if player is withing splash screen
    bool isPlaying;

    //variables to capture player input
    bool downArrowKeyPressed, upArrowKeyPressed, leftArrowKeyPressed, rightArrowKeyPressed;

    //Utility Functions
    void updateGame();
    void displaySplashScreen();
    void displayGameOverScreen();
    void displayPlayerWonScreen();
    void displayInGameScreen();
    void drawGameWorld();
    void InitGameWorldTextures();
    void drawMaze();
    void loadTextures();
    void initialiseKeys();
    void drawKeys();
    void updateKeys();
    void initialiseFruits();
    void drawFruits();
    void initialiseLocks();
    void drawLocks();
    void updateLocks();
    void updateFruits();
    void initialiseGhosts();
    void drawGhosts();
    void updateGhosts();
    void playerGhostCollisions();
    
    //Create Player objects
    std::shared_ptr<Player> player_obj = std::make_shared<Player>(); 
    raylib::Texture2D pacmanRight1_T;
    raylib::Texture2D pacmanLeft1_T;
    raylib::Texture2D pacmanDown1_T;
    raylib::Texture2D pacmanUp1_T;
    raylib::Texture2D SuperpacmanRight1_T;
    raylib::Texture2D SuperpacmanLeft1_T;
    raylib::Texture2D SuperpacmanDown1_T;
    raylib::Texture2D SuperpacmanUp1_T;

    std::shared_ptr<raylib::Texture2D> keyT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> fruitT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> superPelletT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> powerPelletT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> VlockT = std::make_shared<raylib::Texture2D>();//Vertical lock
    std::shared_ptr<raylib::Texture2D> HlockT = std::make_shared<raylib::Texture2D>();//Horizontal lock
    std::shared_ptr<raylib::Texture2D> blueT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> redT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> pinkT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> frightenedGhostT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> orangeT = std::make_shared<raylib::Texture2D>();

    //Game objects
    std::shared_ptr<raylib::Window>window = std::make_shared<raylib::Window>();
    std::shared_ptr<GameWorld>game_world = std::make_shared<GameWorld>();
    std::vector<std::shared_ptr<GameWorldResources>>maze_resources = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>game_world_textures = {};
    std::unique_ptr<CollisionsManager>collision_manager = std::make_unique<CollisionsManager>();
    std::vector<std::shared_ptr<Key>>key_objects = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>key_textures = {};
    std::vector<std::shared_ptr<Fruit>>fruit_objects = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>fruit_textures = {};

    std::vector<std::shared_ptr<Lock>>lock_objects = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>lock_textures = {};

    std::vector<std::shared_ptr<Ghost>>ghost_objects = {};
    std::vector<std::shared_ptr<raylib::Texture2D>>ghost_textures = {};

    StopWatch stop_watch;
    GhostManager ghost_manager;
    GameWorldResources game_maze_resources;
    bool isGameOver;
    bool playerWon;
};
#endif //DISPLAYMANAGER