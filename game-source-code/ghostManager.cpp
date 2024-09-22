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
MAZE_HEIGHT{13},//consists of 13 tiles
TILE_SIZE{48.0f}//each tile is a 48 x 48
{}

void GhostManager::InitialiseGhostPositions(std::vector<std::shared_ptr<Ghost>>& ghosts)
{
    for(auto& ghost : ghosts)
    {
        auto type = ghost->getType();

        switch (type)
        {
        case Type::Pink:
            ghost->setPosition(initialPinkXpos, initialPinkYpos);
            //ghost->assignCorner(0.0f, 0.0f);//Pink's corner @ top-left corner
            ghost->setMode(Mode::Chase);//ghost initially in scatter mode
            break;
        case Type::Blue:
            ghost->setPosition(initialBlueXpos, initialBlueYpos);
            break;
        case Type::Orange:
            ghost->setPosition(initialOrangeXpos, initialOrangeYpos);
            break;
        case Type::Red:
             ghost->setPosition(initialRedXpos, initialRedYpos);
             ghost->assignCorner((MAZE_WIDTH-1)*TILE_SIZE + 9.0f, 0.0f + 9.0f);//Red's corner @ top-right
             ghost->setMode(Mode::Scatter);//ghost initially in scatter mode
             break;
        default:
            break;
        }
    }
}

void GhostManager::updateTarget(std::vector<std::shared_ptr<Ghost>>& ghosts, const float xPlayerPos, const float yPlayerPos)
{
    for (auto& ghost : ghosts)
    {
        //Get type of ghost
        auto type = ghost->getType();
        auto mode = ghost->getMode();
        switch (type)
        {
        case Type::Red:
            //get ghost mode
            if (mode == Mode::Chase)
            {

            }
            if (mode == Mode::Frightened)
            {

            } 
            if (mode == Mode::Scatter)
            {
                setTarget(ghost, xPlayerPos, yPlayerPos);
            }       
        break;
        default:
            break;
        }
    }
}

void GhostManager::setTarget(std::shared_ptr<Ghost>& ghost, const float xPlayerPos, const float yPlayerPos)
{
    auto ghostMode = ghost->getMode();
    switch (ghostMode)
    {
    case Mode::Scatter:
        //Ghost should move to respective corner
        ghost->moveToCorner();
        break;
    
    case Mode::Chase:
        //ghost->
        break;

    case Mode::Frightened:
        break;
    
    default:
        break;
    }
}