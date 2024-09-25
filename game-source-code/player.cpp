#include "player.h"

Player::Player():
xPosition{400.0f},//New player center
yPosition{326.0f},//New player center
playerSpeed{102.0f},
playerDirection{Direction::Right},//Pacman initially facing right
superPacman{false}
{}

void Player::movePlayer(bool rightArrowKeyPressed, bool leftArrowKeyPressed,
                        bool downArrowKeyPressed, bool upArrowKeyPressed, 
                        std::vector<std::shared_ptr<GameWorldResources>>& maze, 
                        std::vector<std::shared_ptr<Lock>>& locks, const float dt)
{
    auto elapsed_time = super_pacman_timer.elapsedTime();
    if (elapsed_time >= 7.0f && superPacman)
        toggleOffSuperPacmanMode();

    if (rightArrowKeyPressed)
    {
        playerDirection = Direction::Right;
        bool _willCollide = willCollideWithWall(Direction::Right, maze);
        auto _willCollide1 = willCoolideWithLock(playerDirection,locks);
        if (_willCollide || _willCollide1)
         return;
        //move player to the right
        xPosition += playerSpeed * dt;
        if (xPosition >= 560.0f)
           xPosition = -32.0f; //Cater for wall width of 8 pixels
    }

    if(leftArrowKeyPressed)
    {
        playerDirection = Direction::Left;
        bool _willCollide = willCollideWithWall(Direction::Left, maze);
        auto _willCollide1 = willCoolideWithLock(playerDirection,locks);
        if (_willCollide || _willCollide1)
         return;        
        //Move player to the left
        xPosition -= playerSpeed * dt;
        if (xPosition <= -32.0f)//Player should wrap around instead
            xPosition = 528.0f; //Cater for wall width of 8 pixels
    }

    if(downArrowKeyPressed)
    {
        playerDirection = Direction::Down;
        bool _willCollide = willCollideWithWall(Direction::Down, maze);
        auto _willCollide1 = willCoolideWithLock(playerDirection,locks);
        if (_willCollide || _willCollide1)
         return;
        //move player downwards
        yPosition += playerSpeed * dt;

        if (yPosition >= 664.0f)
            yPosition = 664.0f; //Cater for wall width of 8 pixels
    }

    if (upArrowKeyPressed)
    {
        playerDirection = Direction::Up;
        //first check if this movement will not result in player collision with wall
        bool _willCollide = willCollideWithWall(Direction::Up, maze);
        auto _willCollide1 = willCoolideWithLock(playerDirection,locks);
        if (_willCollide || _willCollide1)
         return;
        //move player upwards
        yPosition -= playerSpeed * dt;
        //Restrict player within bounds
        if (yPosition <= 8.0f)
            yPosition = 8.0f; //Cater for wall width of 8 pixels
    }
}

std::tuple<float, float> Player::getPlayerPosition() const
{
    return {xPosition, yPosition};
}

void Player::setPlayerPosition(float x, float y)
{
    xPosition = x;
    yPosition = y;
}

Direction Player::getPlayerDirection() const
{
    return playerDirection;
}

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

   return collisions_manager.lockCollisions(locks,nextPlayerXpos,nextPlayerYpos);
}

void Player::setToSuperPacmanMode()
{
    super_pacman_timer.restartTimer();
    superPacman = true;
    std::cout << "Start" << std::endl;
}

void Player::toggleOffSuperPacmanMode()
{
    superPacman = false;
     std::cout << "End" << std::endl;
}

bool Player::isSuperPacman() const
{
    return superPacman;
}