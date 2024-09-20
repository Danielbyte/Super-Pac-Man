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
            //ghost->setPo
            break;
        
        default:
            break;
        }
    }
}