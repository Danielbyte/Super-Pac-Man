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
    }

    if(leftArrowKeyPressed)
    {
        //Move player to the left
    }

    if(downArrowKeyPressed)
    {
        //move player downwards
    }

    if (upArrowKeyPressed)
    {
        //move player upwards
    }
}