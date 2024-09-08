#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class GameWorld
{
public:
 GameWorld();
 static void loadMapFromFile();
 //Access static game map
 static const std::vector<std::vector<char>>& getGameMap();//return by constant reference (make map read only to other classes. only this class can modify this vector)
 
private:
 static std::vector<std::vector<char>>gameMap; //All game objects should modify and share the same coppy of the game maze
};
#endif
