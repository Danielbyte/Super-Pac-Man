#include "ghost.h"

Ghost::Ghost():
ghostSpeed{60.0f},
currentDirection{Direction::Still},
integralDistance{0.0f},
isInitial{true},
justSpawned{false},
canUseDoor{true}
{}

Type Ghost::getType() const
{
    return type;
}

void Ghost::setType(Type _type)
{
    type = _type;
}

void Ghost::updateTarget(const float x, const float y)
{
    xTargetPos = x;
    yTargetPos = y;
    targetTileX = static_cast<int>(xTargetPos/48);
    targetTileY = static_cast<int>(yTargetPos/48);
}

void Ghost::assignCorner(const float x, const float y)
{
    targetCornePosX = x;
    targetCornerPosY = y;
}

Mode Ghost::getMode() const
{
    return mode;
}

void Ghost::moveToCorner()
{
    //set target to target corner
    xTargetPos = targetCornePosX;
    yTargetPos = targetCornerPosY;
    targetTileX = static_cast<int>(xTargetPos/48);
    targetTileY = static_cast<int>(yTargetPos/48);
}

void Ghost::setMode(Mode _mode)
{
    mode = _mode;
}

void Ghost::update(std::vector<std::shared_ptr<GameWorldResources>>& maze,std::vector<std::shared_ptr<Lock>>& locks,
 const float dt)
{
    updatePosition(locks, dt);
}

float Ghost::calculateLinearDistance()
{
    return sqrt(pow(xPosition-xTargetPos,2)+(pow(yPosition-yTargetPos,2)));
}

Direction Ghost::getOptimalDirection(std::vector<std::shared_ptr<Lock>>& locks, const float dt)
{
    Direction bestDir = Direction::Still;
    auto minDistance = calculateLinearDistance();//The straight line distance will give min distance between ghost and target
    std::vector<Direction>directions = {Direction::Left,Direction::Up,Direction::Right, Direction::Down};
    auto isValid = false;
    int TileCol = static_cast<int>(xPosition/48);
    int TileRow = static_cast<int>(yPosition/48);
    for(auto nextDir : directions)
    {
        if (isOppositeDirection(nextDir, currentDirection))
            continue;//Skip this direction if it will result to ghost reversing
        
        getIsValidMove(nextDir, TileRow, TileCol, isValid, locks);
        
        if(isValid)//A valid move if ghost does not collide with wall (should probably use tile-based collisions)
        {
            auto[nextTileX, nextTileY] = getNextTile(nextDir);
            auto newDist = sqrt(pow(nextTileX-targetTileX,2)+(pow(nextTileY-targetTileY,2)));
            if (newDist < minDistance)
            {
                minDistance = newDist;
                bestDir = nextDir;
            }
            isValid = false;
        }
    }

    if (bestDir == Direction::Still)
    {
        bestDir = priorityDirection(locks);
    }
    currentDirection = bestDir;
    return bestDir;
}

