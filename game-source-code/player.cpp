#include "player.h"

Player::Player():
playerSpeed{102.0f},
//playerDirection{Direction::Right},//Pacman initially facing right
superPacman{false},
atePowerPellet{false}
{
    setDirection(Direction::Right);//Pacman initially facing right
    setPosition(400.0f, 326.0f);
}

void Player::movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed,
                        bool downArrowKeyPressed, bool upArrowKeyPressed, 
                        std::vector<std::shared_ptr<GameWorldResources>>& maze, 
                        std::vector<std::shared_ptr<Lock>>& locks, const float dt)
{
    if (rightArrowKeyPressed)
    {
        setDirection(Direction::Right);
        bool _willCollide = willCollideWithWall(Direction::Right, maze);
        auto _willCollide1 = willCoolideWithLock(Direction::Right,locks);
        if (_willCollide || _willCollide1)
         return;
        //move player to the right
        xPosition += playerSpeed * dt;
        if (xPosition >= 560.0f)
           xPosition = -32.0f; //Cater for wall width of 8 pixels
    }

    if(leftArrowKeyPressed)
    {
        setDirection(Direction::Left);
        bool _willCollide = willCollideWithWall(Direction::Left, maze);
        auto _willCollide1 = willCoolideWithLock(Direction::Left,locks);
        if (_willCollide || _willCollide1)
         return;        
        //Move player to the left
        xPosition -= playerSpeed * dt;
        if (xPosition <= -32.0f)//Player should wrap around instead
            xPosition = 528.0f; //Cater for wall width of 8 pixels
    }

    if(downArrowKeyPressed)
    {
        setDirection(Direction::Down);
        bool _willCollide = willCollideWithWall(Direction::Down, maze);
        auto _willCollide1 = willCoolideWithLock(Direction::Down,locks);
        if (_willCollide || _willCollide1)
         return;
        //move player downwards
        yPosition += playerSpeed * dt;

        if (yPosition >= 664.0f)
            yPosition = 664.0f; //Cater for wall width of 8 pixels
    }

    if (upArrowKeyPressed)
    {
        setDirection(Direction::Up);
        //first check if this movement will not result in player collision with wall
        bool _willCollide = willCollideWithWall(Direction::Up, maze);
        auto _willCollide1 = willCoolideWithLock(Direction::Up,locks);
        if (_willCollide || _willCollide1)
         return;
        //move player upwards
        yPosition -= playerSpeed * dt;
        //Restrict player within bounds
        if (yPosition <= 8.0f)
            yPosition = 8.0f; //Cater for wall width of 8 pixels
    }
}
void Player::updatePlayerStates()
{
    auto elapsed_time = super_pacman_timer.elapsedTime();
    if (elapsed_time >= 7.0f && superPacman)
        toggleOffSuperPacmanMode();

    elapsed_time = power_pellet_timer.elapsedTime();
    if (elapsed_time >= 5.0f && atePowerPellet)
       toggleOffPowerPellet();
}
/*std::tuple<float, float> Player::getPlayerPosition() const
{
    return {xPosition, yPosition};
}*/

/*void Player::setPlayerPosition(float x, float y)
{
    xPosition = x;
    yPosition = y;
}*/

/*Direction Player::getPlayerDirection() const
{
    return playerDirection;
}*/

bool Player::willCollideWithWall(Direction direcction, std::vector<std::shared_ptr<GameWorldResources>>& maze)
{
    auto nextPlayerYpos = yPosition;
    auto nextPlayerXpos = xPosition;
    auto minCollisionOffset = 1.8f;
    switch (direcction)
    {
    case Direction::Up:
        nextPlayerYpos -= minCollisionOffset;
        break;
    case Direction::Down:
         nextPlayerYpos += minCollisionOffset;
         break;
    case Direction::Left:
         nextPlayerXpos -= minCollisionOffset;
         break;
    case Direction::Right:
         nextPlayerXpos += minCollisionOffset;
         break;
    default:
        break;
    }
    
    auto isCollided = collisions_manager.playerWallCollisions(maze,nextPlayerXpos, nextPlayerYpos);
    if (isCollided)
    return true;

    return false;
}

bool Player::willCoolideWithLock(Direction direction, std::vector<std::shared_ptr<Lock>>& locks)
{
    auto nextPlayerYpos = yPosition;
    auto nextPlayerXpos = xPosition;
    auto minCollisionOffset = 1.8f;
    switch (direction)
    {
    case Direction::Up:
        nextPlayerYpos -= minCollisionOffset;
        break;
    case Direction::Down:
         nextPlayerYpos += minCollisionOffset;
         break;
    case Direction::Left:
         nextPlayerXpos -= minCollisionOffset;
         break;
    case Direction::Right:
         nextPlayerXpos += minCollisionOffset;
         break;
    default:
        break;
    }

   return collisions_manager.lockCollisions(locks,nextPlayerXpos,nextPlayerYpos, superPacman);
}

void Player::setToSuperPacmanMode()
{
    super_pacman_timer.restartTimer();
    superPacman = true;
}

void Player::inPowerPelletMode()
{
    power_pellet_timer.restartTimer();
    atePowerPellet = true;
}

bool Player::consumedPowerPellet() const
{
    return atePowerPellet;
}

void Player::toggleOffSuperPacmanMode()
{
    superPacman = false;
}

void Player::toggleOffPowerPellet()
{
    atePowerPellet = false;
}

bool Player::isSuperPacman() const
{
    return superPacman;
}