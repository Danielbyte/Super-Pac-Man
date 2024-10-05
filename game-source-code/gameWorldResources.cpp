#include "gameWorldResources.h"

GameWorldResources::GameWorldResources():
tileScreenPosX{0.0f},
tileScreenPosY{0.0f}
{
    loadTextures();
}

GameWorldResources::GameWorldResources(int tilePosX, int tilePosY, const ObjectType _type,
 const float xOffset, const float yOffset)
{
    tileScreenPosX = (tilePosX + xOffset) * 48.0f;
    tileScreenPosY = (tilePosY + yOffset) * 48.0f;
    
    /*auto numberOfRows = game_world->getNumberOfRows();
    auto numberOfColumns = game_world->getNumberOfColumns();
    if (tilePosY == (numberOfRows - 1) && (tilePosX > 0 && tilePosX < (numberOfColumns - 1)))//minus one since tile position start from zero
       tileScreenPosY += 24.0f;
    
    if((tilePosY > 0 && tilePosY != (numberOfRows - 1)) && (tilePosX == (numberOfColumns - 1) || tilePosX != 0))
      tileScreenPosX += 24.0f;*/

    type = _type;
}

void GameWorldResources::initialiseGameBorder(int tilePosX, int tilePosY, const ObjectType _type)
{
    tileScreenPosX = tilePosX * 32.0f;
    tileScreenPosY = tilePosY * 32.0f;
    
    auto numberOfRows = game_world.getNumberOfRows();
    auto numberOfColumns = game_world.getNumberOfColumns();
    if (tilePosY == (numberOfRows - 1) && (tilePosX > 0 && tilePosX < (numberOfColumns - 1)))//minus one since tile position start from zero
       tileScreenPosY += 24.0f;
    
    if((tilePosY > 0 && tilePosY != (numberOfRows - 1)) && (tilePosX == (numberOfColumns - 1) || tilePosX != 0))
      tileScreenPosX += 24.0f;

    type = _type;
}

void GameWorldResources::setMazeWalls(std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures,
std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
    auto maze = game_world.getGameMap();
    int tilePosY = 0;
    int tilePosX = 0;
    for (const auto& row : maze)
    {
        for (const auto tile : row)
        {
            processTileTexture(maze_textures,maze_resources,tile, tilePosX, tilePosY);
            tilePosX++;
        }
        tilePosY++;
        tilePosX = 0;
    }
}

void GameWorldResources::processTileTexture(std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures,
std::vector<std::shared_ptr<GameWorldResources>>& maze_resources,const std::string element,const int tilePosX,const int tilePosY)
{
    float xOffset = 0;
    float yOffset = 0;
    if (element == "10") //Vertical wall on the left
    {
        xOffset = 0;
        yOffset = 0;
        verticalWall(tilePosX, tilePosY, xOffset, yOffset,maze_textures,maze_resources);
    }

    if (element == "01")//Vertical wall on the right
    {
        xOffset = (5/6.0f);//This vertical wall should be at the border of the maze
        yOffset = 0;
        verticalWall(tilePosX, tilePosY, xOffset, yOffset, maze_textures,maze_resources);
    }

    if (element == "-")
    {
        xOffset = 0;
        yOffset = 0;
        horizontalWall(tilePosX,tilePosY,xOffset,yOffset,maze_textures,maze_resources);
    }

    if (element == "┐")
    {
        xOffset = 0;
        yOffset = 0;
        //topRightCorner(tilePosX,tilePosY,xOffset,yOffset);
    }

    if (element == "┌")
    {
        xOffset = 0;
        yOffset = 0;
       // topLeftCorner(tilePosX,tilePosY,xOffset,yOffset);
    }
}

void GameWorldResources::loadTextures()
{
}

void GameWorldResources::verticalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/verticalWallPiece.png");
  maze_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall,xOffset,yOffset);
  maze_resources.push_back(tile_property);
}


void GameWorldResources::horizontalWall(int tilePosX, int tilePosY, const float xOffset,const float yOffset,
std::vector<std::shared_ptr<raylib::Texture2D>>& maze_textures, std::vector<std::shared_ptr<GameWorldResources>>& maze_resources)
{
  auto texture = std::make_shared<raylib::Texture2D>();
  texture->Load("../resources/horizontalWallPiece.png");
  maze_textures.push_back(texture);
  auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall,xOffset,yOffset);
  maze_resources.push_back(tile_property);
}

std::tuple<float, float> GameWorldResources::getTileScreenPosition() const
{
    return {tileScreenPosX, tileScreenPosY};
}

ObjectType GameWorldResources::getObjectType() const
{
    return type;
}