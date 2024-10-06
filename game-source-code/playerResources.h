#ifndef PLAYERRESOURCES
#define PLAYERRESOURCES
#include "raylib-cpp.hpp"
#include "player.h"

using namespace raylib;

class PlayerResources
{
public:
    PlayerResources();
    void updateTexture(std::shared_ptr<Player>& player, std::shared_ptr<raylib::Texture2D>& player_texture);
private:
    std::vector<std::shared_ptr<raylib::Texture2D>>playerTextures = {};//vector to load player textures
};
#endif