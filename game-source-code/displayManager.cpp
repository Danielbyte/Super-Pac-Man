#include "displayManager.h"
#include <fstream>
#include <string>

DisplayManager::DisplayManager() :
window_width{528},
window_height{576},
quitGame{false},
green{38, 185, 154},
black{0,0,0,255},
white{255, 255, 255, 255},
red{230, 41, 55, 255},
isSplashScreen{true},
isPlaying{false},// Player initially not playing
downArrowKeyPressed{false},
upArrowKeyPressed{false}, 
leftArrowKeyPressed{false}, 
rightArrowKeyPressed{false},
isGameOver{false},
playerWon{false},
buttoPressed{false}
{
    window->Init(window_width, window_height, "SUPER PAC-MAN");
    splashScreenT->Load("../resources/Splashscreen.png");
    game_world->loadMapFromFile();
    fruit_objects = game_world->getMazeFruits();
    key_objects = game_world->getMazeKeys();
    lock_objects = game_world->getMazeLocks();
    game_maze_resources.loadFruitTextures(fruit_objects, fruit_textures);
    game_maze_resources.setMazeWalls(game_world_textures, maze_resources);
    game_maze_resources.loadKeyTextures(key_objects, key_textures);
    game_maze_resources.loadLockTextures(lock_objects, lock_textures);
    ghost_manager.initialiseGhosts(ghost_objects);
    ghost_resources.initialiseTextures(ghost_objects, ghost_textures);
    player_resources.loadTextures();
}

void DisplayManager::startGame()
{
    SetTargetFPS(60);
    float timeSinceLatUpdate = 0.0f;
    float framesPerSecond = (1/60.0f);//60Hz
    stop_watch.restartTimer();
    while(!WindowShouldClose() && !quitGame)
    {
        timeSinceLatUpdate += stop_watch.elapsedTime();
        while (timeSinceLatUpdate > framesPerSecond)
        {
            timeSinceLatUpdate -= framesPerSecond;
            //Handle user Input
            handleUserInput(framesPerSecond);
            //update game
            updateGame();
            stop_watch.restartTimer();
        }
        //Draw
        window->BeginDrawing();
        ClearBackground(background);

        if(isSplashScreen)
           displaySplashScreen();

        if(isGameOver)
           displayGameOverScreen();

        if(playerWon)
          displayPlayerWonScreen();

        if(isPlaying)
           displayInGameScreen();

        window->EndDrawing();
    }
    window->Close();
}

void DisplayManager::updateGame()
{
    if(!isPlaying)
    return;

    updatePlayer();
    updateKeys();
    updateFruits();
    updateGhosts();
    playerGhostCollisions();
    updateLocks();
}

void DisplayManager::updateGhosts()
{
    ghost_manager.updateGhostModes(ghost_objects,player_obj);
    ghost_resources.updateTextures(ghost_textures,ghost_objects, player_obj->isSuperPacman());

    for (auto& ghost : ghost_objects)
    {          
        ghost->update(maze_resources,lock_objects ,1/60.0f);
    }
}

void DisplayManager::playerGhostCollisions()
{
    auto [xPlayerPos, yPlayerPos] = player_obj->getPosition();

    for(auto& ghost : ghost_objects)
    {
        auto[xGhostPos, yGhostPos] = ghost->getPosition();
        auto isCollided = collision_manager->playerGhostCollisions(xGhostPos,yGhostPos,xPlayerPos,yPlayerPos);
        auto isSuperPacman = player_obj->isSuperPacman();
        auto ghostMode = ghost->getMode();
        if (isCollided && !isSuperPacman && ghostMode != Mode::Frightened)
        {
            isGameOver = true;
            isPlaying = false;
        }
    }
}

void DisplayManager::updateLocks()
{
    auto lock = lock_objects.begin();
    auto lock_texture = lock_textures.begin();
    while (lock != lock_objects.end())
    {
        if ((*lock)->getIsOpen())
        {
            lock_objects.erase(lock);
            lock_textures.erase(lock_texture);
        }
        else
        {
            ++lock;
            ++lock_texture;
        }
    }
}

void DisplayManager::handleUserInput(const float dt)
{
    //Reset Arrow key booleans
    downArrowKeyPressed = false;
    upArrowKeyPressed = false;
    leftArrowKeyPressed = false;
    rightArrowKeyPressed = false;
    buttoPressed = false;

    player_obj->updatePlayerStates();

    if(IsKeyDown(KEY_UP) && IsKeyUp(KEY_DOWN) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
    {
         upArrowKeyPressed = true;
         buttoPressed = true;
         player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
         lock_objects, dt);
    }

    if(IsKeyDown(KEY_DOWN) && IsKeyUp(KEY_UP) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT))
    {
        downArrowKeyPressed = true;
        buttoPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }

    if((IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER)) && !isPlaying && isSplashScreen)
    {
        ghost_manager.restartGhostTimers();
        isSplashScreen = false;
        isPlaying = true;
    }

    if(IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN))
    {
        leftArrowKeyPressed = true;
        buttoPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }

    if(IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_UP) && IsKeyUp(KEY_DOWN))
    {
        rightArrowKeyPressed = true;
        buttoPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }  

}

