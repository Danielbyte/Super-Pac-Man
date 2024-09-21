#ifndef GHOST_H
#define GHOST_H
#include "stopwatch.h"
#include "player.h"

enum class GDirection{Left, Right, Up, Down, Still};
enum class Mode{Frightened, Scatter, Chase};
enum class Type{Pink, Red, Orange, Blue};
class Ghost
{
private:
    float xPosition;
    float yPosition;
    float xTargetPos, yTargetPos;
    float targetCornePosX, targetCornerPosY;
    GDirection direction;
    GDirection prevDirection;//Track previous direction to avoid reversing
    Mode mode;
    Type type;

    GDirection getOptimalDirection();
    bool isOppositeDirection(GDirection nextDir, GDirection previousDir);
public:
    Ghost();
    std::tuple<float, float>getPosition() const;
    GDirection getDirection() const;
    Type getType() const;
    Mode getMode() const;
    void setDirection(GDirection _direction);
    void setType(Type _type);
    void setMode(Mode _mode);
    void switchMode();
    float getTargetDistance();
    void updateTarget(const float x, const float y);
    void update(std::vector<std::vector<std::string>>& gameMap, const float dt);
    void setPosition(const float xPos, const float yPos);
    void assignCorner(const float x, const float y);
    float calculateLinearDistance();
    void moveToCorner();
};
#endif