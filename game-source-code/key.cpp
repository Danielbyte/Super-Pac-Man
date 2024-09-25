#include "key.h"

Key::Key():
xPosition{-50.0f},//Position outside screen
yPosition{-50.0f},//Position outside of screen
canDelete{false},
lockId1{-100},
lockId2{-100},
lockId3{-100},
tripleOpen{false}
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

void Key::setLockIds(int id1, int id2)
{
    lockId1 = id1;
    lockId2 = id2;
}

void Key::setLockIds(const int id1, const int id2, const int id3)
{
    tripleOpen = true;
    lockId1 = id1;
    lockId2 = id2;
    lockId3 = id3;
}

std::tuple<int, int, int> Key::getTripleLockIdsToUnlock() const
{
    return {lockId1, lockId2, lockId3};
}

std::tuple<int, int> Key::getLockIdsToUnlock() const
{
    return {lockId1, lockId2};
}

bool Key::isTripleOpener() const
{
    return tripleOpen;
}