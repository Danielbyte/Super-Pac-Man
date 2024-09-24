#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H
#include "collisions.h"
#include "gameWorldResources.h"
#include "key.h"
#include "fruit.h"
#include "lock.h"

#include <memory>

class CollisionsManager
{
private:
    float playerWidth, playerLength;
    float horizontalWallWidth, horizontalWallLength;
    float verticalWallWidth, verticalWallLength;
    float keyWidth, keyHeight;
    float fruitWidth, fruitHeight;
    float horizontalLockWidth, horizontalLockLength;
    float verticalLockWidth, verticalLockLength;
    float ghostWidth, ghostLength;
public:
    CollisionsManager();
    bool playerWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze,const float xPlayerPos, const float yPlayerPos);
    std::unique_ptr<Collisions>collision = std::make_unique<Collisions>();
    void playerKeyCollisions(std::vector<std::shared_ptr<Key>>key_objects,const float xPlayerPos, const float yPlayerPos);
    void playerFruitCollisions(std::vector<std::shared_ptr<Fruit>>fruit_objects, const float xPlayerPos, const float yPlayerPos);
    bool lockCollisions(std::vector<std::shared_ptr<Lock>>& lock_objects, const float xPlayerPos, const float yPlayerPos);
    bool ghostWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze, const float ghostXpos, const float ghostYpos);
};
#endif
