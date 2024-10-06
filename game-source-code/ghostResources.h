#ifndef GHOSTRESOURCES_H
#define GHOSTRESOURCES_H
#include "raylib-cpp.hpp"
#include "ghost.h"
#include "ghostManager.h"

using namespace raylib;
class GhostResources
{
private:
    GhostManager ghost_manager;
    void assignTextures(std::shared_ptr<raylib::Texture2D>& ghost_texture,
    std::shared_ptr<raylib::Texture2D>& pinkT, std::shared_ptr<raylib::Texture2D>& oarngeT,
    std::shared_ptr<raylib::Texture2D>& redT, std::shared_ptr<raylib::Texture2D>& blueT, Type type);
public:
    GhostResources();
    void initialiseTextures(std::vector<std::shared_ptr<Ghost>>& ghosts, std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures);
    void updateTextures(std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures, std::vector<std::shared_ptr<Ghost>>& ghosts,
    std::shared_ptr<raylib::Texture2D>& frightenedT,std::shared_ptr<raylib::Texture2D>& pinkT, std::shared_ptr<raylib::Texture2D>& orangeT,
    std::shared_ptr<raylib::Texture2D>& redT, std::shared_ptr<raylib::Texture2D>& blueT);
};
#endif