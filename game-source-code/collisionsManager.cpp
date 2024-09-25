#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{27.0f},
playerLength{27.0f},
horizontalWallWidth{7.0f},
horizontalWallLength{48.0f},
verticalWallWidth{48.0f},
verticalWallLength{7.0f},
keyWidth{15.0f},
keyHeight{32.0f},
fruitWidth{10.0f},
fruitHeight{10.0f},
horizontalLockWidth{3.0f},
horizontalLockLength{40.0f},
verticalLockWidth{32.0f},
verticalLockLength{3.0f},
ghostWidth{30.0f},
ghostLength{30.0f}
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

void CollisionsManager::playerKeyCollisions(std::vector<std::shared_ptr<Key>>keys, const float xPlayerPos, const float yPlayerPos,
std::vector<std::shared_ptr<Lock>>& locks)
{
    auto key = keys.begin();
    int lockId1 = -100, lockId2 = -100, lockId3 = -100;
    while(key != keys.end())
    {
        auto[xPos, yPos] = (*key)->getPosition();
        auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,xPos,yPos,
        keyHeight, keyWidth);

        if (isCollided)
        {
            (*key)->markForDeletion();
            auto [lock1Id, lock2Id] = (*key)->getLockIdsToUnlock();

            if((*key)->isTripleOpener())
            {
                auto [lck1, lck2, lck3] = (*key)->getTripleLockIdsToUnlock();
                lockId1 = lck1;
                lockId2 = lck2;
                lockId3 = lck3;
            }
            for(auto& lock : locks)
            {
                auto lockId = lock->getLockId();
                if (lockId == lock1Id || lockId == lock2Id || lockId == lockId1 || lockId == lockId2 || lockId == lockId3)
                    lock->OpenLock();
            }
        }
        ++key;
    }
}

void CollisionsManager::playerFruitCollisions(std::vector<std::shared_ptr<Fruit>>fruit_objects, const float xPlayerPos, const float yPlayerPos,
bool& isSuperPacman)
{
    auto fruit = fruit_objects.begin();
    while(fruit != fruit_objects.end())
    {
        auto [xPos, yPos] = (*fruit)->getPosition();
        auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,xPos,yPos,fruitWidth,fruitHeight);
        if(isCollided)
        {
            auto isSuperPellet = (*fruit)->getIsSuperPellet();
            if (isSuperPellet && !isSuperPacman)
                isSuperPacman = true;

            (*fruit)->markForDeletion();
        }

        ++fruit;
    }
}

bool CollisionsManager::lockCollisions(std::vector<std::shared_ptr<Lock>>& lock_objects, const float xPlayerPos, const float yPlayerPos)
{
    auto lock = lock_objects.begin();
    while(lock != lock_objects.end())
    {
        auto lockWidth = 0.0f;
        auto lockLength = 0.0f;
        auto lockType = (*lock)->getLockType();
        switch (lockType)
        {
        case LockType::Vertical:
            lockWidth = verticalLockWidth;
            lockLength = verticalLockLength;
            break;
        case LockType::Horizontal:
             lockWidth = horizontalLockWidth;
             lockLength = horizontalLockLength;
             break;
        default:
            break;
        }
        auto [xPos, yPos] = (*lock)->getPosition();
        auto isCollided = collision->checkCollision(xPlayerPos, yPlayerPos, playerWidth, playerLength,
        xPos, yPos, lockWidth, lockLength);

        if (isCollided)
           return true;
        ++lock;
    }

    return false;
}

bool CollisionsManager::ghostWallCollisions(std::vector<std::shared_ptr<GameWorldResources>>& maze, const float ghostXpos, const float ghostYpos)
{
    auto maze_tile = maze.begin();
    while(maze_tile != maze.end())
    {
        auto tile_type = (*maze_tile)->getObjectType();
        auto [tileXpos, tileYpos] = (*maze_tile)->getTileScreenPosition();
        if (tile_type == ObjectType::HorizontalWall)
        {
            auto isCollided = collision->checkCollision(ghostXpos,ghostYpos,ghostWidth,ghostLength,tileXpos,tileYpos,
             horizontalWallWidth, horizontalWallLength);
            if (isCollided)
            {
                return true;
            }
               
        }

        if (tile_type == ObjectType::VerticalWall)
        {
            auto isCollided = collision->checkCollision(ghostXpos,ghostYpos,ghostWidth,ghostLength,tileXpos,tileYpos,
             horizontalWallWidth, horizontalWallLength);
             
            if (isCollided)
            {
                return true;
            }
            
        }
        ++maze_tile;
    }
    return false;
}