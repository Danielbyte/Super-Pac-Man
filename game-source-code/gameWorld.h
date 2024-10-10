#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "fruit.h"
#include "key.h"
#include "lock.h"
#include "flashingSymbols.h"

class GameWorld
{
public:
 GameWorld();
 static void loadMapFromFile();
 //Access static game map
 static const std::vector<std::vector<std::string>>& getGameMap();//return by constant reference (make map read only to other classes. only this class can modify this vector)
 static std::vector<std::shared_ptr<Fruit>>& getMazeFruits();
 static std::vector<std::shared_ptr<Key>>& getMazeKeys();
 static std::vector<std::shared_ptr<Lock>>& getMazeLocks();
 int getNumberOfColumns() const;
 int getNumberOfRows() const;
 void createStar(std::vector<std::shared_ptr<Fruit>>& fruits);
 void placeStar(std::vector<std::shared_ptr<Fruit>>& fruits);
 void restartStarCreationWatch();
 std::shared_ptr<FlashingSymbols>& getReferenceSymbol() const;
 std::shared_ptr<FlashingSymbols>& getSymbolToShow() const;
 void resetFlashingSymbols();

private:
 static std::vector<std::vector<std::string>>gameMap; //All game objects should modify and share the same coppy of the game maze
 static std::vector<std::shared_ptr<Fruit>>fruits;
 static std::vector<std::shared_ptr<Key>>keys;
 static std::vector<std::shared_ptr<Lock>>locks;
 static int numberOfColumns;//number of columns read from game map
 static int numberOfRows;
 StopWatch star_creation_watch;
 std::shared_ptr<FlashingSymbols> ReferenceSymbol = std::make_shared<FlashingSymbols>();//This is the reference symbol
 std::shared_ptr<FlashingSymbols> flashingSymbol = std::make_shared<FlashingSymbols>();

 //Utility function/s
 static void placeFruits();
 static void placeKeys();
 static void placeLocks();
 void selectReferenceSymbol();
};
#endif
