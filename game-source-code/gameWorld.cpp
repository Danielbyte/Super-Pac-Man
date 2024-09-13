#include "gameWorld.h"

GameWorld::GameWorld(){}

void GameWorld::loadMapFromFile()
{
    std::ifstream gameMapFile("../resources/gameMap.txt");
    int count = 0;
    std::string line;
    if(gameMapFile.is_open())
    {
        int tileId;
        while (std::getline(gameMapFile, line))
        {
            std::vector<char>row;
            for (char ch : line) 
            {
                if (ch != ' ')   // Ignore spaces as they are just separators
                    row.push_back(ch);       
            }

            if (!row.empty()) 
                gameMap.push_back(row);
                
            numberOfColumns = std::max(numberOfColumns, static_cast<int>(row.size()));
            ++numberOfRows;
        }
    }
    gameMapFile.close();
}

int GameWorld::getNumberOfColumns() const
{
    return numberOfColumns;
}

int GameWorld::getNumberOfRows() const
{
    return numberOfRows;
}

std::vector<std::vector<char>> GameWorld::gameMap = {};//Static member variables are accessed at class level

int GameWorld::numberOfColumns = 0;

int GameWorld::numberOfRows = 0;

const std::vector<std::vector<char>>& GameWorld::getGameMap()
{
    return gameMap;
}