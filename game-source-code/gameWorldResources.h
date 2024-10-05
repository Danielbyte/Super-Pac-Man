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
void setMazeWalls(std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures,
std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);

void verticalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);
void horizontalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);
std::shared_ptr<raylib::Texture2D>horizontalWallPiece = std::make_shared<raylib::Texture2D>();
std::shared_ptr<raylib::Texture2D>verticalWallPiece = std::make_shared<raylib::Texture2D>();
private:
void loadTextures();
void setWallProperties(int tilePosX, int tilePosY);
void processTileTexture(std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures,
std::vector<std::shared_ptr<GameWorldResources>>& maze_resources,const std::string element,const int tilePosX,const int tilePosY);
void topRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);
void topLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);
void bottomLeftCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);
void bottomRightCorner(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources);

float tileScreenPosX;
float tileScreenPosY;
GameWorld game_world;
ObjectType type;
};
#endif