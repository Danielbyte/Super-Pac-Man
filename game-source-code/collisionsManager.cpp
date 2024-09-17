#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{29.0f},
playerLength{29.0f},
horizontalWallWidth{7.0f},
horizontalWallLength{48.0f},
verticalWallWidth{48.0f},
verticalWallLength{7.0f},
keyWidth{15.0f},
keyHeight{32.0f}
{}

bool CollisionsManager::playerWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze,
 const float xPlayerPos, const float yPlayerPos)
{
    auto maze_tile = maze.begin();
    while(maze_tile != maze.end())
    {
        auto tile_type = (*maze_tile)->getObjectType();
        auto [tileXpos, tileYpos] = (*maze_tile)->getTileScreenPosition();
        if (tile_type == ObjectType::HorizontalWall)
        {
            auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,tileXpos,tileYpos,
             horizontalWallWidth, horizontalWallLength);
            if (isCollided)
               return true;
        }

        if (tile_type == ObjectType::VerticalWall)
        {
            auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,tileXpos,tileYpos,
             verticalWallWidth, verticalWallLength);
            if (isCollided)
            return true;
        }
        ++maze_tile;
    }
    return false;
}

void CollisionsManager::playerKeyCollisions(std::vector<std::shared_ptr<Key>>keys, const float xPlayerPos, const float yPlayerPos)
{
    auto key = keys.begin();
    while(key != keys.end())
    {
        auto[xPos, yPos] = (*key)->getPosition();
        auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,xPos,yPos,
        keyHeight, keyWidth);

        if (isCollided)
        {
            (*key)->markForDeletion();
        }
        ++key;
    }
}