void Ghost::getIsValidMove(Direction _direction, int tileRow, const int tileColumn, bool& isValid,
std::vector<std::shared_ptr<Lock>>& locks)
{    
    //Check for locked sections
    auto [xPos, yPos] = getPosition();
    auto Offset = 12.0f;   
    switch (_direction)
    {
        case Direction::Up:
        if (tileRow > 0 && (gameMap[tileRow][tileColumn] != "-" && gameMap[tileRow][tileColumn] != "="
        && gameMap[tileRow][tileColumn] != "┌" && gameMap[tileRow][tileColumn] != "Π" && gameMap[tileRow][tileColumn] != "┐"))
        {
            if (gameMap[tileRow-1][tileColumn] == "0" || (gameMap[tileRow-1][tileColumn] == "-" || gameMap[tileRow][tileColumn] == "-")
                || gameMap[tileRow-1][tileColumn] == "01" || gameMap[tileRow-1][tileColumn] == "10"
                || gameMap[tileRow-1][tileColumn] == "||"|| gameMap[tileRow-1][tileColumn] == "Π"){isValid = true;}

            yPos -= Offset;
            auto isCollided = collision_manager.ghostLockCollisions(locks,xPos,yPos);
            if (isCollided)
                isValid = false;
        }
        else
        {
            isValid = false;
        }
        break;
        case Direction::Down:
            if ((tileRow + 1) < 12 && (gameMap[tileRow][tileColumn] != "_" && gameMap[tileRow][tileColumn] != "└"
            && gameMap[tileRow][tileColumn] != "┘" && gameMap[tileRow][tileColumn] != "="))
            {
                if (gameMap[tileRow + 1][tileColumn] == "0" || gameMap[tileRow + 1][tileColumn] == "_"
                || gameMap[tileRow + 1][tileColumn] == "┘"
                || gameMap[tileRow + 1][tileColumn] == "└"
                || gameMap[tileRow + 1][tileColumn] == "01" || gameMap[tileRow + 1][tileColumn] == "10"
                || gameMap[tileRow+1][tileColumn] == "||"){isValid = true;}

                yPos += Offset;
                auto isCollided = collision_manager.ghostLockCollisions(locks,xPos,yPos);
                if(isCollided)
                   isValid = false;
            }
            else
            {
               isValid = false;
            }
        break;
        
        case Direction::Right:
            if ((tileColumn+1) < 11 && (gameMap[tileRow][tileColumn] != "┘" && gameMap[tileRow][tileColumn] != "┐"
            && gameMap[tileRow][tileColumn] != "01" && gameMap[tileRow][tileColumn] != "||" && gameMap[tileRow][tileColumn] != "Π"))
            {
                if (gameMap[tileRow][tileColumn+1] == "0" || gameMap[tileRow][tileColumn+1] == "01"
                || gameMap[tileRow][tileColumn+1] == "-" || gameMap[tileRow][tileColumn+1] == "┐"
                || gameMap[tileRow][tileColumn+1] == "┘" || gameMap[tileRow][tileColumn+1] == "_" 
                || gameMap[tileRow][tileColumn+1] == "="){isValid = true;}

                xPos += Offset;
                auto isCollided = collision_manager.ghostLockCollisions(locks,xPos,yPos);

                if (isCollided)
                   isValid = false;
            }
            else
            {
                isValid = false;
            }
        break;

        case Direction::Left:
            if ((tileColumn-1) >= 0 && (gameMap[tileRow][tileColumn] != "||" && gameMap[tileRow][tileColumn] != "10"
            && gameMap[tileRow][tileColumn] != "└" && gameMap[tileRow][tileColumn] != "┌" && gameMap[tileRow][tileColumn] != "Π"))
            {
                if (gameMap[tileRow][tileColumn-1] == "0"
                || gameMap[tileRow][tileColumn-1] == "10" || gameMap[tileRow][tileColumn-1] == "_"
                || gameMap[tileRow][tileColumn-1] == "-" || gameMap[tileRow][tileColumn-1] == "="
                || gameMap[tileRow][tileColumn-1] == "┌"
                || gameMap[tileRow][tileColumn-1] == "└"){isValid = true;}

                xPos -= Offset;
                auto isCollided = collision_manager.ghostLockCollisions(locks,xPos,yPos);
                if (isCollided)
                    isValid = false;

            }
            else
            {
                isValid = false;
            }
             break;

        default:
        break;
    }
}

Direction Ghost::priorityDirection(std::vector<std::shared_ptr<Lock>>& locks)
{
    Direction priorityDir = Direction::Still;
    auto isValid = false;
    int TileCol = static_cast<int>(xPosition/48);
    int TileRow = static_cast<int>(yPosition/48);
    std::vector<Direction>directions = {Direction::Up,Direction::Left,Direction::Down, Direction::Right};//Store according to their priority
    for(auto dir : directions)
    {
        if (isOppositeDirection(dir, currentDirection))
            continue;//Skip this direction if it will result to ghost reversing 

        getIsValidMove(dir, TileRow, TileCol, isValid, locks);
        if (isValid)
        {
            priorityDir = dir;
            break; 
        }      
    }
    return priorityDir;
}

