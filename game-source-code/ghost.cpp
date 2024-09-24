#include "ghost.h"

Ghost::Ghost():
xPosition{-100.0f},
yPosition{-100.0f},
ghostSpeed{60.0f},
currentDirection{GDirection::Still},
integralDistance{0.0f},
isInitial{true}
{}

std::tuple<float, float>Ghost::getPosition() const
{
    return {xPosition, yPosition};
}

void Ghost::setPosition(const float xPos, const float yPos)
{
    xPosition = xPos;
    yPosition = yPos;
}

Type Ghost::getType() const
{
    return type;
}

void Ghost::setType(Type _type)
{
    gameMap = game_world.getGameMap();
    type = _type;
}

void Ghost::updateTarget(const float x, const float y)
{
    xTargetPos = x;
    yTargetPos = y;
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
    if (mode != Mode::Frightened)
    {
       // auto dir = getOptimalDirection(maze, dt);
        updatePosition(locks, dt);
    }
}

float Ghost::calculateLinearDistance()
{
    return sqrt(pow(xPosition-xTargetPos,2)+(pow(yPosition-yTargetPos,2)));
}

GDirection Ghost::getOptimalDirection(std::vector<std::shared_ptr<Lock>>& locks, const float dt)
{
    GDirection bestDir = GDirection::Still;
    auto minDistance = calculateLinearDistance();//The straight line distance will give min distance between ghost and target
    std::vector<GDirection>directions = {GDirection::Left,GDirection::Up,GDirection::Right, GDirection::Down};
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

    if (bestDir == GDirection::Still)
    {
        bestDir = priorityDirection(locks);
    }
    currentDirection = bestDir;
    return bestDir;
}

void Ghost::getIsValidMove(GDirection _direction, int tileRow, const int tileColumn, bool& isValid,
std::vector<std::shared_ptr<Lock>>& locks)
{       
    switch (_direction)
    {
        case GDirection::Up:
        if (tileRow > 0 && (gameMap[tileRow][tileColumn] != "-" && gameMap[tileRow][tileColumn] != "="))
        {
          if (gameMap[tileRow-1][tileColumn] == "0" || (gameMap[tileRow-1][tileColumn] == "-" || gameMap[tileRow][tileColumn] == "-")
          || gameMap[tileRow-1][tileColumn] == "01" || gameMap[tileRow-1][tileColumn] == "10"
          || gameMap[tileRow-1][tileColumn] == "||"){isValid = true;}
        }
        else
        {
            isValid = false;
        }
        break;
        case GDirection::Down:
            if ((tileRow + 1) < 12 && (gameMap[tileRow][tileColumn] != "_" && gameMap[tileRow][tileColumn] != "└"
            && gameMap[tileRow][tileColumn] != "┘"))
            {
                if (gameMap[tileRow + 1][tileColumn] == "0" || gameMap[tileRow + 1][tileColumn] == "_"
                || gameMap[tileRow + 1][tileColumn] == "┘"
                || gameMap[tileRow + 1][tileColumn] == "└"
                || gameMap[tileRow + 1][tileColumn] == "01" || gameMap[tileRow + 1][tileColumn] == "10"
                || gameMap[tileRow+1][tileColumn] == "||"){isValid = true;}
            
            }
            else
            {
               isValid = false;
            }
        break;
        
        case GDirection::Right:
            if ((tileColumn+1) < 11 && (gameMap[tileRow][tileColumn] != "┘" && gameMap[tileRow][tileColumn] != "┐"
            && gameMap[tileRow][tileColumn] != "01" && gameMap[tileRow][tileColumn] != "||"))
            {
                if (gameMap[tileRow][tileColumn+1] == "0" || gameMap[tileRow][tileColumn+1] == "01"
                || gameMap[tileRow][tileColumn+1] == "-" || gameMap[tileRow][tileColumn+1] == "┐"
                || gameMap[tileRow][tileColumn+1] == "┘" || gameMap[tileRow][tileColumn+1] == "_" 
                || gameMap[tileRow][tileColumn+1] == "="){isValid = true;}
            }
            else
            {
                isValid = false;
            }
             break;

        case GDirection::Left:
            if ((tileColumn-1) >= 0 && (gameMap[tileRow][tileColumn] != "||" && gameMap[tileRow][tileColumn] != "10"
            && gameMap[tileRow][tileColumn] != "└" && gameMap[tileRow][tileColumn] != "┌"))
            {
                if (gameMap[tileRow][tileColumn-1] == "0"
                || gameMap[tileRow][tileColumn-1] == "10" || gameMap[tileRow][tileColumn-1] == "_"
                || gameMap[tileRow][tileColumn-1] == "-" || gameMap[tileRow][tileColumn] == "="
                || gameMap[tileRow][tileColumn-1] == "┌"
                || gameMap[tileRow][tileColumn-1] == "└"){isValid = true;}
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

GDirection Ghost::priorityDirection(std::vector<std::shared_ptr<Lock>>& locks)
{
    GDirection priorityDir = GDirection::Still;
    auto isValid = false;
    int TileCol = static_cast<int>(xPosition/48);
    int TileRow = static_cast<int>(yPosition/48);
    std::vector<GDirection>directions = {GDirection::Up,GDirection::Left,GDirection::Down, GDirection::Right};//Store according to their priority
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

bool Ghost::isOppositeDirection(GDirection nextDir, GDirection previousDir)
{
    return ((nextDir == GDirection::Up && previousDir == GDirection::Down) ||(nextDir == GDirection::Down && previousDir == GDirection::Up)
    ||(nextDir == GDirection::Left && previousDir == GDirection::Right) || (nextDir == GDirection::Right && previousDir == GDirection::Left));
}

std::tuple<float,float> Ghost::getNextPosition(GDirection dir, const float dt)
{
    auto[newXpos, newYpos] = getPosition();//Get currentt position

    switch (dir)
    {
    case GDirection::Up:
           newYpos -= ghostSpeed*dt;
        break;
    case GDirection::Down:
        newYpos += ghostSpeed*dt;
    break;
    case GDirection::Left:
        newXpos -= ghostSpeed*dt;
    break;
    case GDirection::Right:
        newXpos += ghostSpeed*dt; 
    break;
    default:
        break;
    }
    return {newXpos, newYpos};
}
std::tuple<int,int> Ghost::getNextTile(GDirection dir)
{
    auto[newXpos, newYpos] = getPosition();//Get currentt position
    int tileX = static_cast<int>(newXpos/48);
    int tileY = static_cast<int>(newYpos/48);

    switch (dir)
    {
    case GDirection::Up:
           tileY -= 1;
        break;
    case GDirection::Down:
        tileY += 1;
    break;
    case GDirection::Left:
        tileX -= 1;
    break;
    case GDirection::Right:
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
    if (currentDirection == GDirection::Still)
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