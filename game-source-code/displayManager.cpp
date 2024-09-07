#include "displayManager.h"

DisplayManager::DisplayManager() :
window_width{800},
window_height{700},
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
        BeginDrawing();
        ClearBackground(background);
        if(isSplashScreen)
           displaySplashScreen();

        if(isPlaying)
           displayInGameScreen();

        EndDrawing();
    }
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

    if(IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER))
    {
        isSplashScreen = false;
        isPlaying = true;
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

void DisplayManager::loadTextures()
{
    playerI = LoadImage("resources/pacman.png");     // Loaded in CPU memory (RAM)
    playerT = LoadTextureFromImage(playerI);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(playerI);  
}