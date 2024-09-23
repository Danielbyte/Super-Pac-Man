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
    GDirection currentDirection;//Track previous direction to avoid reversing
    Mode mode;
    Type type;
    float ghostSpeed;

    GDirection getOptimalDirection(const float dt);
    bool isOppositeDirection(GDirection nextDir, GDirection previousDir);
    std::tuple<float,float> getNextPosition(GDirection dir, const float dt);
    CollisionsManager collision_manager;
    void updatePosition(const float dt);
    std::vector<std::vector<std::string>>gameMap = {};
    GameWorld game_world;
    float integralDistance;//summation of distance travelled by ghost (will be used to monitor if ghost has travelled a tile's distance) 
    bool getIsValidMove(GDirection _direction, int tileRow, const int tileColumn);
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
    void update(std::vector<std::shared_ptr<GameWorldResources>>& maze, const float dt);
    void setPosition(const float xPos, const float yPos);
    void assignCorner(const float x, const float y);
    float calculateLinearDistance();
    void moveToCorner();
};
#endif