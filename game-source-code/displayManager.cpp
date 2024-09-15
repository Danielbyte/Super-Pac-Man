#include "displayManager.h"
#include <fstream>
#include <string>

DisplayManager::DisplayManager() :
window_width{528},
window_height{624},
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

        if(isPlaying)
           displayInGameScreen();

        window->EndDrawing();
    }
    window->Close();
}

void DisplayManager::updateGame()
{
    //collision_manager->playerWallCollisions(maze_resources,player_obj);
}

void DisplayManager::handleUserInput(const float dt)
{
    //Reset Arrow key booleans
    downArrowKeyPressed = false;
    upArrowKeyPressed = false;
    leftArrowKeyPressed = false;
    rightArrowKeyPressed = false;

    if(IsKeyDown(KEY_UP))
    {
        upArrowKeyPressed = true;
         player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources, dt);
    }

    if(IsKeyDown(KEY_DOWN))
    {
        downArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources, dt);
    }

    if(IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER) && !isPlaying && isSplashScreen)
    {
        isSplashScreen = false;
        isPlaying = true;
        std::cout << "Game world Init!" << std::endl;
    }

    if(IsKeyDown(KEY_LEFT))
    {
        leftArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources, dt);
    }

    if(IsKeyDown(KEY_RIGHT))
    {
        rightArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources, dt);
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
    auto playerDirection = player_obj->getPlayerDirection();
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
    drawMaze();
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
        for (const auto tile : row)
        {
            processTileTexture(tile, tilePosX, tilePosY);
            tilePosX++;
        }
        std::cout << std::endl;
        tilePosY++;
        tilePosX = 0;
    }
}

void DisplayManager::processTileTexture(const std::string element, int tilePosX, int tilePosY)
{
    float xOffset = 0;
    float yOffset = 0;
    if (element == "10") //Vertical wall on the left
    {
        xOffset = 0;
        yOffset = 0;
        verticalWall(tilePosX, tilePosY, xOffset, yOffset);
    }

    if (element == "01")//Vertical wall on the right
    {
        if (tilePosX == 10)
        {
            xOffset = (5/6.0f);//This vertical wall should be at the border of the maze
        }
        else
        {
            xOffset = (1/6.0f);//1/6 x 48 = 8
        }
        
        yOffset = 0;
        verticalWall(tilePosX, tilePosY, xOffset, yOffset);
    }

    if (element == "-")
    {
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "┐")
    {
        xOffset = 0;
        yOffset = 0;
        topRightCorner(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "┌")
    {
        xOffset = 0;
        yOffset = 0;
        topLeftCorner(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "└")
    {
        xOffset = 0;
        yOffset = 0;
        bottomLeftCorner(tilePosX,tilePosY,xOffset,yOffset);
    }

        if (element == "┘")
    {
        xOffset = 0;
        yOffset = 0;
        bottomRightCorner(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "_")
    {
        //Bottom horizontal
        xOffset = 0;
        yOffset = 5/6.0f;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "=")
    {
        //Parallel horizontal
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
        yOffset = 5/6.0f;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
    }
       
    /*switch (element)
    {
    case "10":
        setWallProperties(tilePosX,tilePosY);
        break;
    case '=':
        rightCornerDown(tilePosX,tilePosY);
        break;
    case '-':
        leftCornerDown(tilePosX,tilePosY);
        break;
    case 'w':
        leftCornerUp(tilePosX,tilePosY);
        break;
    case 'q':
        rightCornerUp(tilePosX,tilePosY);
        break;
    case 'Q':
        innerHorizontalRightEdge(tilePosX,tilePosY);
        break;
    case '#':
    horizontalWall(tilePosX, tilePosY);
        break;
    case '1':
    xOffset = 0;
    yOffset = 0;
    verticalWall(tilePosX, tilePosY, xOffset, yOffset);
        break;
    case '+':
    innerRightCornerDown(tilePosX, tilePosY);
    break;
    case 'L':
    xOffset = 0;
    yOffset = -1;
    longerVerticalWall(tilePosX, tilePosY,xOffset,yOffset);
    break;
    case 'l':
    yOffset = 0;
    xOffset = 0;
    longerVerticalWall_l(tilePosX, tilePosY,xOffset, yOffset);
    break;
    case '[':
    xOffset = 0;
    innerLeftCornerDown(tilePosX, tilePosY);
    break;
    case 'A':
    innerHorizontalLeftEdge(tilePosX,tilePosY);
    break;
    case 's':
    offsettedinnerHorizontal(tilePosX,tilePosY);
    break;
    case '2':
    yOffset = 0.0f;
    xOffset = -0.01f;
        verticalWall(tilePosX, tilePosY, xOffset,yOffset);
        break;
    default:
        break;
    }*/
}

void DisplayManager::topRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset)
{
    horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
    auto newXoffset = 5/6.0f;//place vertical piece at the end of the horizontal piece to form ┐
    verticalWall(tilePosX,tilePosY,newXoffset,yOffset);
}

void DisplayManager::topLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset)
{
    horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
    verticalWall(tilePosX,tilePosY,xOffset,yOffset);
}

void DisplayManager::bottomLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset)
{
    verticalWall(tilePosX,tilePosY,xOffset,yOffset);
    auto newYoffset = 5/6.0f;
    horizontalWall(tilePosX,tilePosY,xOffset,newYoffset);
}

