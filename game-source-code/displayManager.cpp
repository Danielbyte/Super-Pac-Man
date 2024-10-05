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
playerWon{false}
{
    window->Init(window_width, window_height, "SUPER PAC-MAN");
    loadTextures();
    game_world->loadMapFromFile();
    fruit_objects = game_world->getMazeFruits();
    key_objects = game_world->getMazeKeys();
    lock_objects = game_world->getMazeLocks();
    game_maze_resources.loadFruitTextures(fruit_objects, fruit_textures);
    game_maze_resources.setMazeWalls(game_world_textures, maze_resources);
    game_maze_resources.loadKeyTextures(key_objects, key_textures);
    game_maze_resources.loadLockTextures(lock_objects, lock_textures);
    InitGameWorldTextures();
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

    auto [xPos, yPos] = player_obj->getPlayerPosition();
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

    updateKeys();
    updateFruits();
    updateGhosts();
    playerGhostCollisions();
    updateLocks();
}

void DisplayManager::updateGhosts()
{
    auto [xPlayerPos, yPlayerPos] = player_obj->getPlayerPosition();
    auto playerAtePowerPellet = player_obj->consumedPowerPellet();
    ghost_manager.updateTarget(ghost_objects, xPlayerPos, yPlayerPos);
    auto ghost_texture = ghost_textures.begin();
    for (auto& ghost : ghost_objects)
    {
        auto justReSpawned = ghost->isJustRespawned();
        if (playerAtePowerPellet && !justReSpawned)
        {
            ghost->setMode(Mode::Frightened);
            (*ghost_texture) = frightenedGhostT;
        }

        if(!playerAtePowerPellet && (ghost->getMode() == Mode::Frightened))
        {
            ghost->setMode(Mode::Scatter);
            auto ghostType = ghost->getType();
            switch (ghostType)
            {
            case Type::Blue:
                (*ghost_texture) = blueT;
                break;
            case Type::Pink:
                 (*ghost_texture) = pinkT;
                 break;
            case Type::Red:
                 (*ghost_texture) = redT;
                 break;
            case Type::Orange:
                 (*ghost_texture) = orangeT;  
            default:
                break;
            }
        }

        if (justReSpawned)
        {
            auto ghostType = ghost->getType();
            switch (ghostType)
            {
            case Type::Blue:
                (*ghost_texture) = blueT;
                break;
            case Type::Pink:
                 (*ghost_texture) = pinkT;
                 break;
            case Type::Red:
                 (*ghost_texture) = redT;
                 break;
            case Type::Orange:
                 (*ghost_texture) = orangeT;  
            default:
                break;
            }   
        }
          
        ghost->update(maze_resources,lock_objects ,1/60.0f);
        ++ghost_texture;
    }
}

