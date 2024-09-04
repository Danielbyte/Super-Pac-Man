#include "displayManager.h"

DisplayManager::DisplayManager() :
quitGame{false},
green{38, 185, 154},
black{0,0,0,255},
isSplashScreen{true}
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
        EndDrawing();
    }
}

void DisplayManager::handleUserInput()
{
}

void DisplayManager::displaySplashScreen()
{
    ClearBackground(green);
    raylib::DrawText("WELCOME TO SUPER-PACMAN",150,450,20,black);
    raylib::DrawText("PRESS ENTER TO START GAME",150,500,20,black);
    raylib::DrawText("PRESS ARROW KEYS TO MOVE PLAYER",150,550,20,black);
    raylib::DrawText("PRESS ESCAPE(Esc) TO QUIT GAME",150,600,20,black);
}