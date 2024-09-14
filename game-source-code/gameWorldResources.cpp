#include "gameWorldResources.h"

GameWorldResources::GameWorldResources():
tileScreenPosX{0.0f},
tileScreenPosY{0.0f}
{
    loadTextures();
}

GameWorldResources::GameWorldResources(int tilePosX, int tilePosY, const ObjectType _type)
{
    tileScreenPosX = tilePosX * 22.52f;
    tileScreenPosY = tilePosY * 22.52f;
    
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
std::tuple<float, float> GameWorldResources::getTileScreenPosition() const
{
    return {tileScreenPosX, tileScreenPosY};
}

ObjectType GameWorldResources::getObjectType() const
{
    return type;
}