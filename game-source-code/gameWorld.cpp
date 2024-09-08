#include "gameWorld.h"

GameWorld::GameWorld(){}

std::vector<std::vector<char>> GameWorld::loadMapFromFile()
{
    std::ifstream gameMapFile("resources/gameMap.txt");
    int count = 0;
    if(gameMapFile.is_open())
    {
        int tileId;
        while (gameMapFile>>tileId)
        {
            //std::cout << tileId << std::endl;
            ++count;
        }
        
    }
    gameMapFile.close();
    //std::cout << "Number of tiles: "<< count << std::endl; 
}