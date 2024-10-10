#include "gameWorldResources.h"

GameWorldResources::GameWorldResources():
tileScreenPosX{0.0f},
tileScreenPosY{0.0f}
{
}

GameWorldResources::GameWorldResources(int tilePosX, int tilePosY, const ObjectType _type,
 const float xOffset, const float yOffset)
{
    tileScreenPosX = (tilePosX + xOffset) * 48.0f;
    tileScreenPosY = (tilePosY + yOffset) * 48.0f;
    type = _type;
}

void GameWorldResources::initialiseGameBorder(int tilePosX, int tilePosY, const ObjectType _type)
{
    tileScreenPosX = tilePosX * 32.0f;
    tileScreenPosY = tilePosY * 32.0f;
    
    auto numberOfRows = game_world.getNumberOfRows();
    auto numberOfColumns = game_world.getNumberOfColumns();
    if (tilePosY == (numberOfRows - 1) && (tilePosX > 0 && tilePosX < (numberOfColumns - 1)))//minus one since tile position start from zero
       tileScreenPosY += 24.0f;
    
    if((tilePosY > 0 && tilePosY != (numberOfRows - 1)) && (tilePosX == (numberOfColumns - 1) || tilePosX != 0))
      tileScreenPosX += 24.0f;

    type = _type;
}

void GameWorldResources::setMazeWalls(std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures,
std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
    auto maze = game_world.getGameMap();
    int tilePosY = 0;
    int tilePosX = 0;
    for (const auto& row : maze)
    {
        for (const auto tile : row)
        {
            processTileTexture(maze_textures,maze_resources,tile, tilePosX, tilePosY);
            tilePosX++;
        }
        tilePosY++;
        tilePosX = 0;
    }
}

void GameWorldResources::processTileTexture(std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures,
std::vector<std::shared_ptr<GameWorldResources>>& maze_resources,const std::string element,const int tilePosX,const int tilePosY)
{
    float xOffset = 0;
    float yOffset = 0;
    if (element == "10") //Vertical wall on the left
    {
        xOffset = 0;
        yOffset = 0;
        verticalWall(tilePosX, tilePosY, xOffset, yOffset,maze_textures,maze_resources);
    }

    if (element == "01")//Vertical wall on the right
    {
        xOffset = (5/6.0f);//This vertical wall should be at the border of the maze
        yOffset = 0;
        verticalWall(tilePosX, tilePosY, xOffset, yOffset, maze_textures,maze_resources);
    }

    if (element == "-")
    {
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "┐")
    {
        xOffset = 0;
        yOffset = 0;
        topRightCorner(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "┌")
    {
        xOffset = 0;
        yOffset = 0;
        topLeftCorner(tilePosX,tilePosY,xOffset,yOffset, maze_textures,maze_resources);
    }

    if (element == "└")
    {
        xOffset = 0;
        yOffset = 0;
        bottomLeftCorner(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

        if (element == "┘")
    {
        xOffset = 0;
        yOffset = 0;
        bottomRightCorner(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "_")
    {
        //Bottom horizontal
        xOffset = 0;
        yOffset = 5/6.0f;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "=")
    {
        //Parallel horizontal
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
        yOffset = 5/6.0f;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "||")
    {
        //Parallel vertical
        xOffset = 0;
        yOffset = 0;
        verticalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
        xOffset = 5/6.0f;
        verticalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "Π")
    {
        //As the symbol suggests, you welcome
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures, maze_resources);
        verticalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
        xOffset = 5/6.0f;//the far right wall
        verticalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }
}

void GameWorldResources::topRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
    horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    auto newXoffset = 5/6.0f;//place vertical piece at the end of the horizontal piece to form ┐
    verticalWall(tilePosX,tilePosY,newXoffset,yOffset,maze_textures,maze_resources);
}

void GameWorldResources::topLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
    horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    verticalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
}

void GameWorldResources::bottomLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
    verticalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    auto newYoffset = 5/6.0f;
    horizontalWall(tilePosX,tilePosY,xOffset,newYoffset, maze_textures,maze_resources);
}

void GameWorldResources::bottomRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
    auto newYoffset = 5/6.0f;
    horizontalWall(tilePosX,tilePosY,xOffset,newYoffset,maze_textures,maze_resources);
    auto newXoffset = 5/6.0f;
    verticalWall(tilePosX,tilePosY,newXoffset,yOffset, maze_textures,maze_resources);
}

