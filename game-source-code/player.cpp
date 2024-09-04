#include "player.h"

Player::Player():
xPosition{800.0f},
yPosition{450.0f}
{}

void Player::movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed,
                        bool downArrowKeyPressed, bool upArrowKeyPressed)
{
    if (rightArrowKeyPressed)
    {
        //move player to the right
        xPosition += 2.5f;
        if (xPosition >= 1426.0f)
           xPosition = 1426.0f;
    }

    if(leftArrowKeyPressed)
    {
        //Move player to the left
        xPosition -= 2.5f;
        if (xPosition <= 174.0f)
            xPosition = 174.0f;
    }

    if(downArrowKeyPressed)
    {
        //move player downwards
        yPosition += 2.5f;

        if (yPosition >= 711.5f)
            yPosition = 711.5f;
    }

    if (upArrowKeyPressed)
    {
        //move player upwards
        yPosition -= 2.5f;
        //Restrict player within bounds
        if (yPosition <= 188.5f)
            yPosition = 188.5f;
    }
}