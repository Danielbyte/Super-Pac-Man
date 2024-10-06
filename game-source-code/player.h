#ifndef PLAYER
#define PLAYER
#include<tuple>
#include "collisionsManager.h"
#include "gameWorldResources.h"
#include "lock.h"
#include "stopwatch.h"
#include "entity.h"

class Player : public Entity
{
private:
 float playerSpeed;
 bool willCollideWithWall(Direction direction, std::vector<std::shared_ptr<GameWorldResources>>& maze);//function to check if the next move will result in a wall collision
 bool willCoolideWithLock(Direction direction, std::vector<std::shared_ptr<Lock>>& locks);
 CollisionsManager collisions_manager;
 bool superPacman;
 bool atePowerPellet;
 StopWatch super_pacman_timer;
 StopWatch power_pellet_timer;

public:
    Player();
    void movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed, bool downArrowKeyPressed, bool upArrowKeyPressed
    , std::vector<std::shared_ptr<GameWorldResources>>& maze, std::vector<std::shared_ptr<Lock>>& locks, const float dt);

    bool isSuperPacman() const;
    bool consumedPowerPellet() const;

    void setToSuperPacmanMode();
    void inPowerPelletMode();
    void toggleOffSuperPacmanMode();
    void toggleOffPowerPellet();
    void updatePlayerStates();
};
#endif //PLAYER

