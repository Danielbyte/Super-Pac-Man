#include "gameWorldResources.h"

GameWorldResources::GameWorldResources():
tileScreenPosX{0.0f},
tileScreenPosY{0.0f}
{
    loadTextures();
}

GameWorldResources::GameWorldResources(int tilePosX, int tilePosY)
{
    tileScreenPosX = tilePosX * 32.0f;
    tileScreenPosY = tilePosY * 32.0f;
    
    auto numberOfRows = game_world->getNumberOfRows();
    if (tilePosY == (numberOfRows - 1))//minus one since tile position start from zero
       tileScreenPosY += 24.0f;

    auto numberOfColumns = game_world->getNumberOfColumns();
    if((tilePosY > 0 && tilePosY != (numberOfRows - 1)) && tilePosX == (numberOfColumns - 1))
      tileScreenPosX += 24.0f;
}

void GameWorldResources::loadTextures()
{
}
std::tuple<float, float> GameWorldResources::getTileScreenPosition() const
{
    return {tileScreenPosX, tileScreenPosY};
}