bool Ghost::isOppositeDirection(Direction nextDir, Direction previousDir)
{
    return ((nextDir == Direction::Up && previousDir == Direction::Down) ||(nextDir == Direction::Down && previousDir == Direction::Up)
    ||(nextDir == Direction::Left && previousDir == Direction::Right) || (nextDir == Direction::Right && previousDir == Direction::Left));
}

std::tuple<float,float> Ghost::getNextPosition(Direction dir, const float dt)
{
    auto[newXpos, newYpos] = getPosition();//Get currentt position

    switch (dir)
    {
    case Direction::Up:
           newYpos -= ghostSpeed*dt;
        break;
    case Direction::Down:
        newYpos += ghostSpeed*dt;
    break;
    case Direction::Left:
        newXpos -= ghostSpeed*dt;
    break;
    case Direction::Right:
        newXpos += ghostSpeed*dt; 
    break;
    default:
        break;
    }
    return {newXpos, newYpos};
}
std::tuple<int,int> Ghost::getNextTile(Direction dir)
{
    auto[newXpos, newYpos] = getPosition();//Get currentt position
    int tileX = static_cast<int>(newXpos/48);
    int tileY = static_cast<int>(newYpos/48);

    switch (dir)
    {
    case Direction::Up:
           tileY -= 1;
        break;
    case Direction::Down:
        tileY += 1;
    break;
    case Direction::Left:
        tileX -= 1;
    break;
    case Direction::Right:
        tileX += 1; 
    break;
    default:
        break;
    }
    return {tileX, tileY};
}

void Ghost::updatePosition(std::vector<std::shared_ptr<Lock>>& locks, const float dt)
{
    //auto[nextX, nextY] = getNextPosition(dir, dt);
    integralDistance += ghostSpeed * dt;
    float nextX, nextY;
    auto isUpdated = false;
    if (currentDirection == Direction::Still)
    {
        auto bestDirection = getOptimalDirection(locks,dt);
        auto [_nextX, _nextY] = getNextPosition(bestDirection, dt);
        nextX = _nextX;
        nextY = _nextY;
        currentDirection = bestDirection;
        isUpdated = true;
    }

    if (integralDistance >= 48.0f || isInitial)
    {
        int x = static_cast<int>(xPosition/48);
        int y = static_cast<int>(yPosition/48);
        nextX = x * 48.0f + 9.0f;
        nextY = y * 48.0f + 9.0f;
        integralDistance = 0.0f;

        auto bestDirection = getOptimalDirection(locks, dt);
        currentDirection = bestDirection;
        auto [_nextX, _nextY] = getNextPosition(bestDirection, dt);
        nextX = _nextX;
        nextY = _nextY;
        isUpdated = true;
        isInitial = false;
    }
    if(!isUpdated)
    {
       auto [_nextX, _nextY] = getNextPosition(currentDirection, dt);
       nextX = _nextX;
       nextY = _nextY;
    }

    setPosition(nextX, nextY);
}

bool Ghost::isJustRespawned()
{
    auto time_elapsed = time_since_respawn.elapsedTime();
    if (time_elapsed < 5.0f)
        justSpawned = true;
    
    else
        justSpawned = false;

    return justSpawned;
}

void Ghost::respawn()
{
    time_since_respawn.restartTimer();
    mode = Mode::Scatter;
    setPosition(249.0f, 105.0f);
    currentDirection = Direction::Still;
    integralDistance = 0.0f;
    isInitial = true;
}

bool Ghost::getCanUseDoor() const
{
    return canUseDoor;
}

void Ghost::disableDoorUse()
{
    canUseDoor = false;
}

void Ghost::setToUseGhostDoor()
{
    canUseDoor = true;
}