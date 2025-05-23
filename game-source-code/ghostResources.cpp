#include "ghostResources.h"

GhostResources::GhostResources():
isFlattened{false}
{}

void GhostResources::initialiseTextures(std::vector<std::shared_ptr<Ghost>>& ghosts, std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures)
{
    blueT->Load("../resources/blue1.png");
    redT->Load("../resources/red1.png");
    pinkT->Load("../resources/pink1.png");
    orangeT->Load("../resources/orange1.png");
    frightenedT->Load("../resources/frightened.png");

    flattenedblueT->Load("../resources/blue2_flattened.png");
    flattenedRedT->Load("../resources/red2_flattened.png");
    flattenedPinkT->Load("../resources/pink2_flattened.png");
    flattenedOrangeT->Load("../resources/orange2_flattened.png");
    flattenedFrightenedT->Load("../resources/frightened_flattened.png");

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

void GhostResources::updateTextures(std::vector<std::shared_ptr<raylib::Texture2D>>& ghost_textures, std::vector<std::shared_ptr<Ghost>>& ghosts, bool flattened)
{
    isFlattened = flattened;
    auto ghost_texture = ghost_textures.begin();
    for(auto& ghost : ghosts)
    {
        auto ghostMode = ghost->getMode();
        auto type = ghost->getType();
        switch (ghostMode)
        {
        case Mode::Frightened:
             (*ghost_texture) = frightenedT;
             if(isFlattened) 
               (*ghost_texture) = flattenedFrightenedT;
            break;
        case Mode::Chase:
        case Mode::Scatter:
        case Mode::Initial:
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
        if(isFlattened)
           ghost_texture = flattenedRedT;
        break;
    case Type::Blue:
         ghost_texture = blueT;
         if(isFlattened)
            ghost_texture = flattenedblueT;
        break;
    case Type::Orange:
         ghost_texture = orangeT;
         if (isFlattened)
            ghost_texture = flattenedOrangeT;
         break;
    case Type::Pink:
         ghost_texture = pinkT;
         if (isFlattened)
            ghost_texture = flattenedPinkT;
         break;
    default:
        break;
    }
}