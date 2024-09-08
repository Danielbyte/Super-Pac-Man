#ifndef GAMEWORLDRESOURCES_H
#define GAMEWORLDRESOURCES_H

#include "raylib-cpp.hpp"
#include<tuple>
using namespace raylib;

//This class is for updating maze texture/s
class GameWorldResources
{
public:
GameWorldResources();
GameWorldResources(int tilePosX, int tilePosY);//constructor overloading
std::tuple<float, float>getTileScreenPosition() const;
private:
void loadTextures();
float tileScreenPosX;
float tileScreenPosY;
};
#endif