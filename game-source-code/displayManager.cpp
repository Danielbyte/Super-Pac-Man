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
    auto [xPos, yPos] = player_obj->getPlayerPosition();
    collision_manager->playerKeyCollisions(key_objects,xPos,yPos);
    collision_manager->playerFruitCollisions(fruit_objects, xPos, yPos);
    updateKeys();
    updateFruits();
    updateGhosts();
}

void DisplayManager::updateGhosts()
{
    auto [xPlayerPos, yPlayerPos] = player_obj->getPlayerPosition();
    ghost_manager.updateTarget(ghost_objects, xPlayerPos, yPlayerPos);

    for (auto& ghost : ghost_objects)
    {
        ghost->update(maze_resources, 1/60.0f);
    }
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
         player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
         lock_objects, dt);
    }

    if(IsKeyDown(KEY_DOWN))
    {
        downArrowKeyPressed = true;
        player_obj->movePlayer(rightArrowKeyPressed,leftArrowKeyPressed,downArrowKeyPressed,upArrowKeyPressed, maze_resources,
        lock_objects, dt);
    }

    if(IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_KP_ENTER) && !isPlaying && isSplashScreen)
    {
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
    drawKeys();
    drawFruits();
    drawLocks();
    drawGhosts();
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
        tilePosY++;
        tilePosX = 0;
    }

    initialiseKeys();
    initialiseFruits();
    initialiseLocks();
    initialiseGhosts();
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
        xOffset = (5/6.0f);//This vertical wall should be at the border of the maze
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

    if (element == "||")
    {
        //Parallel vertical
        xOffset = 0;
        yOffset = 0;
        verticalWall(tilePosX,tilePosY,xOffset,yOffset);
        xOffset = 5/6.0f;
        verticalWall(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "Π")
    {
        //As the symbol suggests, you welcome
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset);
        verticalWall(tilePosX,tilePosY,xOffset,yOffset);
        xOffset = 5/6.0f;//the far right wall
        verticalWall(tilePosX,tilePosY,xOffset,yOffset);
    }
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

void DisplayManager::horizontalWall(int tilePosX, int tilePosY,const float xOffset,const float yOffset)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  game_world_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall, xOffset, yOffset);
  maze_resources.push_back(tile_property);
}

void DisplayManager::initialiseKeys()
{
    std::shared_ptr<Key>key1 = std::make_shared<Key>();
    key1->setPosition(16.5f,8.5f);
    key_objects.push_back(key1);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key2 = std::make_shared<Key>();
    key2->setPosition(496.5f,8.5f);
    key_objects.push_back(key2);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key3 = std::make_shared<Key>();
    key3->setPosition(16.5f,536.0f);
    key_objects.push_back(key3);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key4 = std::make_shared<Key>();
    key4->setPosition(496.5f,536.0f);
    key_objects.push_back(key4);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key5 = std::make_shared<Key>();
    key5->setPosition(111.0f,488.0f);
    key_objects.push_back(key5);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key6 = std::make_shared<Key>();
    key6->setPosition(402.0f,488.0f);
    key_objects.push_back(key6);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key7 = std::make_shared<Key>();
    key7->setPosition(496.5f,290.0f);
    key_objects.push_back(key7);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key8 = std::make_shared<Key>();
    key8->setPosition(496.5f,206.5f);
    key_objects.push_back(key8);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key9 = std::make_shared<Key>();
    key9->setPosition(16.5f,206.5f);
    key_objects.push_back(key9);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key10 = std::make_shared<Key>();
    key10->setPosition(402.0f,110.0f);
    key_objects.push_back(key10);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key11 = std::make_shared<Key>();
    key11->setPosition(111.0f,110.0f);
    key_objects.push_back(key11);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key12 = std::make_shared<Key>();
    key12->setPosition(255.0f,390.0f);
    key_objects.push_back(key12);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key13 = std::make_shared<Key>();
    key13->setPosition(16.5f,290.0f);
    key_objects.push_back(key13);
    key_textures.push_back(keyT);

    std::shared_ptr<Key>key14 = std::make_shared<Key>();
    key14->setPosition(163.0f,290.0f);
    key_objects.push_back(key14);
    key_textures.push_back(keyT);
    
    std::shared_ptr<Key>key15 = std::make_shared<Key>();
    key15->setPosition(353.0f,290.0f);
    key_objects.push_back(key15);
    key_textures.push_back(keyT);
    
}

