#ifndef GAMEWORLDRESOURCES_H
#define GAMEWORLDRESOURCES_H

#include "raylib-cpp.hpp"
#include<tuple>
#include<iostream>
#include <memory>
#include "gameWorld.h"
using namespace raylib;

enum class ObjectType {VerticalWall, HorizontalWall, Other};

//This class is for updating maze texture/s
class GameWorldResources
{
public:
GameWorldResources();
GameWorldResources(int tilePosX, int tilePosY, const ObjectType _type, const float xOffset, const float yOffset);//constructor overloading
std::tuple<float, float>getTileScreenPosition() const;
ObjectType getObjectType() const;
void initialiseGameBorder(int tilePosX, int tilePosY, const ObjectType _type);

private:
void loadTextures();
void setWallProperties(int tilePosX, int tilePosY);
float tileScreenPosX;
float tileScreenPosY;
std::shared_ptr<GameWorld>game_world = std::make_shared<GameWorld>();
ObjectType type;

raylib::Texture2D horizontalWallPieceT;
raylib::Image horizontalWallPieceI;
raylib::Texture2D verticalWallPieceT;
raylib::Image verticalWallPieceI;

std::vector<std::shared_ptr<GameWorldResources>>maze_resources = {};
std::vector<std::shared_ptr<raylib::Texture2D>>game_world_textures = {};

};
#endif