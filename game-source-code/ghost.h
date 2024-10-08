#ifndef GHOST_H
#define GHOST_H
#include "stopwatch.h"
#include "player.h"

enum class Mode{Frightened, Scatter, Chase};
enum class Type{Pink, Red, Orange, Blue};

class Ghost : public Entity
{
private:
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
    GameWorld game_world;
    float integralDistance;//summation of distance travelled by ghost (will be used to monitor if ghost has travelled a tile's distance) 
    void getIsValidMove(Direction _direction, int tileRow, const int tileColumn, bool& isValid,
    std::vector<std::shared_ptr<Lock>>& locks);
    Direction priorityDirection(std::vector<std::shared_ptr<Lock>>& locks);
    bool isInitial;
    std::tuple<int,int> getNextTile(Direction dir);
    StopWatch time_since_respawn;
    bool justSpawned;
    bool canUseDoor;
public:
    Ghost();
    Type getType() const;
    Mode getMode() const;
    void setType(Type _type);
    void setMode(Mode _mode);
    void updateTarget(const float x, const float y);
    void update(std::vector<std::shared_ptr<GameWorldResources>>& maze,std::vector<std::shared_ptr<Lock>>& locks,
     const float dt);
    void assignCorner(const float x, const float y);
    float calculateLinearDistance();
    void moveToCorner();
    bool isJustRespawned();
    void respawn();
    bool getCanUseDoor() const;
    void setToUseGhostDoor();
    void disableDoorUse();
};
#endif