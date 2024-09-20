#ifndef GHOSTMANAGER_H
#define GHOSTMANAGER_H
#include "ghost.h"

class GhostManager
{
private:
    float initialBlueXpos, initialBlueYpos;
    float initialRedXpos, initialRedYpos;
    float initialOrangeXpos, initialOrangeYpos;
    float initialPinkXpos, initialPinkYpos;
public:
    GhostManager();
    void InitialiseGhostPositions(std::vector<std::shared_ptr<Ghost>>& ghosts);
};
#endif
