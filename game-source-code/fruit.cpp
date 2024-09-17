#include "fruit.h"
Fruit::Fruit():
xPosition{-100.0f},
yPosition{-100.0f},//Initially, at position that is off the screen
canDelete{false}
{}

void Fruit::setPosition(const float xPos,const float yPos)
{
    xPosition = xPos;
    yPosition = yPos;
}

void Fruit::markForDeletion()
{
    canDelete = true;
}

bool Fruit::getIfCanDelete() const
{
    return canDelete;
}
   
std::tuple<float, float> Fruit::getPosition() const
{
    return {xPosition, yPosition};
}