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
            std::vector<std::string>row;
            std::istringstream iss(line);// Ignore spaces as they are just separators
            std::string tile;

            while (iss >> tile)
                  row.push_back(tile);//read each tile  
            
            if (!row.empty()) 
                gameMap.push_back(row);
                
            numberOfColumns = std::max(numberOfColumns, static_cast<int>(row.size()));
            ++numberOfRows;
        }
    }
    gameMapFile.close();
}

void GameWorld::placeFruits()
{
    std::shared_ptr<Fruit>fruit1 = std::make_shared<Fruit>();
    fruit1->setPosition(56.5f,152.5f);
    fruits.push_back(fruit1);

    std::shared_ptr<Fruit>fruit2 = std::make_shared<Fruit>();
    fruit2->setPosition(104.5f,152.5f);
    fruits.push_back(fruit2);

    std::shared_ptr<Fruit>fruit3 = std::make_shared<Fruit>();
    fruit3->setPosition(104.5f,200.5f);
    fruits.push_back(fruit3);

    std::shared_ptr<Fruit>fruit4 = std::make_shared<Fruit>();
    fruit4->setPosition(104.5f,248.5f);
    fruits.push_back(fruit4);

    std::shared_ptr<Fruit>fruit5 = std::make_shared<Fruit>();
    fruit5->setPosition(440.0f,345.0f);
    fruits.push_back(fruit5);

    std::shared_ptr<Fruit>fruit6 = std::make_shared<Fruit>();
    fruit6->setPosition(440.0f,392.0f);
    fruits.push_back(fruit6);

    std::shared_ptr<Fruit>fruit7 = std::make_shared<Fruit>();
    fruit7->setPosition(440.0f,152.5f);
    fruits.push_back(fruit7);

    std::shared_ptr<Fruit>fruit8 = std::make_shared<Fruit>();
    fruit8->setPosition(391.0f,152.5f);
    fruits.push_back(fruit8);
}

int GameWorld::getNumberOfColumns() const
{
    return numberOfColumns;
}

int GameWorld::getNumberOfRows() const
{
    return numberOfRows;
}

std::vector<std::vector<std::string>> GameWorld::gameMap = {};//Static member variables are accessed at class level
std::vector<std::shared_ptr<Fruit>> GameWorld::fruits = {};

int GameWorld::numberOfColumns = 0;

int GameWorld::numberOfRows = 0;

const std::vector<std::vector<std::string>>& GameWorld::getGameMap()
{
    return gameMap;
}

std::vector<std::shared_ptr<Fruit>>& GameWorld::getMazeFruits()
{
    return fruits;
}