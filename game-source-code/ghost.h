#ifndef GHOST_H
#define GHOST_H
#include <tuple>
#include "stopwatch.h"

enum class Direction{Left, Right, Up, Down, Still};
enum class Mode{Frightened, Scatter, Chase};
enum class Type{Pink, Red, Orange, Blue};
class Ghost
{
private:
    float xPosition;
    float yPosition;
    float xTargetPos, yTargetPos;
    Direction direction;
    Mode mode;
    Type type;
public:
    Ghost();
    std::tuple<float, float>getPosition() const;
    Direction getDirection() const;
    Type getType() const;
    Mode getMode() const;
    void setDirection(Direction _direction);
    void setType(Type _type);
    void setMode(Mode _mode);
};
#endif