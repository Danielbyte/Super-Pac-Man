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
 static std::vector<std::vector<char>>gameMap; //All game objects should modify and share the same coppy of the game maze
private:
    /* data */
};
#endif
