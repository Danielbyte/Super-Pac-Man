#ifndef PLAYERRESOURCES
#define PLAYERRESOURCES
#include "raylib-cpp.hpp"
#include "player.h"

using namespace raylib;

class PlayerResources
{
public:
    PlayerResources();
    void initialiseTexture();
    void updateTexture(std::shared_ptr<Player>& player, std::shared_ptr<raylib::Texture2D>& player_texture,const bool buttoPressed);
private:
    std::vector<std::shared_ptr<raylib::Texture2D>>rightTexturesNM = {};//Texture for player moving to the right (NM->normal mode)
    std::vector<std::shared_ptr<raylib::Texture2D>>leftTexturesNM = {};//Texture for player moving to the left(NM->normal mode)
    std::vector<std::shared_ptr<raylib::Texture2D>>upTexturesNM = {};//Texture for player moving up(NM->normal mode)
    std::vector<std::shared_ptr<raylib::Texture2D>>downTexturesNM = {};//Texture for player moving down(NM->normal mode)

    std::vector<std::shared_ptr<raylib::Texture2D>>rightTexturesSP = {};//Texture for player moving to the right(SP->Super pacman)
    std::vector<std::shared_ptr<raylib::Texture2D>>leftTexturesSP = {};//Texture for player moving to the left(SP->Super pacman)
    std::vector<std::shared_ptr<raylib::Texture2D>>upTexturesSP = {};//Texture for player moving up(SP->Super pacman)
    std::vector<std::shared_ptr<raylib::Texture2D>>downTexturesSP = {};//Texture for player moving down(SP->Super pacman)
};
#endif