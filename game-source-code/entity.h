#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <tuple>
#include <string>
#include <vector>

enum class Direction{Up, Down, Left, Right, Still};

class Entity
{
private:
    /* data */
protected:
    float xPosition;
    float yPosition;
    std::vector<std::vector<std::string>>gameMap = {};
    Direction direction;
public:
    Entity();
    ~Entity();
    std::tuple<float, float> getPosition() const;
    void setPosition(const float x, const float y);
    void setDirection(Direction _direction);
    Direction getDirection() const;
};
#endif