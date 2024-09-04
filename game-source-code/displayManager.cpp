#include "displayManager.h"

DisplayManager::DisplayManager() :
quitGame{false},
green{38, 185, 154},
black{0,0,0,255},
isSplashScreen{true},
isPlaying{false}// Player initially not playing
{
    InitWindow(screen_width, screen_height, "SUPER PAC-MAN");
}

void DisplayManager::startGame()
{
    while(!WindowShouldClose() && !quitGame)
    {
        //Handle user Input
        //update game
        //Draw
        BeginDrawing();

        if(isSplashScreen)
           displaySplashScreen();

        if(isPlaying)
           displayInGameScreen();

        handleUserInput();

        ClearBackground(background);

        EndDrawing();
    }
}

void DisplayManager::handleUserInput()
{
    if (IsKeyPressed)
    {
        switch (GetKeyPressed())
        {
        case KEY_ENTER:
        case KEY_KP_ENTER:
            if (isSplashScreen)
            {
                isSplashScreen = false;
                isPlaying = true;
            }
            break;

        default:
            break;
        }
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
    background = black;
}