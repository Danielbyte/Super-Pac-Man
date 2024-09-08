#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <vector>
#include <fstream>
#include <string>

class GameWorld
{
public:
 GameWorld();
 std::vector<std::vector<char>>loadMapFromFile();
private:
    /* data */
};
#endif
