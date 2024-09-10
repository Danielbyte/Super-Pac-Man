#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <raylib-cpp.hpp>
#include "displayManager.h"

TEST_CASE("TEST IF GAME MAP IS INITIALLY EMPTY")
{
    auto game_world = std::make_shared<GameWorld>();

    auto maze = game_world->getGameMap();
    auto expected_map_size = 0;
    auto actual_map_size = maze.size();
    CHECK_EQ(expected_map_size,actual_map_size);
}

TEST_CASE("TEST IF GAME MAP IS CAN BE INITIALISED WITHIN GAME LOOP")
{
    auto game_world = std::make_shared<GameWorld>();
    auto maze = game_world->getGameMap();
    //Map should be empty since it has not been initialised
    CHECK(maze.empty() == true);

    game_world->loadMapFromFile();
    maze = game_world->getGameMap();
    CHECK_FALSE(maze.empty());//maze should not be empty after initialisation
}

TEST_CASE("TEST IF GAME MAP IS ACCURATELY LOADED FROM FILE")
{
    //In this case, the loaded map from txt file is known
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    auto maze = game_world->getGameMap();
    char expected_char = '-'; //at point (0,0), this is the expected character
    char actual_char = maze[0][0];
    CHECK_EQ(expected_char,actual_char);

    //Char somewhere at the center of maze
    expected_char = '0';
    actual_char = maze[12][10];
    CHECK_EQ(expected_char,actual_char);
}

TEST_CASE("TEST IF PLAYER IS CAN SPAWN AT THE RIGHT POSITION")
{
    auto player = std::make_unique<Player>();
    auto expectedXPlayerInitPos = 376.0f;
    auto expectedYPlayerInitPos = 326.0f;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    
    CHECK_EQ(expectedXPlayerInitPos, actualXpos);
    CHECK_EQ(expectedYPlayerInitPos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE LEFT")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto player_speed = 2.0f;

    bool movingLeft = true,movingRight = false,movingUp = false, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    auto expectedXpos = InitXpos - player_speed;
    auto expectedYpos = InitYpos;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE RIGHT")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto player_speed = 2.0f;

    bool movingLeft = false,movingRight = true,movingUp = false, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    auto expectedXpos = InitXpos + player_speed;
    auto expectedYpos = InitYpos;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE UP")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto player_speed = 2.0f;

    bool movingLeft = false,movingRight = false,movingUp = true, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    auto expectedYpos = InitYpos - player_speed;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE DOWN")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto player_speed = 2.0f;

    bool movingLeft = false,movingRight = false,movingUp = false, movingDown = true;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    auto expectedYpos = InitYpos + player_speed;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON LOWER BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto window_height = 704;
    auto player_dimension = 32;
    auto wall_width = 8.0f;
    auto lower_boundary = window_height - (player_dimension + wall_width);

    bool movingLeft = false,movingRight = false,movingUp = false, movingDown = true;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    }
    
    auto expectedYpos = lower_boundary;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON UPPER BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto window_height = 704;
    auto player_dimension = 32;
    auto wall_width = 8.0f;
    auto lower_boundary = wall_width;

    bool movingLeft = false,movingRight = false,movingUp = true, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    }
    
    auto expectedYpos = lower_boundary;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}