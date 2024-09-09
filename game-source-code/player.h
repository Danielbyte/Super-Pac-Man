#ifndef PLAYER
#define PLAYER
#include<tuple>

class Player
{
private:
 float xPosition;
 float yPosition;
 float playerSpeed;

public:
    Player();
    void movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed, bool downArrowKeyPressed, bool upArrowKeyPressed);
    std::tuple<float, float> getPlayerPosition() const;

    void setPlayerPosition(float x, float y);
};
#endif //PLAYER

