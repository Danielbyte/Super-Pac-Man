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
    int MAZE_WIDTH, MAZE_HEIGHT;
    float TILE_SIZE;
    float red_mode_switch;
    float pink_mode_switch;
    float orange_mode_switch;
    void setTarget(std::shared_ptr<Ghost> ghost, const float xPlayerPos, const float yPlayerPos);
    std::unique_ptr<StopWatch>red_watch = std::make_unique<StopWatch>();
    std::unique_ptr<StopWatch>blue_watch = std::make_unique<StopWatch>();
    std::unique_ptr<StopWatch>pink_watch = std::make_unique<StopWatch>();
    std::unique_ptr<StopWatch>orange_watch = std::make_unique<StopWatch>();
    std::tuple<int, int> convertToTilePosition(float xPos, float yPos);
public:
    GhostManager();
    void InitialiseGhostPositions(std::vector<std::shared_ptr<Ghost>>& ghosts);
    void updateTarget(std::vector<std::shared_ptr<Ghost>> ghosts, const float xPlayerPos, const float yPlayerPos);
    void restartGhostTimers();//Timers that will manage ghost switching modes
    void initialiseGhosts(std::vector<std::shared_ptr<Ghost>>& ghosts);
    void updateGhostModes(std::vector<std::shared_ptr<Ghost>>& ghosts, std::shared_ptr<Player>& player);
};
#endif
