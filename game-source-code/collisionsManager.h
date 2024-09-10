#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H
#include "collisions.h"
#include "gameWorldResources.h"

#include <memory>

class CollisionsManager
{
private:
    float playerWidth, playerLength;
    float horizontalWallWidth, horizontalWallLength;
    float verticalWallWidth, verticalWallLength;
public:
    CollisionsManager();
    bool playerWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze,const float xPlayerPos, const float yPlayerPos);
    std::unique_ptr<Collisions>collision = std::make_unique<Collisions>();
};
#endif
