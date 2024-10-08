#include "ghostManager.h"

GhostManager::GhostManager():
initialBlueXpos{297.0f},
initialBlueYpos{153.90},
initialRedXpos{249.0f},
initialRedYpos{105.0f},
initialOrangeXpos{249.0f},
initialOrangeYpos{201.0f},
initialPinkXpos{201.0f},
initialPinkYpos{153.0f},
MAZE_WIDTH{11},//consist of 11 tiles
MAZE_HEIGHT{12},//consists of 13 tiles
TILE_SIZE{48.0f},//each tile is a 48 x 48
red_mode_switch{1},//2 = chase mode, 1 = scatter mode
pink_mode_switch{1},
orange_mode_switch{1},
blue_mode_switch{1}
{
    auto [doorTileX, doorTileY] = convertToTilePosition(initialRedXpos, initialRedYpos);
}

void GhostManager::InitialiseGhostPositions(std::vector<std::shared_ptr<Ghost>>& ghosts)
{
    for(auto& ghost : ghosts)
    {
        auto type = ghost->getType();

        switch (type)
        {
        case Type::Pink:
            ghost->setPosition(initialPinkXpos, initialPinkYpos);
            ghost->assignCorner(0.0f, -48.0f);//Pink's corner @ top-left corner
            ghost->setMode(Mode::Initial);//ghost initial mode
            break;
        case Type::Blue:
            ghost->setPosition(initialBlueXpos, initialBlueYpos);
            ghost->assignCorner((MAZE_WIDTH-1)*TILE_SIZE, MAZE_HEIGHT*TILE_SIZE);
            ghost->setMode(Mode::Initial);
            break;
        case Type::Orange:
            ghost->setPosition(initialOrangeXpos, initialOrangeYpos);
            ghost->assignCorner(0.0f, MAZE_HEIGHT*TILE_SIZE);
            ghost->setMode(Mode::Initial);
            break;
        case Type::Red:
             ghost->setPosition(initialRedXpos, initialRedYpos);
             ghost->assignCorner((MAZE_WIDTH-1)*TILE_SIZE, -48.0f);//Red's corner @ top-right
             ghost->setMode(Mode::Scatter);//ghost initially in scatter mode
             ghost->disableDoorUse();
             ghost->moveToCorner();
             break;
        default:
            break;
        }
    }
}

void GhostManager::updateTarget(std::vector<std::shared_ptr<Ghost>> ghosts, const float xPlayerPos, const float yPlayerPos)
{
    for (auto& ghost : ghosts)
    {
        //Get type of ghost
        auto type = ghost->getType();
        auto mode = ghost->getMode();
        if (mode == Mode::Frightened)
        {
            red_watch->restartTimer();
            pink_watch->restartTimer();
            orange_watch->restartTimer();
            blue_watch->restartTimer();
            red_mode_switch = 1;
            orange_mode_switch = 1;
            pink_mode_switch = 1;
            blue_mode_switch = 1;
            setTarget(ghost, xPlayerPos, yPlayerPos);
            continue;
        }

        auto time_elapsed = red_watch->elapsedTime();
        auto pink_time_elapsed = pink_watch->elapsedTime();
        auto orange_time_elapsed = orange_watch->elapsedTime();
        auto blue_time_elapsed = blue_watch->elapsedTime();
        switch (type)
        {
        case Type::Red:
            if (time_elapsed >= 5.0f && red_mode_switch == 1)
            {
                ghost->setMode(Mode::Chase);
                red_watch->restartTimer();
                red_mode_switch = 2;
                break;  
            }
            if (time_elapsed >= 30.0f && red_mode_switch == 2)
            {
                ghost->setMode(Mode::Scatter);
                red_watch->restartTimer();
                red_mode_switch = 1;
            }
            break;
        case Type::Pink:
            if (pink_time_elapsed >= 5.0f && pink_mode_switch == 1)
            {
                ghost->setMode(Mode::Chase);
                pink_watch->restartTimer();
                pink_mode_switch = 2;
                break;  
            }
            if (pink_time_elapsed >= 30.0f && pink_mode_switch == 2)
            {
                ghost->setMode(Mode::Scatter);
                pink_watch->restartTimer();
                pink_mode_switch = 1;
            }
            break;
        case Type::Orange:
            if (orange_time_elapsed >= 5.0f && orange_mode_switch == 1)
            {
                ghost->setMode(Mode::Chase);
                orange_watch->restartTimer();
                orange_mode_switch = 2;
                break;  
            }
            if (orange_time_elapsed >= 30.0f && orange_mode_switch == 2)
            {
                ghost->setMode(Mode::Scatter);
                orange_watch->restartTimer();
                orange_mode_switch = 1;
            }
            break;
        case Type::Blue:
            if (blue_time_elapsed >= 5.0f && blue_mode_switch == 1)
            {
                ghost->setMode(Mode::Chase);
                blue_watch->restartTimer();
                blue_mode_switch = 2;
                break;  
            }
            if (blue_time_elapsed >= 30.0f && blue_mode_switch == 2)
            {
                ghost->setMode(Mode::Scatter);
                blue_watch->restartTimer();
                blue_mode_switch = 1;
            }
            break;
        
        default:
            break;
        }
        setTarget(ghost, xPlayerPos, yPlayerPos);
    }
}

