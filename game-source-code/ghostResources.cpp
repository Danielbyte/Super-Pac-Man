#include "ghostResources.h"

GhostResources::GhostResources(){}

void GhostResources::initialiseTextures(std::vector<std::shared_ptr<Ghost>>& ghosts, std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures)
{
    auto blueT = std::make_shared<raylib::Texture2D>();
    blueT->Load("../resources/blue1.png");
    auto redT = std::make_shared<raylib::Texture2D>();
    redT->Load("../resources/red1.png");
    auto pinkT = std::make_shared<raylib::Texture2D>();
    pinkT->Load("../resources/pink1.png");
    auto orangeT = std::make_shared<raylib::Texture2D>();
    orangeT->Load("../resources/orange1.png");
    for (auto& ghost : ghosts)
    {
        auto ghostType = ghost->getType();
        switch(ghostType)
        {
            case Type::Blue:
            ghost_textures.push_back(blueT);
            break;
            case Type::Orange:
            ghost_textures.push_back(orangeT);
            break;
            case Type::Red:
            ghost_textures.push_back(redT);
            break;
            case Type::Pink:
            ghost_textures.push_back(pinkT);
            break;
            default:
            break;
        }
    }
}

void GhostResources::updateTextures(std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures,
    std::vector<std::shared_ptr<Ghost>>& ghosts, std::shared_ptr<raylib::Texture2D>& frightenedT,
    std::shared_ptr<raylib::Texture2D>& pinkT, std::shared_ptr<raylib::Texture2D>& orangeT,
    std::shared_ptr<raylib::Texture2D>& redT, std::shared_ptr<raylib::Texture2D>& blueT)
{
    auto ghost_texture = ghost_textures.begin();
    for(auto& ghost : ghosts)
    {
        auto ghostMode = ghost->getMode();
        auto type = ghost->getType();
        switch (ghostMode)
        {
        case Mode::Frightened:
             (*ghost_texture) = frightenedT;
            break;
        case Mode::Chase:
        case Mode::Scatter:
             assignTextures(*ghost_texture,pinkT,orangeT,redT,blueT,type);
             break;
        default:
            break;
        }

        ++ghost_texture;
    }
}

void GhostResources::assignTextures(std::shared_ptr<raylib::Texture2D>& ghost_texture,std::shared_ptr<raylib::Texture2D>& pinkT, std::shared_ptr<raylib::Texture2D>& orangeT,
    std::shared_ptr<raylib::Texture2D>& redT, std::shared_ptr<raylib::Texture2D>& blueT, Type type)
{
    switch (type)
    {
    case Type::Red:
        ghost_texture = redT;
        break;
    case Type::Blue:
         ghost_texture = blueT;
        break;
    case Type::Orange:
         ghost_texture = orangeT;
         break;
    case Type::Pink:
         ghost_texture = pinkT;
         break;
    default:
        break;
    }
}