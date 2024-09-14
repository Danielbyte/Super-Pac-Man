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

public:
    Player();
    void movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed, bool downArrowKeyPressed, bool upArrowKeyPressed
    , std::vector<std::shared_ptr<GameWorldResources>>& maze, const float dt);
    std::tuple<float, float> getPlayerPosition() const;
    Direction playerDirection;

    void setPlayerPosition(float x, float y);
     Direction getPlayerDirection() const;
};
#endif //PLAYER

