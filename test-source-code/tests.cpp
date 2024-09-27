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
    std::string expected_char = "┌"; //at point (0,0), this is the expected character
    std::string actual_char = maze[0][0];
    CHECK_EQ(expected_char,actual_char);

    //Char somewhere at the center of maze
    expected_char = "||";
    actual_char = maze[1][1];
    CHECK_EQ(expected_char,actual_char);
}

//STOP WATCH TEST CASES
TEST_CASE("TEST IF TIMER INCREMENTS WHEN TIMING A GAME EVENT")
{
    StopWatch watch;
    auto time1 = watch.elapsedTime();

    for (int i = 0; i < 100; ++i)
    {
        //Pass some time
    }
    auto time2 = watch.elapsedTime();
    CHECK_GT(time2,time1);//time 2 should be greater than time1
}

TEST_CASE("TEST IF TIMER IS SUCCESSFULLY RESTARTED")
{
    StopWatch watch;
    auto time1 = watch.elapsedTime();

    for (int i = 0; i < 100; ++i)
    {
        //Pass some time
    }
    auto time2 = watch.elapsedTime();
    watch.restartTimer();
    auto time3 = watch.elapsedTime();
    CHECK_LE(time3,time1);//time 3 should be lesser than time2
}

TEST_CASE("TEST IF PLAYER IS CAN SPAWN AT THE RIGHT POSITION")
{
    auto player = std::make_unique<Player>();
    auto expectedXPlayerInitPos = 400.0f;
    auto expectedYPlayerInitPos = 326.0f;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    
    CHECK_EQ(expectedXPlayerInitPos, actualXpos);
    CHECK_EQ(expectedYPlayerInitPos,actualYpos);
}
/*
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

TEST_CASE("TEST IF PLAYER IS BOUNDED ON LEFT BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto window_height = 704;
    auto player_dimension = 32;
    auto wall_width = 8.0f;
    auto left_boundary = wall_width;

    bool movingLeft = true,movingRight = false,movingUp = false, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    }
    
    auto expectedYpos = InitYpos;
    auto expectedXpos = left_boundary;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON RIGHT BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto window_width = 800;
    auto player_dimension = 32;
    auto wall_width = 8.0f;
    auto right_boundary = window_width - (player_dimension + wall_width);

    bool movingLeft = false,movingRight = true,movingUp = false, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources);
    }
    
    auto expectedYpos = InitYpos;
    auto expectedXpos = right_boundary;
    auto [actualXpos, actualYpos] = player->getPlayerPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF COLLISION IS DETECTED BETWEEN WALL AND PLAYER")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    auto collisions_manager = CollisionsManager{};
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>maze = {};

    //Place wall two tiles above player 
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto tilePosX = static_cast<int>(InitXpos/32);
    auto tilePosY = static_cast<int>((InitYpos - 64.0f)/32);
    auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall);
    maze.push_back(tile_property);
    player->setPlayerPosition(tilePosX * 32.0f,tilePosY * 32.0f);//Place player such that it collides with the wall

    auto [finalXpos, finalYpos] = player->getPlayerPosition();    
    auto isCollided = collisions_manager.playerWallCollisions(maze,finalXpos, finalYpos);
    
    //A collision should have been detected
    CHECK_EQ(isCollided,true);
}

TEST_CASE("TEST IF PLAYER CANNOT MOVE PAST WALL")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    auto collisions_manager = CollisionsManager{};
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>maze = {};

    //Place wall two tiles above player 
    auto [InitXpos, InitYpos] = player->getPlayerPosition();
    auto tilePosX = static_cast<int>(InitXpos/32);
    auto tilePosY = static_cast<int>((InitYpos - 64.0f)/32);
    auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::HorizontalWall);

    maze.push_back(tile_property);
    auto wall_bottom = tilePosY * 32.0f - 8.0f;
    player->setPlayerPosition(tilePosX * 32.0f,wall_bottom);//Place player such that it collides with the wall
    bool movingLeft = false,movingRight = false,movingUp = true, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move past a wall
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, maze);
    }

    auto [finalXpos, finalYpos] = player->getPlayerPosition();
    
    CHECK(finalYpos == wall_bottom);
    CHECK_EQ(finalXpos,tilePosX * 32);
}*/
