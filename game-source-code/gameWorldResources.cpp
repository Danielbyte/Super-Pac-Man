#include "gameWorldResources.h"

GameWorldResources::GameWorldResources():
tileScreenPosX{0.0f},
tileScreenPosY{0.0f}
{
    loadTextures();
}

GameWorldResources::GameWorldResources(int tilePosX, int tilePosY, const ObjectType _type)
{
    tileScreenPosX = tilePosX * 32.0f;
    tileScreenPosY = tilePosY * 32.0f;
    
    auto numberOfRows = game_world->getNumberOfRows();
    auto numberOfColumns = game_world->getNumberOfColumns();
    if (tilePosY == (numberOfRows - 1) && (tilePosX > 0 && tilePosX < (numberOfColumns - 1)))//minus one since tile position start from zero
       tileScreenPosY += 24.0f;
    
    if((tilePosY > 0 && tilePosY != (numberOfRows - 1)) && (tilePosX == (numberOfColumns - 1) || tilePosX != 0))
      tileScreenPosX += 24.0f;

    type = _type;
}

void GameWorldResources::loadTextures()
{
}

void GameWorldResources::InitGameWorldTextures()
{
    auto game_maze = game_world->getGameMap();
    int tilePosY = 0;
    int tilePosX = 0;
    for (const auto& row : game_maze)
    {
        for (char cell : row)
        {
            processTileTexture(cell, tilePosX, tilePosY);
            tilePosX++;
        }
        tilePosY++;
        tilePosX = 0;
    }
}

void GameWorldResources::processTileTexture(const char element, int tilePosX, int tilePosY)
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

void GameWorldResources::setWallProperties(int tilePosX, int tilePosY)
{  
    auto texture = std::make_shared<raylib::Texture2D>();
    auto maxCol = game_world->getNumberOfColumns();

    if ((tilePosX == 0 || tilePosX == (maxCol-1)) && (tilePosY >= 1 && tilePosY < ((game_world->getGameMap().size())-1)))
    {
        texture->Load("../resources/verticalWallPiece.png"); 
        auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall);
        maze_resources.push_back(tile_property);
    }
        
    else if (tilePosY == 0 || tilePosY == ((game_world->getGameMap().size())-1))
    {
        texture->Load("../resources/horizontalWallPiece.png");
        auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall);
        maze_resources.push_back(tile_property);
    }     
    game_world_textures.push_back(texture);
}

std::tuple<float, float> GameWorldResources::getTileScreenPosition() const
{
    return {tileScreenPosX, tileScreenPosY};
}

ObjectType GameWorldResources::getObjectType() const
{
    return type;
}