#include "player.h"

Player::Player():
xPosition{376.0f},//New player center
yPosition{326.0f},//New player center
playerSpeed{2.0f}
{}

void Player::movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed,
                        bool downArrowKeyPressed, bool upArrowKeyPressed)
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