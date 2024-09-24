#include "lock.h"

Lock::Lock():
xPosition{-100.0f},
yPosition{-100.0f},
isOpen{false},
lockId{0},
lock_type{LockType::Unknown}//lock type unknown initially
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

void Lock::setPosition(const float xPos, const float yPos)
{
    xPosition = xPos;
    yPosition = yPos;
}

LockType Lock::getLockType() const
{
    return lock_type;
}

void Lock::setLockType(LockType type)
{
    lock_type = type;
}

int Lock::getLockId() const
{
    return lockId;
}
    
void Lock::setLockId(int id)
{
    lockId = id;
}