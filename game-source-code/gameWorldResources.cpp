#include "gameWorldResources.h"

GameWorldResources::GameWorldResources():
tileScreenPosX{0.0f},
tileScreenPosY{0.0f}
{
    loadTextures();
}

GameWorldResources::GameWorldResources(int tilePosX, int tilePosY)
{
    tileScreenPosX = tilePosX * 16.0f;
    tileScreenPosY = tilePosY * 16.0f;
}

void GameWorldResources::loadTextures()
{
}
std::tuple<float, float> GameWorldResources::getTileScreenPosition() const
{
    return {tileScreenPosX, tileScreenPosY};
}