void DisplayManager::initialiseFruits()
{
    std::shared_ptr<Fruit>fruit1 = std::make_shared<Fruit>();
    fruit1->setPosition(56.5f,152.5f);
    fruit_objects.push_back(fruit1);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit2 = std::make_shared<Fruit>();
    fruit2->setPosition(104.5f,152.5f);
    fruit_objects.push_back(fruit2);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit3 = std::make_shared<Fruit>();
    fruit3->setPosition(104.5f,200.5f);
    fruit_objects.push_back(fruit3);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit4 = std::make_shared<Fruit>();
    fruit4->setPosition(104.5f,248.5f);
    fruit_objects.push_back(fruit4);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit5 = std::make_shared<Fruit>();
    fruit5->setPosition(440.0f,345.0f);
    fruit_objects.push_back(fruit5);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit6 = std::make_shared<Fruit>();
    fruit6->setPosition(440.0f,392.0f);
    fruit_objects.push_back(fruit6);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit7 = std::make_shared<Fruit>();
    fruit7->setPosition(440.0f,152.5f);
    fruit_objects.push_back(fruit7);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit8 = std::make_shared<Fruit>();
    fruit8->setPosition(391.0f,152.5f);
    fruit_objects.push_back(fruit8);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit9 = std::make_shared<Fruit>();
    fruit9->setPosition(391.0f,200.5f);
    fruit_objects.push_back(fruit9);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit10 = std::make_shared<Fruit>();
    fruit10->setPosition(391.0f,248.5f);
    fruit_objects.push_back(fruit10);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit11 = std::make_shared<Fruit>();
    fruit11->setPosition(485.0f,248.5f);
    fruit_objects.push_back(fruit11);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit12 = std::make_shared<Fruit>();
    fruit12->setPosition(6.5f,249.5f);
    fruit_objects.push_back(fruit12);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit13 = std::make_shared<Fruit>();
    fruit13->setPosition(56.5f,345.0f);
    fruit_objects.push_back(fruit13);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit14 = std::make_shared<Fruit>();
    fruit14->setPosition(56.5f,392.0f);
    fruit_objects.push_back(fruit14);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit15 = std::make_shared<Fruit>();
    fruit15->setPosition(150.5f,536.0f);
    fruit_objects.push_back(fruit15);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit16 = std::make_shared<Fruit>();
    fruit16->setPosition(200.5f,536.0f);
    fruit_objects.push_back(fruit16);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit17 = std::make_shared<Fruit>();
    fruit17->setPosition(247.5f,536.0f);
    fruit_objects.push_back(fruit17);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit18 = std::make_shared<Fruit>();
    fruit18->setPosition(297.5f,536.0f);
    fruit_objects.push_back(fruit18);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit19 = std::make_shared<Fruit>();
    fruit19->setPosition(345.5f,536.0f);
    fruit_objects.push_back(fruit19);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit20 = std::make_shared<Fruit>();
    fruit20->setPosition(150.5f,55.5f);
    fruit_objects.push_back(fruit20);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit21 = std::make_shared<Fruit>();
    fruit21->setPosition(200.5f,55.5f);
    fruit_objects.push_back(fruit21);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit22 = std::make_shared<Fruit>();
    fruit22->setPosition(247.5f,55.5f);
    fruit_objects.push_back(fruit22);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit23 = std::make_shared<Fruit>();
    fruit23->setPosition(297.5f,55.5f);
    fruit_objects.push_back(fruit23);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit24 = std::make_shared<Fruit>();
    fruit24->setPosition(345.5f,55.5f);
    fruit_objects.push_back(fruit24);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit25 = std::make_shared<Fruit>();
    fruit25->setPosition(297.5f,345.0f);
    fruit_objects.push_back(fruit25);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit26 = std::make_shared<Fruit>();
    fruit26->setPosition(343.5f,392.0f);
    fruit_objects.push_back(fruit26);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit27 = std::make_shared<Fruit>();
    fruit27->setPosition(343.5f,440.5f);
    fruit_objects.push_back(fruit27);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit28 = std::make_shared<Fruit>();
    fruit28->setPosition(200.5f,345.0f);
    fruit_objects.push_back(fruit28);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit29 = std::make_shared<Fruit>();
    fruit29->setPosition(150.5f,392.0f);
    fruit_objects.push_back(fruit29);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit30 = std::make_shared<Fruit>();
    fruit30->setPosition(150.5f,440.5f);
    fruit_objects.push_back(fruit30);
    fruit_textures.push_back(fruitT);

    std::shared_ptr<Fruit>fruit31 = std::make_shared<Fruit>();
    fruit31->setPosition(247.5f,440.5f);
    fruit_objects.push_back(fruit31);
    fruit_textures.push_back(fruitT);
}

