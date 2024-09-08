#include "gameWorld.h"

GameWorld::GameWorld(){}

void GameWorld::loadMapFromFile()
{
    std::ifstream gameMapFile("resources/gameMap.txt");
    int count = 0;
    std::string line;
    if(gameMapFile.is_open())
    {
        int tileId;
        while (std::getline(gameMapFile, line))
        {
            std::vector<char>row(line.begin(), line.end());
            gameMap.push_back(row);
            ++count;
        }
        
    }
    gameMapFile.close();
    std::cout << "Number of Rows: " << gameMap.size() << std::endl;
}

std::vector<std::vector<char>> GameWorld::gameMap = {};//Static member variables are accessed at class level

const std::vector<std::vector<char>>& GameWorld::getGameMap()
{
    return gameMap;
}