void DisplayManager::playerGhostCollisions()
{
    auto [xPlayerPos, yPlayerPos] = player_obj->getPlayerPosition();

    for(auto& ghost : ghost_objects)
    {
        auto[xGhostPos, yGhostPos] = ghost->getPosition();
        auto isCollided = collision_manager->playerGhostCollisions(xGhostPos,yGhostPos,xPlayerPos,yPlayerPos);
        auto isSuperPacman = player_obj->isSuperPacman();
        if (isCollided)
        {
            auto ghostFrightened = ghost->getMode();
            if (ghostFrightened == Mode::Frightened)
            {
                ghost->respawn();//Will toggle off for now (Buggy)
                continue;
            }
            if (!isSuperPacman)
            {
                isGameOver = true;
                isPlaying = false;
            }
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

    player_obj->updatePlayerStates();

    if(IsKeyDown(KEY_UP))
    {
        upArrowKeyPressed = true;
         player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
         lock_objects, dt);
    }

    if(IsKeyDown(KEY_DOWN))
    {
        downArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }

    if((IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER)) && !isPlaying && isSplashScreen)
    {
        ghost_manager.restartGhostTimers();
        isSplashScreen = false;
        isPlaying = true;
    }

    if(IsKeyDown(KEY_LEFT))
    {
        leftArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }

    if(IsKeyDown(KEY_RIGHT))
    {
        rightArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }  

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
    background = green;
    raylib::DrawText("WELCOME TO SUPER-PACMAN",50,200,20,black);
    raylib::DrawText("PRESS ENTER TO START GAME",50,250,20,black);
    raylib::DrawText("PRESS ARROW KEYS TO MOVE PLAYER",50,300,20,black);
    raylib::DrawText("PRESS ESCAPE(Esc) TO QUIT GAME",50,350,20,black);
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
    auto [xPlayerPos, yPlayerPos] = player_obj->getPlayerPosition();
    auto playerDirection = player_obj->getPlayerDirection();
    auto isSuperPacman = player_obj->isSuperPacman();
    if (!isSuperPacman)
    {
      switch (playerDirection)
      {
      case Direction::Right:
          pacmanRight1_T.Draw(xPlayerPos, yPlayerPos);
          break;
      case Direction::Left:
          pacmanLeft1_T.Draw(xPlayerPos,yPlayerPos);
          break;
      case Direction::Up:
        pacmanUp1_T.Draw(xPlayerPos,yPlayerPos);
        break;
      case Direction::Down:
        pacmanDown1_T.Draw(xPlayerPos,yPlayerPos);
        break;
      default:
        break;
      }
    }

    if (isSuperPacman)
    {
      switch (playerDirection)
      {
      case Direction::Right:
          SuperpacmanRight1_T.Draw(xPlayerPos - 12.5f, yPlayerPos-12.5f);
          break;
      case Direction::Left:
          SuperpacmanLeft1_T.Draw(xPlayerPos - 12.5f,yPlayerPos - 12.5f);
          break;
      case Direction::Up:
        SuperpacmanUp1_T.Draw(xPlayerPos - 12.5f,yPlayerPos-12.5f);
        break;
      case Direction::Down:
        SuperpacmanDown1_T.Draw(xPlayerPos - 12.5f,yPlayerPos-12.5f);
        break;
      default:
        break;
      }
    }
    //EndDrawing();
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

void DisplayManager::InitGameWorldTextures()
{
    initialiseGhosts();
}

void DisplayManager::initialiseGhosts()
{
    auto blue = std::make_shared<Ghost>();
    blue->setType(Type::Blue);
    ghost_objects.push_back(blue);
    ghost_textures.push_back(blueT);

    auto orange = std::make_shared<Ghost>();
    orange->setType(Type::Orange);
    ghost_objects.push_back(orange);
    ghost_textures.push_back(orangeT);

    auto pink = std::make_shared<Ghost>();
    pink->setType(Type::Pink);
    ghost_objects.push_back(pink);
    ghost_textures.push_back(pinkT);

    auto red = std::make_shared<Ghost>();
    red->setType(Type::Red);
    ghost_objects.push_back(red);
    ghost_textures.push_back(redT);

    ghost_manager.InitialiseGhostPositions(ghost_objects);
}

void DisplayManager::loadTextures()
{
    pacmanRight1_T = LoadTexture("../resources/pacmanRight1.png");
    pacmanLeft1_T = LoadTexture("../resources/pacmanLeft1.png");
    pacmanDown1_T = LoadTexture("../resources/pacmanDown1.png");
    pacmanUp1_T = LoadTexture("../resources/pacmanUp1.png");
    SuperpacmanRight1_T = LoadTexture("../resources/SuperpacmanRight1.png");
    SuperpacmanLeft1_T = LoadTexture("../resources/SuperpacmanLeft1.png");
    SuperpacmanDown1_T = LoadTexture("../resources/SuperpacmanDown1.png");
    SuperpacmanUp1_T = LoadTexture("../resources/SuperpacmanUp1.png");
    
    blueT->Load("../resources/blue1.png");
    redT->Load("../resources/red1.png");
    pinkT->Load("../resources/pink1.png");
    orangeT->Load("../resources/orange1.png");
    frightenedGhostT->Load("../resources/frightened.png");
}

DisplayManager::~DisplayManager()
{
    //Some hoise keeping
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