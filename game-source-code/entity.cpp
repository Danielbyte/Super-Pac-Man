#include "entity.h"

Entity::Entity():
xPosition{-100.0f},
yPosition{-100.0f}
{
    gameMap = game_world.getGameMap();
}

void Entity::setPosition(const float x, const float y)
{
    xPosition = x;
    yPosition = y;
}

std::tuple<float, float> Entity::getPosition() const
{
    return {xPosition, yPosition};
}

Direction Entity::getDirection() const
{
    return direction;
}

void Entity::setDirection(Direction _direction)
{
    direction = _direction;
}

Entity::~Entity()
{
    gameMap.clear();
}