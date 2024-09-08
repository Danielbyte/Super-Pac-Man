#ifndef GAMEWORLDRESOURCES_H
#define GAMEWORLDRESOURCES_H

#include "raylib-cpp.hpp"
using namespace raylib;

//This class is for updating maze texture/s
class GameWorldResources
{
public:
GameWorldResources();

private:
void loadTextures();
};
#endif