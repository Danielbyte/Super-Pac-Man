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