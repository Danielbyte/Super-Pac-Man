#include "playerResources.h"

PlayerResources::PlayerResources()
{
    loadTextures();
}

void PlayerResources::updateTexture(std::shared_ptr<Player>& player, std::shared_ptr<raylib::Texture2D>& player_texture,const bool buttoPressed)
{
    auto direction = player->getPlayerDirection();
    auto isSuperPacman = player->isSuperPacman();

    if(!isSuperPacman)
    {
        switch (direction)
        {
        case Direction::Right:
            /* code */
            break;
        
        default:
            break;
        }
    }
}

void PlayerResources::loadTextures()
{
    //NORMAL MODE
    auto pacmanRight1_T = std::make_shared<raylib::Texture2D>();
    pacmanRight1_T->Load("../resources/pacmanRight1.png");
    rightTexturesNM.push_back(pacmanRight1_T);

    //Left
    auto pacmanLeft1_T = std::make_shared<raylib::Texture2D>();
    pacmanLeft1_T->Load("../resources/pacmanLeft1.png");
    leftTexturesNM.push_back(pacmanLeft1_T);

    //Down
    auto pacmanDown1_T = std::make_shared<raylib::Texture2D>();
    pacmanDown1_T->Load("../resources/pacmanDown1.png");
    downTexturesNM.push_back(pacmanDown1_T);

    //Up
    auto pacmanUp1_T = std::make_shared<raylib::Texture2D>();
    pacmanUp1_T->Load("../resources/pacmanUp1.png");
    upTexturesNM.push_back(pacmanUp1_T);

     //SUPER-PACMAN MODE
    //To the right
    auto SuperpacmanRight1_T = std::make_shared<raylib::Texture2D>();
    SuperpacmanRight1_T->Load("../resources/SuperpacmanRight1.png");
    rightTexturesSP.push_back(SuperpacmanRight1_T);

    //To the left
    auto SuperpacmanLeft1_T = std::make_shared<raylib::Texture2D>();
    SuperpacmanLeft1_T->Load("../resources/SuperpacmanLeft1.png");
    leftTexturesSP.push_back(SuperpacmanLeft1_T);

    //Moving down
    auto SuperpacmanDown1_T = std::make_shared<raylib::Texture2D>();
    SuperpacmanDown1_T->Load("../resources/SuperpacmanDown1.png");
    downTexturesSP.push_back(SuperpacmanDown1_T);

    //Moving up
    auto SuperpacmanUp1_T = std::make_shared<raylib::Texture2D>();
    SuperpacmanUp1_T->Load("../resources/SuperpacmanUp1.png");
    upTexturesSP.push_back(SuperpacmanUp1_T);
}

void updateLeftTextures(std::shared_ptr<raylib::Texture2D>& playerTexture, bool isSuperPacman)
{

}

void updateRightTextures(std::shared_ptr<raylib::Texture2D>& playerTexture, bool isSuperPacman)
{

}

void updateUpTextures(std::shared_ptr<raylib::Texture2D>& playerTexture, bool isSuperPacman)
{

}

void updateDownTextures(std::shared_ptr<raylib::Texture2D>& playerTexture, bool isSuperPacman)
{
    
}