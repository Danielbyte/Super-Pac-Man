#include "displayManager.h"

DisplayManager::DisplayManager()
{
    InitWindow(screen_width, screen_height, "SUPER PAC-MAN");
}

void DisplayManager::startGame()
{
    std::cout << "Screen Width: "<<screen_width<< " Screen height: "<<screen_height << std::endl;
}