#include "ghostManager.h"

GhostManager::GhostManager():
initialBlueXpos{297.0f},
initialBlueYpos{153.90},
initialRedXpos{249.0f},
initialRedYpos{105.0f},
initialOrangeXpos{249.0f},
initialOrangeYpos{201.0f},
initialPinkXpos{201.0f},
initialPinkYpos{153.0f}
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
            break;
        case Type::Blue:
            ghost->setPosition(initialBlueXpos, initialBlueYpos);
            break;
        case Type::Orange:
            ghost->setPosition(initialOrangeXpos, initialOrangeYpos);
            break;
        case Type::Red:
             ghost->setPosition(initialRedXpos, initialRedYpos);
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
        switch (type)
        {
        case Type::Red:
            //get ghost mode
             //auto mode = ghost->getMode();
             
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