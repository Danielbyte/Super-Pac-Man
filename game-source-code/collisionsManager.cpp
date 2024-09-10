#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{32.0f},
playerLength{32.0f},
horizontalWallWidth{8.0f},
horizontalWallLength{32.0f},
verticalWallWidth{32.0f},
verticalWallLength{8.0f}
{}

void CollisionsManager::playerWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze,
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
            std::cout << "Collided" << std::endl;
        }

        if (tile_type == ObjectType::VerticalWall)
        {
            auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,tileXpos,tileYpos,
             verticalWallWidth, verticalWallLength);
            if (isCollided)
            std::cout << "Collided" << std::endl;
        }
        ++maze_tile;
    }
}