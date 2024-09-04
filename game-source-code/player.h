#ifndef PLAYER
#define PLAYER
#include<tuple>

class Player
{
private:
 float xPosition;
 float yPosition;

public:
    Player();
    void movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed, bool downArrowKeyPressed, bool upArrowKeyPressed);
    std::tuple<float, float> getPlayerPosition() const;
};
#endif //PLAYER

