#include "lock.h"

Lock::Lock():
xPosition{-100.0f},
yPosition{-100.0f},
isOpen{false}
{}

std::tuple<float, float> Lock::getPosition() const
{
    return {xPosition, yPosition};
}

void Lock::OpenLock()
{
    isOpen = true;
}

bool Lock::getIsOpen() const
{
    return isOpen;
}