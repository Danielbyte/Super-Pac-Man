#include "displayManager.h"

DisplayManager::DisplayManager() :
quitGame{false},
green{38, 185, 154}
{
    InitWindow(screen_width, screen_height, "SUPER PAC-MAN");
}

void DisplayManager::startGame()
{
    while(!WindowShouldClose())
    {
        //Handle user Input
        //update game
        //Draw
        BeginDrawing();
        ClearBackground(green);
        EndDrawing();
    }
}

void DisplayManager::handleUserInput()
{
}