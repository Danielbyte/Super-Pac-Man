#include "ghostResources.h"

GhostResources::GhostResources(){}

void GhostResources::initialiseTextures(std::vector<std::shared_ptr<Ghost>>& ghosts, std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures)
{
    blueT->Load("../resources/blue1.png");
    redT->Load("../resources/red1.png");
    pinkT->Load("../resources/pink1.png");
    orangeT->Load("../resources/orange1.png");
    frightenedT->Load("../resources/frightened.png");

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

void GhostResources::updateTextures(std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures, std::vector<std::shared_ptr<Ghost>>& ghosts)
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
             assignTextures(*ghost_texture,type);
             break;
        default:
            break;
        }

        ++ghost_texture;
    }
}

void GhostResources::assignTextures(std::shared_ptr<raylib::Texture2D>& ghost_texture, Type type)
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