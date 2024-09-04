#ifndef PLAYER
#define PLAYER

class Player
{
private:
 float xPosition;
 float yPosition;

public:
    Player();
    void movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed, bool downArrowKeyPressed, bool upArrowKeyPressed);
};
#endif //PLAYER