void DisplayManager::bottomRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset)
{
    auto newYoffset = 5/6.0f;
    horizontalWall(tilePosX,tilePosY,xOffset,newYoffset);
    auto newXoffset = 5/6.0f;
    verticalWall(tilePosX,tilePosY,newXoffset,yOffset);
}

void DisplayManager::verticalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/verticalWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall,xOffset,yOffset);
  maze_resources.push_back(tile_property);
}

void DisplayManager::longerVerticalWall(int tilePosX, int tilePosY, const float xOffset, const float yOffset)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/verticalLongerWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall, xOffset, yOffset);
  maze_resources.push_back(tile_property);
}

void DisplayManager::longerVerticalWall_l(int tilePosX, int tilePosY, const float xOffset, const float yOffset)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/verticalLongerWallPiece_l.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall, xOffset, yOffset);
  maze_resources.push_back(tile_property);
}

void DisplayManager::horizontalWall(int tilePosX, int tilePosY,const float xOffset,const float yOffset)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall, xOffset, yOffset);
  maze_resources.push_back(tile_property);
}

void DisplayManager::setWallProperties(int tilePosX, int tilePosY)
{  
    auto texture = std::make_shared<raylib::Texture2D>();
    auto maxCol = game_world->getNumberOfColumns();

    if ((tilePosX == 0 || tilePosX == (maxCol-1)) && (tilePosY >= 1 && tilePosY < ((game_world->getGameMap().size())-1)))
    {
        texture->Load("../resources/verticalWallPiece.png"); 
        auto tile_property = std::make_shared<GameWorldResources>();
        tile_property->initialiseGameBorder(tilePosX, tilePosY, ObjectType::VerticalWall);
        maze_resources.push_back(tile_property);
    }
        
    else if (tilePosY == 0 || tilePosY == ((game_world->getGameMap().size())-1))
    {
        texture->Load("../resources/horizontalWallPiece.png");
        auto tile_property = std::make_shared<GameWorldResources>();
        tile_property->initialiseGameBorder(tilePosX, tilePosY, ObjectType::HorizontalWall);
        maze_resources.push_back(tile_property);
    }
    game_world_textures.push_back(texture);
}

void DisplayManager::rightCornerDown(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/RightCornerDown.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>();
  tile_property->initialiseGameBorder(tilePosX, tilePosY, ObjectType::Other);
  maze_resources.push_back(tile_property);
}

void DisplayManager::innerRightCornerDown(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/innerRightCornerDown.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::Other, 0, 0);
  maze_resources.push_back(tile_property);
}

void DisplayManager::rightCornerUp(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/RightCornerUp.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>();
  tile_property->initialiseGameBorder(tilePosX, tilePosY, ObjectType::Other);
  maze_resources.push_back(tile_property);
}

void DisplayManager::innerHorizontalRightEdge(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall, -0.05f, 0.05f);
  maze_resources.push_back(tile_property);
}

void DisplayManager::innerHorizontalLeftEdge(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall, 0.05f, 0.05f);
  maze_resources.push_back(tile_property);
}

void DisplayManager::offsettedinnerHorizontal(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall, -0.05f, 0.00f);
  maze_resources.push_back(tile_property);
}

void DisplayManager::leftCornerDown(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/LeftCornerDown.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>();
  tile_property->initialiseGameBorder(tilePosX, tilePosY, ObjectType::Other);
  maze_resources.push_back(tile_property);
}

void DisplayManager::innerLeftCornerDown(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/innerLeftCornerDown.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::Other, 0, 0);
  maze_resources.push_back(tile_property);
}

void DisplayManager::leftCornerUp(int tilePosX, int tilePosY)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/LeftCornerUp.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>();
  tile_property->initialiseGameBorder(tilePosX, tilePosY, ObjectType::Other);
  maze_resources.push_back(tile_property);
}

void DisplayManager::loadTextures()
{
    auto texture = std::make_shared<raylib::Texture2D>();
    pacmanRight1_I = LoadImage("../resources/pacmanRight1.png");     // Loaded in CPU memory (RAM)
    pacmanRight1_T = LoadTextureFromImage(pacmanRight1_I);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(pacmanRight1_I); 

    pacmanLeft1_I = LoadImage("../resources/pacmanLeft1.png");     // Loaded in CPU memory (RAM)
    pacmanLeft1_T = LoadTextureFromImage(pacmanLeft1_I);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(pacmanLeft1_I);
    
    pacmanDown1_I= LoadImage("../resources/pacmanDown1.png");
    pacmanDown1_T = LoadTextureFromImage(pacmanDown1_I);
    UnloadImage(pacmanDown1_I);

    pacmanUp1_I= LoadImage("../resources/pacmanUp1.png");
    pacmanUp1_T = LoadTextureFromImage(pacmanUp1_I);
    UnloadImage(pacmanUp1_I);

    /*horizontalWallPieceI = LoadImage("resources/horizontalWallPiece.png");
    horizontalWallPieceT = LoadTextureFromImage(horizontalWallPieceI);
    verticalWallPieceI = LoadImage("resources/verticalWallPiece.png");
    verticalWallPieceT = LoadTextureFromImage(verticalWallPieceI);
    UnloadImage(horizontalWallPieceI);
    UnloadImage(verticalWallPieceI);*/
    /*┌
      Π
      ┘
      ┐
      └
    */
}