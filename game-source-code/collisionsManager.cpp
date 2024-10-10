#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{25.0f},
playerLength{25.0f},
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
std::vector<std::shared_ptr<Lock>>& locks, ScoreManager& score_manager)
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
            score_manager.updateCurrentScore(ScoreType::Key);

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
bool& isSuperPacman, bool& atePowerPellet, ScoreManager& score_manager, std::shared_ptr<GameWorld>& game_world)
{
    auto fruit = fruit_objects.begin();
    while(fruit != fruit_objects.end())
    {
        auto [xPos, yPos] = (*fruit)->getPosition();
        auto scoreUpdated = false;
        auto isCollided = collision->checkCollision(xPlayerPos,yPlayerPos,playerWidth,playerLength,xPos,yPos,fruitWidth,fruitHeight);
        if(isCollided)
        {
            auto isSuperPellet = (*fruit)->getIsSuperPellet();
            if (isSuperPellet && !isSuperPacman)
                isSuperPacman = true;

            if (isSuperPellet)
            {
                score_manager.updateCurrentScore(ScoreType::SuperPellet);
                scoreUpdated = true;
            }

            auto isPowerPellet = (*fruit)->getIsPowerPellet();
            if(isPowerPellet)
            {
                atePowerPellet = true;
                score_manager.updateCurrentScore(ScoreType::PowerPellet);
                scoreUpdated = true;
            }
            
            auto isStar = (*fruit)->getIsStar();
            if (isStar)
            {
                auto [no_match, other_match, maze_symbol_match] = game_world->symbolMatches();
                if(no_match)
                  score_manager.updateCurrentScore(ScoreType::Star);

                if (other_match)
                   score_manager.updateCurrentScore(ScoreType::OtherMatchBonus);
                
                if (maze_symbol_match)
                    score_manager.updateCurrentScore(ScoreType::MazeMatchBonus);

                scoreUpdated = true;
            }

            //Update score if it is a normal fruit
            if (!scoreUpdated)
                score_manager.updateCurrentScore(ScoreType::Fruit);

            (*fruit)->markForDeletion();
        }

        ++fruit;
    }
}

bool CollisionsManager::lockCollisions(std::vector<std::shared_ptr<Lock>>& lock_objects, const float xPlayerPos, const float yPlayerPos,
bool inSupePacmanMode)
{
    auto lock = lock_objects.begin();
    auto lockWidth = 0.0f;
    auto lockLength = 0.0f;
    while(lock != lock_objects.end())
    {
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

        if (isCollided && inSupePacmanMode)
            (*lock)->OpenLock();

        if (isCollided && !inSupePacmanMode)
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

bool CollisionsManager::playerGhostCollisions(const float xGhostPos, const float yGhostPos, const float xPlayerPos, const float yPlayerPos)
{
    return(collision->checkCollision(xGhostPos,yGhostPos,ghostWidth,ghostLength,xPlayerPos,yPlayerPos,playerWidth,playerLength));
}

bool CollisionsManager::ghostLockCollisions(std::vector<std::shared_ptr<Lock>>& lock_objects, const float xGhostPos, const float yGhostPos, bool canUseDoor)
{
    auto lock = lock_objects.begin();
    auto lockWidth = 0.0f;
    auto lockLength = 0.0f;
    while(lock != lock_objects.end())
    {
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
        auto isGhostHouseLock = (*lock)->getIsGhostLock();
        auto isCollided = collision->checkCollision(xGhostPos, yGhostPos, ghostWidth, ghostLength,
        xPos, yPos, lockWidth, lockLength);

        if (isCollided && isGhostHouseLock && canUseDoor)
           return false;

        if (isCollided)
            return true;
            
        ++lock;
    }

    return false;
}