void GhostManager::setTarget(std::shared_ptr<Ghost> ghost, const float xPlayerPos, const float yPlayerPos)
{
    auto ghostMode = ghost->getMode();
    auto[xPos, yPos] = ghost->getPosition();
    switch (ghostMode)
    {
    case Mode::Scatter:
        //Ghost should move to respective corner
        ghost->moveToCorner();
    break;
    
    case Mode::Chase:
        ghost->updateTarget(xPlayerPos,yPlayerPos);
    break;

    case Mode::Frightened:
        ghost->moveToCorner();
    break;
    case Mode::Initial:
         ghost->updateTarget(initialRedXpos,initialRedYpos);
         if (yPos <= initialRedYpos)
         {
            ghost->setMode(Mode::Scatter);
            ghost->disableDoorUse();
         }
    break;
    
    default:
        break;
    }
}

std::tuple<int, int> GhostManager::convertToTilePosition(float xPos, float yPos)
{
    int x = static_cast<int>(xPos/TILE_SIZE);
    int y = static_cast<int>(yPos/TILE_SIZE);
    return{x , y};
}

void GhostManager::initialiseGhosts(std::vector<std::shared_ptr<Ghost>>& ghosts)
{
    auto blue = std::make_shared<Ghost>();
    blue->setType(Type::Blue);
    ghosts.push_back(blue);

    auto orange = std::make_shared<Ghost>();
    orange->setType(Type::Orange);
    ghosts.push_back(orange);

    auto pink = std::make_shared<Ghost>();
    pink->setType(Type::Pink);
    ghosts.push_back(pink);

    auto red = std::make_shared<Ghost>();
    red->setType(Type::Red);
    ghosts.push_back(red);

    InitialiseGhostPositions(ghosts);
}

void GhostManager::updateGhostModes(std::vector<std::shared_ptr<Ghost>>& ghosts, std::shared_ptr<Player>& player)
{
    auto [xPlayerPos, yPlayerPos] = player->getPosition();
    auto playerAtePowerPellet = player->consumedPowerPellet();
    updateTarget(ghosts, xPlayerPos, yPlayerPos);
    for (auto& ghost : ghosts)
    {
        auto justRespawned = ghost->isJustRespawned();
        if(playerAtePowerPellet && !justRespawned)
           ghost->setMode(Mode::Frightened);
        
        //Toggle of frightened mode
        if(!playerAtePowerPellet && (ghost->getMode() == Mode::Frightened))
           ghost->setMode(Mode::Scatter);
    }
}

void GhostManager::restartGhostTimers()
{
    red_watch->restartTimer();
    blue_watch->restartTimer();
    orange_watch->restartTimer();
    pink_watch->restartTimer();
}