#include "player.h"

Player::Player():
xPosition{800.0f},
yPosition{450.0f},
playerSpeed{2.0f}
{}

void Player::movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed,
                        bool downArrowKeyPressed, bool upArrowKeyPressed)
{
    if (rightArrowKeyPressed)
    {
        //move player to the right
        xPosition += playerSpeed;
        if (xPosition >= 752.0f)
           xPosition = 752.0f;
    }

    if(leftArrowKeyPressed)
    {
        //Move player to the left
        xPosition -= playerSpeed;
        if (xPosition <= 0.0f)
            xPosition = 0.0f;
    }

    if(downArrowKeyPressed)
    {
        //move player downwards
        yPosition += playerSpeed;

        if (yPosition >= 711.5f)
            yPosition = 711.5f;
    }

    if (upArrowKeyPressed)
    {
        //move player upwards
        yPosition -= playerSpeed;
        //Restrict player within bounds
        if (yPosition <= 188.5f)
            yPosition = 188.5f;
    }
}

std::tuple<float, float> Player::getPlayerPosition() const
{
    return {xPosition, yPosition};
}