#ifndef GHOSTRESOURCES_H
#define GHOSTRESOURCES_H
#include "raylib-cpp.hpp"
#include "ghost.h"
#include "ghostManager.h"

using namespace raylib;
class GhostResources
{
private:
    bool isFlattened; 
    GhostManager ghost_manager;
    void assignTextures(std::shared_ptr<raylib::Texture2D>& ghost_texture,Type type);

    std::shared_ptr<raylib::Texture2D> frightenedT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> flattenedFrightenedT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> pinkT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> flattenedPinkT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> orangeT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> flattenedOrangeT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> redT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> flattenedRedT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> blueT = std::make_shared<raylib::Texture2D>();
    std::shared_ptr<raylib::Texture2D> flattenedblueT = std::make_shared<raylib::Texture2D>();
public:
    GhostResources();
    void initialiseTextures(std::vector<std::shared_ptr<Ghost>>& ghosts, std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures);
    void updateTextures(std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures, std::vector<std::shared_ptr<Ghost>>& ghosts,bool flattened);
};
#endif