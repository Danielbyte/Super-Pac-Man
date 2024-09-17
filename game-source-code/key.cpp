#include "key.h"

Key::Key():
xPosition{-50.0f},//Position outside screen
yPosition{-50.0f},//Position outside of screen
canDelete{false}
{}

std::tuple<float, float> Key::getPosition() const
{
    return {xPosition, yPosition};
}

void Key::setPosition(const float xPos, const float yPos)
{
    xPosition = xPos;
    yPosition = yPos;
}

void Key::markForDeletion()
{
    canDelete = true;
}

bool Key::getIfCanDelete() const
{
    return canDelete;
}