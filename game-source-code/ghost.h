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
    GDirection direction;
    Mode mode;
    Type type;
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
    //void updateTarget();
    void update(std::shared_ptr<Player>& player, std::vector<std::vector<std::string>>& gameMap);
    void setPosition(const float xPos, const float yPos);
};
#endif