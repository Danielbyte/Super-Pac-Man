#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "fruit.h"

class GameWorld
{
public:
 GameWorld();
 static void loadMapFromFile();
 //Access static game map
 static const std::vector<std::vector<std::string>>& getGameMap();//return by constant reference (make map read only to other classes. only this class can modify this vector)
 static std::vector<std::shared_ptr<Fruit>>& getMazeFruits();
 int getNumberOfColumns() const;
 int getNumberOfRows() const;

private:
 static std::vector<std::vector<std::string>>gameMap; //All game objects should modify and share the same coppy of the game maze
 static std::vector<std::shared_ptr<Fruit>>fruits;
 static int numberOfColumns;//number of columns read from game map
 static int numberOfRows;

 //Utility function/s
 static void placeFruits();
};
#endif
