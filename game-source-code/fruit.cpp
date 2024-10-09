#include "fruit.h"
Fruit::Fruit():
xPosition{-100.0f},
yPosition{-100.0f},//Initially, at position that is off the screen
canDelete{false},
isSuperPellet{false},
isPowerPellet{false},
isStar{false}
{
    lifetime.restartTimer();
}

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

bool Fruit::getIsSuperPellet() const
{
    return isSuperPellet;
}

bool Fruit::getIsPowerPellet() const
{
    return isPowerPellet;
}

void Fruit::markAsPowerPellet()
{
    isPowerPellet = true;
}

void Fruit::markAsSuperPellet()
{
    isSuperPellet = true;
}

void Fruit::markAsStar()
{
    isStar = true;
}

bool Fruit::getIsStar() const
{
    return isStar;
}

float Fruit::getLifeTime()
{
    return lifetime.elapsedTime();
}