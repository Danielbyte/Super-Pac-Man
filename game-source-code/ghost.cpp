#include "ghost.h"

Ghost::Ghost():
xPosition{-100.0f},
yPosition{-100.0f},
ghostSpeed{90.0f},
prevDirection{GDirection::Still}
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
}

void Ghost::setMode(Mode _mode)
{
    mode = _mode;
}

void Ghost::update(std::vector<std::shared_ptr<GameWorldResources>>& maze, const float dt)
{
    if (mode != Mode::Frightened)
    {
        auto dir = getOptimalDirection(maze, dt);
        updatePosition(dir, dt);
    }
}

float Ghost::calculateLinearDistance()
{
    //calculates distance between ghost and target
    //Dear old friend, Pythagoras
    /*auto TileCol = static_cast<int>(xPosition/48);
    std::cout << "Tile col: " << TileCol << std::endl;*/
    return sqrt(pow(xPosition-xTargetPos,2)+(pow(yPosition-yTargetPos,2)));
}

GDirection Ghost::getOptimalDirection(std::vector<std::shared_ptr<GameWorldResources>>& maze,const float dt)
{
    GDirection bestDir = GDirection::Still;
    auto minDistance = calculateLinearDistance();//The straight line distance will give min distance between ghost and target
    std::vector<GDirection>directions = {GDirection::Left,GDirection::Right,GDirection::Up, GDirection::Down};

    for(auto dir : directions)
    {
        if (isOppositeDirection(dir, prevDirection))
            continue;//Skip this direction if it will result to ghost reversing
        
        auto[newXpos, newYpos] = getNextPosition(dir, dt);
        auto isCollided = collision_manager.ghostWallCollisions(maze,newXpos,newYpos);
        if(!isCollided)//A valid move if ghost does not collide with wall (should probably use tile-based collisions)
        {
            auto newDist = sqrt(pow(newXpos-xTargetPos,2)+(pow(newYpos-yTargetPos,2)));
            if (newDist < minDistance)
            {
                minDistance = newDist;
                bestDir = dir;
            }
        }
    }
    //if no valid direction is found, allow reversing (Condition when ghost is stuck)
    if(bestDir == GDirection::Still)
    {
        for (auto dir : directions)
        {
            auto[newXpos, newYpos] = getNextPosition(dir, dt);
            auto isCollided = collision_manager.ghostWallCollisions(maze,newXpos,newYpos);
            if(!isCollided)
            {
                bestDir = dir;
                break;
            }
        }
    }
    return bestDir;
}

bool Ghost::isOppositeDirection(GDirection nextDir, GDirection previousDir)
{
    return ((nextDir == GDirection::Up && previousDir == GDirection::Down) ||(nextDir == GDirection::Down && previousDir == GDirection::Up)
    ||(nextDir == GDirection::Left && previousDir == GDirection::Right) || (nextDir == GDirection::Right && previousDir == GDirection::Left));
}

std::tuple<float,float> Ghost::getNextPosition(GDirection dir, const float dt)
{
    auto[newXpos, newYpos] = getPosition();//Get currentt position
    auto TileCol = static_cast<int>(newXpos/48);
    auto TileRow = static_cast<int>(newYpos/48);
    switch (dir)
    {
    case GDirection::Up:
        if (gameMap[TileRow-1][TileCol] == "0")
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

void Ghost::updatePosition(GDirection dir, const float dt)
{
    prevDirection = dir;
    auto[nextX, nextY] = getNextPosition(dir, dt);
    setPosition(nextX, nextY);
}