#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H
#include "collisions.h"
#include "gameWorldResources.h"
#include "player.h"

#include <memory>

class CollisionsManager
{
private:
    float playerWidth, playerLength;
    float horizontalWallWidth, horizontalWallLength;
    float verticalWallWidth, verticalWallLength;
public:
    CollisionsManager();
    void playerWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze, std::shared_ptr<Player>& player);
};
#endif
