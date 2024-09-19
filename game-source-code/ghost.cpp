#include "ghost.h"

Ghost::Ghost():
xPosition{-100.0f},
yPosition{-100.0f}
{}

std::tuple<float, float>Ghost::getPosition() const
{
    return {xPosition, yPosition};
}