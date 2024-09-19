#ifndef GHOST_H
#define GHOST_H
#include <tuple>
class Ghost
{
private:
    float xPosition;
    float yPosition;
public:
    Ghost();
    std::tuple<float, float>getPosition() const;
};
#endif