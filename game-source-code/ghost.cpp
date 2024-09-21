#include "ghost.h"

Ghost::Ghost():
xPosition{-100.0f},
yPosition{-100.0f}
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