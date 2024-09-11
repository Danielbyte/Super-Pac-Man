#ifndef PLAYER
#define PLAYER
#include<tuple>
#include "collisionsManager.h"
#include "gameWorldResources.h"

enum class Direction{Up, Down, Left, Right, Still};

class Player
{
private:
 float xPosition;
 float yPosition;
 float playerSpeed;
 bool willCollide(Direction direction, std::vector<std::shared_ptr<GameWorldResources>>& maze);//function to check if the next move will result in a wall collision
 CollisionsManager collisions_manager;
 Direction getPlayerDirection() const;

public:
    Player();
    void movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed, bool downArrowKeyPressed, bool upArrowKeyPressed
    , std::vector<std::shared_ptr<GameWorldResources>>& maze);
    std::tuple<float, float> getPlayerPosition() const;
    Direction playerDirection;

    void setPlayerPosition(float x, float y);
};
#endif //PLAYER