void DisplayManager::updatePlayer()
{
    auto [xPos, yPos] = player_obj->getPosition();
    collision_manager->playerKeyCollisions(key_objects,xPos,yPos,lock_objects);

    auto isSuPerPacman = player_obj->isSuperPacman();
    auto atePowerPellet = player_obj->consumedPowerPellet();

    auto prevPlayerState = isSuPerPacman;
    auto powerPelletPrevState = atePowerPellet;
    collision_manager->playerFruitCollisions(fruit_objects, xPos, yPos, isSuPerPacman, atePowerPellet);

    if (isSuPerPacman && (isSuPerPacman != prevPlayerState))//detect a difference in state
        player_obj->setToSuperPacmanMode();

    if(atePowerPellet && (atePowerPellet != powerPelletPrevState))
       player_obj->inPowerPelletMode();

    player_resources.updateTexture(player_obj,player_texture, buttoPressed);
}

void DisplayManager::updateKeys()
{
    auto key_object = key_objects.begin();
    auto key_texture = key_textures.begin();
    while(key_object != key_objects.end())
    {
        if((*key_object)->getIfCanDelete())
        {
            key_objects.erase(key_object);
            key_textures.erase(key_texture);
        }
        else
        {
          ++key_object;
          ++key_texture;
        }
    }
}

void DisplayManager::updateFruits()
{
    auto fruit_object = fruit_objects.begin();
    auto fruit_texture = fruit_textures.begin();
    while(fruit_object != fruit_objects.end())
    {
        if ((*fruit_object)->getIfCanDelete())
        {
            fruit_objects.erase(fruit_object);
            fruit_textures.erase(fruit_texture);
        }

        else
        {
            ++fruit_object;
            ++fruit_texture;
        }
    }

    if (fruit_objects.empty())
    {
        playerWon = true;
        isPlaying = false;
    }
}

void DisplayManager::displaySplashScreen()
{
    splashScreenT->Draw();
}

void DisplayManager::displayGameOverScreen()
{
    background = black;
    raylib::DrawText("GAME OVER! PRESS Esc TO QUIT",50,300,20,red);
}

void DisplayManager::displayPlayerWonScreen()
{
    background = black;
    raylib::DrawText("YOU WON! PRESS Esc TO QUIT",50,300,20,green);
}

void DisplayManager::displayInGameScreen()
{
    drawMaze();
    drawKeys();
    drawFruits();
    drawLocks();
    drawGhosts();

    background = black;//Updating background
    auto [xPlayerPos, yPlayerPos] = player_obj->getPosition();
    auto playerDirection = player_obj->getDirection();
    auto isSuperPacman = player_obj->isSuperPacman();
    player_resources.updateTexture(player_obj, player_texture,buttoPressed);

    if (!isSuperPacman)
    {
        player_texture->Draw(xPlayerPos, yPlayerPos);
        return;
    }
       
    auto offset = 12.5f;
    player_texture->Draw(xPlayerPos-offset, yPlayerPos-offset);
}

void DisplayManager::drawMaze()
{
    auto tile_property = maze_resources.begin();
    auto tile_texture = game_world_textures.begin();
    while(tile_property != maze_resources.end())
    {
        auto [tileScreenPosX, tileScreenPosY] = (*tile_property)->getTileScreenPosition();
        (*tile_texture)->Draw(tileScreenPosX,tileScreenPosY);
        ++tile_property;
        ++tile_texture;
    }
}

void DisplayManager::drawKeys()
{
    auto key = key_objects.begin();
    auto key_texture = key_textures.begin();

    while(key != key_objects.end())
    {
        auto [xPos, yPos] = (*key)->getPosition();
        (*key_texture)->Draw(xPos, yPos);
        ++key_texture;
        ++key;
    }
}

void DisplayManager::drawFruits()
{
    auto fruit = fruit_objects.begin();
    auto fruit_texture = fruit_textures.begin();
    while(fruit != fruit_objects.end())
    {
        auto [xPos, yPos] = (*fruit)->getPosition();
        (*fruit_texture)->Draw(xPos, yPos);
        ++fruit;
        ++fruit_texture;
    }
}

void DisplayManager::drawLocks()
{
    auto lock = lock_objects.begin();
    auto lock_texture = lock_textures.begin();
    while(lock != lock_objects.end())
    {
        auto [xPos, yPos] = (*lock)->getPosition();
        (*lock_texture)->Draw(xPos, yPos);
        ++lock;
        ++lock_texture;
    }
}

void DisplayManager::drawGhosts()
{
    auto ghost = ghost_objects.begin();
    auto ghost_texture = ghost_textures.begin();
    while(ghost != ghost_objects.end())
    {
        auto[xPos, yPos] = (*ghost)->getPosition();
        (*ghost_texture)->Draw(xPos, yPos);
        ++ghost;
        ++ghost_texture;
    }
}

void DisplayManager::drawGameWorld()
{
}

DisplayManager::~DisplayManager()
{
    //Some house keeping
    ghost_textures.clear();
    ghost_objects.clear();
    lock_textures.clear();
    lock_objects.clear();
    fruit_textures.clear();
    fruit_objects.clear();
    key_textures.clear();
    key_objects.clear();
    game_world_textures.clear();
    maze_resources.clear();
}