void GameWorldResources::verticalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/verticalWallPiece.png");
  maze_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall,xOffset,yOffset);
  maze_resources.push_back(tile_property);
}


void GameWorldResources::horizontalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  maze_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall,xOffset,yOffset);
  maze_resources.push_back(tile_property);
}

void GameWorldResources::loadFruitTextures(std::vector<std::shared_ptr<Fruit>>& fruits, std::vector<std::shared_ptr<raylib::Texture2D>>& fruit_textures)
{
    auto fruit = fruits.begin();
    auto fruitT = std::make_shared<raylib::Texture2D>();
    fruitT->Load("../resources/fruit.png");
    auto superPelletT = std::make_shared<raylib::Texture2D>();
    superPelletT->Load("../resources/superPellet1.png");
    auto powerPellet = std::make_shared<raylib::Texture2D>();
    powerPellet->Load("../resources/powerPellet.png");

    while (fruit != fruits.end())
    {
        auto isSuperPellet = (*fruit)->getIsSuperPellet();
        auto isPowerPellet = (*fruit)->getIsPowerPellet();
        
        if(isSuperPellet)
        {
            fruit_textures.push_back(superPelletT);
        }

        else if(isPowerPellet)
        {
            fruit_textures.push_back(powerPellet);
        }

        else
        {
            fruit_textures.push_back(fruitT);
        }
        ++fruit;
    }  
}

void GameWorldResources::loadKeyTextures(std::vector<std::shared_ptr<Key>>& keys, std::vector<std::shared_ptr<raylib::Texture2D>>& key_textures)
{
    auto keyT = std::make_shared<raylib::Texture2D>();
    keyT->Load("../resources/key.png");

    for(auto& key : keys)
       key_textures.push_back(keyT);
}

void GameWorldResources::loadLockTextures(std::vector<std::shared_ptr<Lock>>& locks, std::vector<std::shared_ptr<raylib::Texture2D>>& lock_textures)
{
    auto VlockT = std::make_shared<raylib::Texture2D>();
    VlockT->Load("../resources/lockV.png");
    auto HlockT = std::make_shared<raylib::Texture2D>();
    HlockT->Load("../resources/lockH.png");

    for(auto& lock : locks)
    {
        auto lockType = lock->getLockType();
        switch (lockType)
        {
        case LockType::Vertical:
            lock_textures.push_back(VlockT);
            break;
        case LockType::Horizontal:
             lock_textures.push_back(HlockT);
             break;
        default:
            break;
        }
    }
}

std::tuple<float, float> GameWorldResources::getTileScreenPosition() const
{
    return {tileScreenPosX, tileScreenPosY};
}

ObjectType GameWorldResources::getObjectType() const
{
    return type;
}

std::shared_ptr<raylib::Texture2D> GameWorldResources::getReferenceSymbolTexture(std::shared_ptr<GameWorld> game_world)
{
    switch ((game_world->getReferenceSymbol()))
    {
    case SymbolType::Fruit:
        return fruit;
        break;
    case SymbolType::Burger:
         return burger;
         break;
    case SymbolType::Cake:
         return cake;
         break;
    case SymbolType::Donut:
         return donut;
         break;
    case SymbolType::Key:
         return key;
         break;
    case SymbolType::Shoe:
         return shoe;
         break;
    case SymbolType::Unknown:
         return unknown;
         break;
    default:
        break;
    }
    return unknown;
}

std::shared_ptr<raylib::Texture2D> GameWorldResources::getFlashingSymbolTexture(std::shared_ptr<GameWorld> game_world)
{
    switch ((game_world->getFlashingSymbol()))
    {
    case SymbolType::Fruit:
        return fruit;
        break;
    case SymbolType::Burger:
         return burger;
         break;
    case SymbolType::Cake:
         return cake;
         break;
    case SymbolType::Donut:
         return donut;
         break;
    case SymbolType::Key:
         return key;
         break;
    case SymbolType::Shoe:
         return shoe;
         break;
    case SymbolType::Unknown:
         return unknown;
         break;
    default:
        break;
    }
    return unknown;
}

void GameWorldResources::loadFlashingSymbolsTextures()
{
    shoe->Load("../resources/shoe.png");
    donut->Load("../resources/donut.png");
    cake->Load("../resources/cake.png");
    fruit->Load("../resources/fruit.png");
    key->Load("../resources/key.png");
    burger->Load("../resources/burger.png");
    unknown->Load("../resources/unknown.png");
}