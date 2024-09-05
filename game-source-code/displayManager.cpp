#include "displayManager.h"

DisplayManager::DisplayManager() :
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
    window->Init(screen_width, screen_height, "SUPER PAC-MAN");
    loadTextures();
}

void DisplayManager::startGame()
{
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
        case KEY_DOWN:
             downArrowKeyPressed = true;
             player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed);
             break;
        case KEY_UP:
             upArrowKeyPressed = true;
             player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed);
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