#include "entity.h"

Entity::Entity():
xPosition{-100.0f},
yPosition{-100.0f}
{}

void Entity::setPosition(const float x, const float y)
{

}

std::tuple<float, float> Entity::getPosition() const
{
    return {xPosition, yPosition};
}