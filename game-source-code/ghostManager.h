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
    float targetXpos, targetYpos;
    void setTarget(std::shared_ptr<Ghost>& ghost, const float xPlayerPos, const float yPlayerPos);
public:
    GhostManager();
    void InitialiseGhostPositions(std::vector<std::shared_ptr<Ghost>>& ghosts);
    void updateTarget(std::vector<std::shared_ptr<Ghost>>& ghosts, const float xPlayerPos, const float yPlayerPos);
};
#endif
