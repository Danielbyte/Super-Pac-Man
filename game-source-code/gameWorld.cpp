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

    std::shared_ptr<Fruit>fruit9 = std::make_shared<Fruit>();
    fruit9->setPosition(391.0f,200.5f);
    fruits.push_back(fruit9);

    std::shared_ptr<Fruit>fruit10 = std::make_shared<Fruit>();
    fruit10->setPosition(391.0f,248.5f);
    fruits.push_back(fruit10);

    std::shared_ptr<Fruit>fruit11 = std::make_shared<Fruit>();
    fruit11->setPosition(485.0f,248.5f);
    fruits.push_back(fruit11);

    std::shared_ptr<Fruit>fruit12 = std::make_shared<Fruit>();
    fruit12->setPosition(6.5f,249.5f);
    fruits.push_back(fruit12);

    std::shared_ptr<Fruit>fruit13 = std::make_shared<Fruit>();
    fruit13->setPosition(56.5f,345.0f);
    fruits.push_back(fruit13);

    std::shared_ptr<Fruit>fruit14 = std::make_shared<Fruit>();
    fruit14->setPosition(56.5f,392.0f);
    fruits.push_back(fruit14);

    std::shared_ptr<Fruit>fruit15 = std::make_shared<Fruit>();
    fruit15->setPosition(150.5f,536.0f);
    fruits.push_back(fruit15);

    std::shared_ptr<Fruit>fruit16 = std::make_shared<Fruit>();
    fruit16->setPosition(200.5f,536.0f);
    fruits.push_back(fruit16);

    std::shared_ptr<Fruit>fruit17 = std::make_shared<Fruit>();
    fruit17->setPosition(247.5f,536.0f);
    fruits.push_back(fruit17);

    std::shared_ptr<Fruit>fruit18 = std::make_shared<Fruit>();
    fruit18->setPosition(297.5f,536.0f);
    fruits.push_back(fruit18);

    std::shared_ptr<Fruit>fruit19 = std::make_shared<Fruit>();
    fruit19->setPosition(345.5f,536.0f);
    fruits.push_back(fruit19);

    std::shared_ptr<Fruit>fruit20 = std::make_shared<Fruit>();
    fruit20->setPosition(150.5f,55.5f);
    fruits.push_back(fruit20);

    std::shared_ptr<Fruit>fruit21 = std::make_shared<Fruit>();
    fruit21->setPosition(200.5f,55.5f);
    fruits.push_back(fruit21);

    std::shared_ptr<Fruit>fruit22 = std::make_shared<Fruit>();
    fruit22->setPosition(247.5f,55.5f);
    fruits.push_back(fruit22);

    std::shared_ptr<Fruit>fruit23 = std::make_shared<Fruit>();
    fruit23->setPosition(297.5f,55.5f);
    fruits.push_back(fruit23);

    std::shared_ptr<Fruit>fruit24 = std::make_shared<Fruit>();
    fruit24->setPosition(345.5f,55.5f);
    fruits.push_back(fruit24);

    std::shared_ptr<Fruit>fruit25 = std::make_shared<Fruit>();
    fruit25->setPosition(297.5f,345.0f);
    fruits.push_back(fruit25);

    std::shared_ptr<Fruit>fruit26 = std::make_shared<Fruit>();
    fruit26->setPosition(343.5f,392.0f);
    fruits.push_back(fruit26);

    std::shared_ptr<Fruit>fruit27 = std::make_shared<Fruit>();
    fruit27->setPosition(343.5f,440.5f);
    fruits.push_back(fruit27);

    std::shared_ptr<Fruit>fruit28 = std::make_shared<Fruit>();
    fruit28->setPosition(200.5f,345.0f);
    fruits.push_back(fruit28);

    std::shared_ptr<Fruit>fruit29 = std::make_shared<Fruit>();
    fruit29->setPosition(150.5f,392.0f);
    fruits.push_back(fruit29);

    std::shared_ptr<Fruit>fruit30 = std::make_shared<Fruit>();
    fruit30->setPosition(150.5f,440.5f);
    fruits.push_back(fruit30);

    std::shared_ptr<Fruit>fruit31 = std::make_shared<Fruit>();
    fruit31->setPosition(247.5f,440.5f);
    fruits.push_back(fruit31);

    std::shared_ptr<Fruit>superPellet1 = std::make_shared<Fruit>();
    superPellet1->setPosition(154.5f,345.5f);
    superPellet1->markAsSuperPellet();
    fruits.push_back(superPellet1);
    
    std::shared_ptr<Fruit>superPellet2 = std::make_shared<Fruit>();
    superPellet2->setPosition(440.0f,345.5f);
    superPellet2->markAsSuperPellet();
    fruits.push_back(superPellet2);

    std::shared_ptr<Fruit>superPellet3 = std::make_shared<Fruit>();
    superPellet3->setPosition(343.5f,345.0f);
    superPellet3->markAsSuperPellet();
    fruits.push_back(superPellet3);

    std::shared_ptr<Fruit>powerPellet1 = std::make_shared<Fruit>();
    powerPellet1->setPosition(57.0f,57.5f);
    powerPellet1->markAsPowerPellet();
    fruits.push_back(powerPellet1);

    std::shared_ptr<Fruit>powerPellet2 = std::make_shared<Fruit>();
    powerPellet2->setPosition(440.0f,56.0f);
    powerPellet2->markAsPowerPellet();
    fruits.push_back(powerPellet2);

    std::shared_ptr<Fruit>powerPellet3 = std::make_shared<Fruit>();
    powerPellet3->setPosition(56.0f,490.0f);
    powerPellet3->markAsPowerPellet();
    fruits.push_back(powerPellet3);

    std::shared_ptr<Fruit>powerPellet4 = std::make_shared<Fruit>();
    powerPellet4->setPosition(440.0f,490.0f);
    powerPellet4->markAsPowerPellet();
    fruits.push_back(powerPellet4);
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