void DisplayManager::initialiseLocks()
{
    std::shared_ptr<Lock>lock1 = std::make_shared<Lock>();
    lock1->setPosition(56.5f,146.0f);
    lock1->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock1);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock2 = std::make_shared<Lock>();
    lock2->setPosition(56.5f,93.0f);
    lock2->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock2);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock3 = std::make_shared<Lock>();
    lock3->setPosition(56.5f,48.0f);
    lock3->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock3);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock4 = std::make_shared<Lock>();
    lock4->setPosition(56.5f,190.0f);
    lock4->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock4);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock5 = std::make_shared<Lock>();
    lock5->setPosition(140.0f,240.0f);
    lock5->setLockType(LockType::Vertical);
    lock_objects.push_back(lock5);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock6 = std::make_shared<Lock>();
    lock6->setPosition(98.5f,240.0f);
    lock6->setLockType(LockType::Vertical);
    lock_objects.push_back(lock6);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock7 = std::make_shared<Lock>();
    lock7->setPosition(56.5f,336.5f);
    lock7->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock7);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock8 = std::make_shared<Lock>();
    lock8->setPosition(56.5f,429.0f);
    lock8->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock8);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock9 = std::make_shared<Lock>();
    lock9->setPosition(56.5f,480.0f);
    lock9->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock9);
    lock_textures.push_back(HlockT);
    
    std::shared_ptr<Lock>lock10 = std::make_shared<Lock>();
    lock10->setPosition(56.5f,525.0f);
    lock10->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock10);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock11 = std::make_shared<Lock>();
    lock11->setPosition(145.0f,536.0f);
    lock11->setLockType(LockType::Vertical);
    lock_objects.push_back(lock11);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock12 = std::make_shared<Lock>();
    lock12->setPosition(380.5f,536.0f);
    lock12->setLockType(LockType::Vertical);
    lock_objects.push_back(lock12);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock13 = std::make_shared<Lock>();
    lock13->setPosition(433.5f,525.0f);
    lock13->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock13);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock14 = std::make_shared<Lock>();
    lock14->setPosition(433.5f,480.0f);
    lock14->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock14);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock15 = std::make_shared<Lock>();
    lock15->setPosition(433.5f,429.0f);
    lock15->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock15);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock16 = std::make_shared<Lock>();
    lock16->setPosition(433.5f,336.5f);
    lock16->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock16);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock17 = std::make_shared<Lock>();
    lock17->setPosition(433.5f,189.0f);
    lock17->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock17);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock18 = std::make_shared<Lock>();
    lock18->setPosition(433.5f,146.0f);
    lock18->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock18);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock19 = std::make_shared<Lock>();
    lock19->setPosition(433.5f,93.0f);
    lock19->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock19);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock20 = std::make_shared<Lock>();
    lock20->setPosition(433.5f,48.0f);
    lock20->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock20);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock21 = std::make_shared<Lock>();
    lock21->setPosition(481.0f,248.0f);
    lock21->setLockType(LockType::Vertical);
    lock_objects.push_back(lock21);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock22 = std::make_shared<Lock>();
    lock22->setPosition(524.0f,248.0f);
    lock22->setLockType(LockType::Vertical);
    lock_objects.push_back(lock22);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock23 = std::make_shared<Lock>();
    lock23->setPosition(2.5f,248.0f);
    lock23->setLockType(LockType::Vertical);
    lock_objects.push_back(lock23);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock24 = std::make_shared<Lock>();
    lock24->setPosition(45.0f,248.0f);
    lock24->setLockType(LockType::Vertical);
    lock_objects.push_back(lock24);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock25 = std::make_shared<Lock>();
    lock25->setPosition(145.0f,56.5f);
    lock25->setLockType(LockType::Vertical);
    lock_objects.push_back(lock25);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock26 = std::make_shared<Lock>();
    lock26->setPosition(381.0f,54.5f);
    lock26->setLockType(LockType::Vertical);
    lock_objects.push_back(lock26);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock27 = std::make_shared<Lock>();
    lock27->setPosition(247.0f,51.0f);
    lock27->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock27);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock28 = std::make_shared<Lock>();
    lock28->setPosition(247.0f,147.0f);
    lock28->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock28);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock29 = std::make_shared<Lock>();
    lock29->setPosition(152.0f,338.0f);
    lock29->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock29);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock30 = std::make_shared<Lock>();
    lock30->setPosition(337.0f,338.0f);
    lock30->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock30);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock31 = std::make_shared<Lock>();
    lock31->setPosition(337.0f,477.0f);
    lock31->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock31);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock32 = std::make_shared<Lock>();
    lock32->setPosition(152.5f,477.0f);
    lock32->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock32);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock33 = std::make_shared<Lock>();
    lock33->setPosition(247.0f,477.0f);
    lock33->setLockType(LockType::Horizontal);
    lock_objects.push_back(lock33);
    lock_textures.push_back(HlockT);

    std::shared_ptr<Lock>lock34 = std::make_shared<Lock>();
    lock34->setPosition(237.0f,344.0f);
    lock34->setLockType(LockType::Vertical);
    lock_objects.push_back(lock34);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock35 = std::make_shared<Lock>();
    lock35->setPosition(289.0f,344.0f);
    lock35->setLockType(LockType::Vertical);
    lock_objects.push_back(lock35);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock36 = std::make_shared<Lock>();
    lock36->setPosition(385.0f,245.0f);
    lock36->setLockType(LockType::Vertical);
    lock_objects.push_back(lock36);
    lock_textures.push_back(VlockT);

    std::shared_ptr<Lock>lock37 = std::make_shared<Lock>();
    lock37->setPosition(428.0f,245.0f);
    lock37->setLockType(LockType::Vertical);
    lock_objects.push_back(lock37);
    lock_textures.push_back(VlockT);
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
    
    keyT ->Load("../resources/key.png");
    fruitT->Load("../resources/fruit.png");
    VlockT->Load("../resources/lockV.png");
    HlockT->Load("../resources/lockH.png");

    blueT->Load("../resources/blue1.png");
    redT->Load("../resources/red1.png");
    pinkT->Load("../resources/pink1.png");
    orangeT->Load("../resources/orange1.png");

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