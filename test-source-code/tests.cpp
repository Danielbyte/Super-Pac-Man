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