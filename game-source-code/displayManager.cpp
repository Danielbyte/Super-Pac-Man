#include "displayManager.h"
#include <fstream>
#include <string>

DisplayManager::DisplayManager() :
window_width{800},
window_height{704},
quitGame{false},
green{38, 185, 154},
black{0,0,0,255},
white{255, 255, 255, 255},
isSplashScreen{true},
isPlaying{false},// Player initially not playing
downArrowKeyPressed{false},
upArrowKeyPressed{false}, 
leftArrowKeyPressed{false}, 
rightArrowKeyPressed{false}
{
    window->Init(window_width, window_height, "SUPER PAC-MAN");
    loadTextures();
    game_world->loadMapFromFile();
}

void DisplayManager::startGame()
{
    SetTargetFPS(60);
    while(!WindowShouldClose() && !quitGame)
    {
        //Handle user Input
        handleUserInput();
        //update game

        //Draw
        window->BeginDrawing();
        ClearBackground(background);

        if(isSplashScreen)
           displaySplashScreen();

        if(isPlaying)
           displayInGameScreen();

        window->EndDrawing();
    }
    window->Close();
}

void DisplayManager::handleUserInput()
{
    //Reset Arrow key booleans
    downArrowKeyPressed = false;
    upArrowKeyPressed = false;
    leftArrowKeyPressed = false;
    rightArrowKeyPressed = false;

    if(IsKeyDown(KEY_UP))
    {
        upArrowKeyPressed = true;
         player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed);
    }

    if(IsKeyDown(KEY_DOWN))
    {
        downArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed);
    }

    if(IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER) && !isPlaying && isSplashScreen)
    {
        isSplashScreen = false;
        isPlaying = true;
        InitGameWorldTextures();
        std::cout << "Game world Init!" << std::endl;
    }

    if(IsKeyDown(KEY_LEFT))
    {
        leftArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed);
    }

    if(IsKeyDown(KEY_RIGHT))
    {
        rightArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed);
    }  

}

void DisplayManager::displaySplashScreen()
{
    background = green;
    raylib::DrawText("WELCOME TO SUPER-PACMAN",150,450,20,black);
    raylib::DrawText("PRESS ENTER TO START GAME",150,500,20,black);
    raylib::DrawText("PRESS ARROW KEYS TO MOVE PLAYER",150,550,20,black);
    raylib::DrawText("PRESS ESCAPE(Esc) TO QUIT GAME",150,600,20,black);
}

void DisplayManager::displayInGameScreen()
{
    background = black;//Updating background
    auto [xPlayerPos, yPlayerPos] = player_obj->getPlayerPosition();
    playerT.Draw(xPlayerPos, yPlayerPos);
    //EndDrawing();
}

void DisplayManager::drawGameWorld()
{
}

void DisplayManager::InitGameWorldTextures()
{
    auto game_maze = game_world->getGameMap();
    int tilePosY = 0;
    int tilePosX = 0;
    for (const auto& row : game_maze)
    {
        tilePosY++;
        for (char cell : row)
        {
            tilePosX++;
            processTileTexture(cell, tilePosX, tilePosY);
        }
        tilePosX = 0;
    }
}

void DisplayManager::processTileTexture(const char element, int tilePosX, int tilePosY)
{
    switch (element)
    {
    case '*':
        setWallProperties(tilePosX,tilePosY);
        break;
    
    default:
        break;
    }
}

void DisplayManager::setWallProperties(int tilePosX, int tilePosY)
{
    auto texture = std::make_shared<raylib::Texture2D>();
    auto maxCol = game_world->getNumberOfColumns();
    if (tilePosX == maxCol && tilePosY != 0 && (tilePosY != (game_world->getGameMap()).size()))
        texture->Load("resources/verticalWallPiece.png");
    
    else
     texture->Load("resources/horizontalWallPiece.png");

    game_world_textures.push_back(texture);
    auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY);
    maze_resources.push_back(tile_property);
}

void DisplayManager::loadTextures()
{
    playerI = LoadImage("resources/pacmanRight1.png");     // Loaded in CPU memory (RAM)
    playerT = LoadTextureFromImage(playerI);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(playerI);  

    /*horizontalWallPieceI = LoadImage("resources/horizontalWallPiece.png");
    horizontalWallPieceT = LoadTextureFromImage(horizontalWallPieceI);
    verticalWallPieceI = LoadImage("resources/verticalWallPiece.png");
    verticalWallPieceT = LoadTextureFromImage(verticalWallPieceI);
    UnloadImage(horizontalWallPieceI);
    UnloadImage(verticalWallPieceI);*/
}