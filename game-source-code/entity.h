#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <tuple>
#include <string>
#include <vector>

class Entity
{
private:
    /* data */
protected:
    float xPosition;
    float yPosition;
    std::vector<std::vector<std::string>>gameMap = {};
public:
    Entity();
    std::tuple<float, float> getPosition() const;
    void setPosition(const float x, const float y);
    ~Entity();
};
#endif