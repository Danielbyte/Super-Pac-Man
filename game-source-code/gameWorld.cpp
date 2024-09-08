#include "gameWorld.h"

GameWorld::GameWorld(){}

void GameWorld::loadMapFromFile()
{
    std::vector<std::vector<char>>map = {};
    std::ifstream gameMapFile("resources/gameMap.txt");
    int count = 0;
    std::string line;
    if(gameMapFile.is_open())
    {
        int tileId;
        while (std::getline(gameMapFile, line))
        {
            std::vector<char>row(line.begin(), line.end());
            map.push_back(row);
            ++count;
        }
        
    }
    gameMapFile.close();
    std::cout << "Number of tiles: "<< map.size() << std::endl;
    std::cout << "Number of rows: " << count << std::endl;
}