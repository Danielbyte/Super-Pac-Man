#ifndef GHOST_H
#define GHOST_H
#include "stopwatch.h"
#include "player.h"

enum class Mode{Frightened, Scatter, Chase};
enum class Type{Pink, Red, Orange, Blue};

class Ghost : public Entity
{
private:
    float xPosition;
    float yPosition;
    float xTargetPos, yTargetPos;
    int targetTileX, targetTileY;
    float targetCornePosX, targetCornerPosY;
    Direction direction;
    Direction currentDirection;//Track previous direction to avoid reversing
    Mode mode;
    Type type;
    float ghostSpeed;

    Direction getOptimalDirection(std::vector<std::shared_ptr<Lock>>& locks, const float dt);
    bool isOppositeDirection(Direction nextDir, Direction previousDir);
    std::tuple<float,float> getNextPosition(Direction dir, const float dt);
    CollisionsManager collision_manager;
    void updatePosition(std::vector<std::shared_ptr<Lock>>& locks, const float dt);
    std::vector<std::vector<std::string>>gameMap = {};
    GameWorld game_world;
    float integralDistance;//summation of distance travelled by ghost (will be used to monitor if ghost has travelled a tile's distance) 
    void getIsValidMove(Direction _direction, int tileRow, const int tileColumn, bool& isValid,
    std::vector<std::shared_ptr<Lock>>& locks);
    Direction priorityDirection(std::vector<std::shared_ptr<Lock>>& locks);
    bool isInitial;
    std::tuple<int,int> getNextTile(Direction dir);
    StopWatch time_since_respawn;
    bool justSpawned;
public:
    Ghost();
    std::tuple<float, float>getPosition() const;
    Direction getDirection() const;
    Type getType() const;
    Mode getMode() const;
    void setDirection(Direction _direction);
    void setType(Type _type);
    void setMode(Mode _mode);
    void switchMode();
    float getTargetDistance();
    void updateTarget(const float x, const float y);
    void update(std::vector<std::shared_ptr<GameWorldResources>>& maze,std::vector<std::shared_ptr<Lock>>& locks,
     const float dt);
    void setPosition(const float xPos, const float yPos);
    void assignCorner(const float x, const float y);
    float calculateLinearDistance();
    void moveToCorner();
    bool isJustRespawned();
    void respawn();
};
#endif