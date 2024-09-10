#include "player.h"

Player::Player():
xPosition{376.0f},//New player center
yPosition{326.0f},//New player center
playerSpeed{2.0f}
{}

void Player::movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed,
                        bool downArrowKeyPressed, bool upArrowKeyPressed, 
                        std::vector<std::shared_ptr<GameWorldResources>>& maze)
{
    if (rightArrowKeyPressed)
    {
        //move player to the right
        xPosition += playerSpeed;
        if (xPosition >= 760.0f)
           xPosition = 760.0f; //Cater for wall width of 8 pixels
    }

    if(leftArrowKeyPressed)
    {
        //Move player to the left
        xPosition -= playerSpeed;
        if (xPosition <= 8.0f)
            xPosition = 8.0f; //Cater for wall width of 8 pixels
    }

    if(downArrowKeyPressed)
    {
        //move player downwards
        yPosition += playerSpeed;

        if (yPosition >= 664.0f)
            yPosition = 664.0f; //Cater for wall width of 8 pixels
    }

    if (upArrowKeyPressed)
    {
        //first check if this movement will not result in player collision with wall
        bool _willCollide = willCollide(Direction::Up, maze);

        if (_willCollide)
         return;
        //move player upwards
        yPosition -= playerSpeed;
        //Restrict player within bounds
        if (yPosition <= 8.0f)
            yPosition = 8.0f; //Cater for wall width of 8 pixels
    }
}

std::tuple<float, float> Player::getPlayerPosition() const
{
    return {xPosition, yPosition};
}

void Player::setPlayerPosition(float x, float y)
{
    xPosition = x;
    yPosition = y;
}

bool Player::willCollide(Direction direcction, std::vector<std::shared_ptr<GameWorldResources>>& maze)
{
    auto nextPlayerYpos = yPosition + 0.2f;
    auto isCollided = collisions_manager.playerWallCollisions(maze,xPosition, nextPlayerYpos);

    if (isCollided)
    return true;

    return false;
}