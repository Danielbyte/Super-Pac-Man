#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <raylib-cpp.hpp>
#include "displayManager.h"
#include "gameWorldResources.h"
#include "ghost.h"
#include "scoreManager.h"
#include <fstream>

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
/*TEST_CASE("TEST IF TIMER INCREMENTS WHEN TIMING A GAME EVENT")
{
    StopWatch watch;
    auto time1 = watch.elapsedTime();

    for (int i = 0; i < 100; ++i)
    {
        //Pass some time
    }
    auto time2 = watch.elapsedTime();
    CHECK_GT(time2,time1);//time 2 should be greater than time1
}*/

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
    auto [actualXpos, actualYpos] = player->getPosition();
    
    CHECK_EQ(expectedXPlayerInitPos, actualXpos);
    CHECK_EQ(expectedYPlayerInitPos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE LEFT")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPosition();
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};

    bool movingLeft = true,movingRight = false,movingUp = false, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources, locks, dt);
    auto expectedXpos = InitXpos - player_speed * dt;
    auto expectedYpos = InitYpos;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE RIGHT")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPosition();
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};

    bool movingLeft = false,movingRight = true,movingUp = false, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks,dt);
    auto expectedXpos = InitXpos + player_speed * dt;
    auto expectedYpos = InitYpos;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE UP")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPosition();
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};

    bool movingLeft = false,movingRight = false,movingUp = true, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks, dt);
    auto expectedYpos = InitYpos - player_speed * dt;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER CAN MOVE DOWN")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPosition();
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};

    bool movingLeft = false,movingRight = false,movingUp = false, movingDown = true;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources, locks, dt);
    auto expectedYpos = InitYpos + player_speed * dt;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON LOWER BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();

    //Place player a level higher than lower boundary (To avoid wall collisions)
    player->setPosition(96.0f, 543.0f);
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources = {};
    auto [InitXpos, InitYpos] = player->getPosition();
    auto window_height = 576;
    auto player_dimension = 25;
    auto wall_width = 8.0f;
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};
    auto lower_boundary = window_height - (player_dimension + wall_width);

    bool movingLeft = false,movingRight = false,movingUp = false, movingDown = true;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks,dt);
    }
    
    auto expectedYpos = lower_boundary;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON UPPER BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    player->setPosition(0, 8.0f);//place player at upper margin
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources = {};
    auto [InitXpos, InitYpos] = player->getPosition();
    auto window_height = 576;
    auto player_dimension = 25;
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};
    auto wall_width = 8.0f;
    auto lower_boundary = wall_width;

    bool movingLeft = false,movingRight = false,movingUp = true, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks,dt);
    }
    
    auto expectedYpos = lower_boundary;
    auto expectedXpos = InitXpos;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON LEFT BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    player->setPosition(8,0);//place player on left margin
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPosition();
    auto window_height = 576;
    auto player_dimension = 25;
    auto wall_width = 8.0f;
    auto left_boundary = wall_width;
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};

    bool movingLeft = true,movingRight = false,movingUp = false, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks, dt);
    }
    
    auto expectedYpos = InitYpos;
    auto expectedXpos = left_boundary;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER IS BOUNDED ON RIGHT BOUND OF SCREEN")
{
    auto player = std::make_unique<Player>();
    player->setPosition(495, 0);//Place player on right boundary
    auto game_world = std::make_unique<GameWorld>();
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    auto [InitXpos, InitYpos] = player->getPosition();
    auto window_width = 528;
    auto player_dimension = 25;
    auto wall_width = 8.0f;
    auto right_boundary = window_width - (player_dimension + wall_width);
    auto player_speed = 102.0f;
    float dt = 1/60;
    std::vector<std::shared_ptr<Lock>>locks = {};

    bool movingLeft = false,movingRight = true,movingUp = false, movingDown = false;
    for (int i = 0; i < 500; i++)
    {
        //Simulate the player attempting to move out of bounds
        player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources, locks, dt);
    }
    
    auto expectedYpos = InitYpos;
    auto expectedXpos = right_boundary;
    auto [actualXpos, actualYpos] = player->getPosition();
    CHECK_EQ(expectedXpos,actualXpos);
    CHECK_EQ(expectedYpos,actualYpos);
}

TEST_CASE("TEST IF PLAYER POSITION CAN BE SET AND RETRIEVED")
{
    auto player = std::make_unique<Player>();
    float xTestPos = 200.0f;
    float yTestPos = 48.0f;
    player->setPosition(xTestPos, yTestPos);
    auto[xPos, yPos] = player->getPosition();//Retrieve position
    CHECK_EQ(xTestPos,xPos);
    CHECK_EQ(yTestPos,yPos);
}

TEST_CASE("TEST IF PLAYER DIRECTION CAN BE RETRIEVED")
{
    auto player = std::make_unique<Player>();
    
    auto actualDirection = player->getDirection();
    auto expectedDirection = Direction::Right;//player initially facing right
    CHECK_EQ(actualDirection,expectedDirection);
}

TEST_CASE("TEST IF PLAYER DIRECTION CAN BE UPDATED TO THE LEFT")
{
    auto player = std::make_unique<Player>();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    std::vector<std::shared_ptr<Lock>>locks = {};
    auto dt = 1/60.0f;

    bool movingLeft = true,movingRight = false,movingUp = false, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks, dt);
    
    auto actualDirection = player->getDirection();
    auto expectedDirection = Direction::Left;//player initially facing right
    CHECK_EQ(actualDirection,expectedDirection);
}

TEST_CASE("TEST IF PLAYER DIRECTION CAN BE UPDATED DOWNWARDS")
{
    auto player = std::make_unique<Player>();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    std::vector<std::shared_ptr<Lock>>locks = {};
    auto dt = 1/60.0f;

    bool movingLeft = false,movingRight = false,movingUp = false, movingDown = true;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks, dt);
    
    auto actualDirection = player->getDirection();
    auto expectedDirection = Direction::Down;//player initially facing right
    CHECK_EQ(actualDirection,expectedDirection);
}

TEST_CASE("TEST IF PLAYER DIRECTION CAN BE UPDATED UPWARDS")
{
    auto player = std::make_unique<Player>();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    std::vector<std::shared_ptr<Lock>>locks = {};
    auto dt = 1/60.0f;

    bool movingLeft = false,movingRight = false,movingUp = true, movingDown = false;
    player->movePlayer(movingRight,movingLeft,movingDown,movingUp, game_resources,locks, dt);
    
    auto actualDirection = player->getDirection();
    auto expectedDirection = Direction::Up;//player initially facing right
    CHECK_EQ(actualDirection,expectedDirection);
}

TEST_CASE("TEST IF PLAYER STATE UPDATE WHEN PLAYER CONSUMES POWER PELLET")
{
    auto player = std::make_unique<Player>();
    auto PowerPelletMode = player->consumedPowerPellet();
    CHECK_FALSE(PowerPelletMode);
    player->inPowerPelletMode();//set player to consume power pellet
    PowerPelletMode = player->consumedPowerPellet();
    CHECK_EQ(PowerPelletMode, true);
}

TEST_CASE("TEST IF PLAYER STATE UPDATE WHEN PLAYER CONSUMES SUPER PELLET")
{
    auto player = std::make_unique<Player>();
    auto superPacManMode = player->isSuperPacman();
    CHECK_FALSE(superPacManMode);
    player->setToSuperPacmanMode();
    superPacManMode = player->isSuperPacman();
    CHECK_EQ(superPacManMode, true);
}

TEST_CASE("TEST IF SUPER-PACMAN MODE CAN BE TOGGLED OFF")
{
    auto player = std::make_unique<Player>();
    auto superPacManMode = player->isSuperPacman();
    CHECK_FALSE(superPacManMode);
    player->setToSuperPacmanMode();
    superPacManMode = player->isSuperPacman();
    CHECK_EQ(superPacManMode, true);
    player->toggleOffSuperPacmanMode();
    superPacManMode = player->isSuperPacman();
    CHECK_FALSE(superPacManMode);
}

TEST_CASE("TEST IF POWER PELLET MODE CAN BE TOGGLED OFF")
{
    auto player = std::make_unique<Player>();
    auto powerPelletMode = player->consumedPowerPellet();
    CHECK_FALSE(powerPelletMode);
    player->inPowerPelletMode();
    powerPelletMode = player->consumedPowerPellet();
    CHECK_EQ(powerPelletMode, true);
    player->toggleOffPowerPellet();
    powerPelletMode = player->consumedPowerPellet();
    CHECK_FALSE(powerPelletMode);
}

TEST_CASE("TEST IF COLLISION IS DETECTED BETWEEN WALL AND PLAYER")
{
    auto player = std::make_unique<Player>();
    auto game_world = std::make_unique<GameWorld>();
    auto collisions_manager = CollisionsManager{};
    game_world->loadMapFromFile();
    std::vector<std::shared_ptr<GameWorldResources>>maze = {};

    //Place wall two tiles above player 
    auto [InitXpos, InitYpos] = player->getPosition();
    auto tilePosX = static_cast<int>(InitXpos/32);
    auto tilePosY = static_cast<int>((InitYpos - 64.0f)/32);
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    auto tile_property = std::make_shared<GameWorldResources>(tilePosX, tilePosY, ObjectType::VerticalWall,xOffset,yOffset);
    maze.push_back(tile_property);

    maze.push_back(tile_property);
    player->setPosition(tilePosX * 48.0f,tilePosY * 48.0f);//Place player such that it collides with the wall

    auto [finalXpos, finalYpos] = player->getPosition();    
    auto isCollided = collisions_manager.playerWallCollisions(maze,finalXpos, finalYpos);
    
    //A collision should have been detected
    CHECK_EQ(isCollided,true);
}

TEST_CASE("COLLISION BETWEEN GHOST AND PLAYER")
{
    auto ghost = std::make_unique<Ghost>();
    CollisionsManager manage_collisions;
    ghost->setPosition(0.0f, 0.0f);
    auto [ghostX, ghostY] = ghost->getPosition();
    auto player = std::make_unique<Player>();
    player->setPosition(0.0f, 0.0f);//Move player to collide with ghost
    auto[playerX, playerY] = player->getPosition();
    auto isCollided = manage_collisions.playerGhostCollisions(ghostX, ghostY,playerX, playerY);

    CHECK_EQ(isCollided, true);
}

TEST_CASE("GHOST MODE CAN BE SET AND RETRIEVED")
{
    auto ghost = std::make_unique<Ghost>();
    ghost->setMode(Mode::Scatter);
    auto mode = ghost->getMode();
    CHECK_EQ(mode, Mode::Scatter);
}

TEST_CASE("GHOST TYPE CAN BE SET")
{
    auto ghost = std::make_unique<Ghost>();
    ghost->setType(Type::Blue);
    auto ghostType = ghost->getType();
    CHECK_EQ(ghostType, Type::Blue);
}

/*TEST_CASE("GHOST MOVEMENT IS UPDATED")
{
    auto ghost = std::make_unique<Ghost>();
    auto player = std::make_unique<Player>();
    std::vector<std::shared_ptr<GameWorldResources>>game_resources;
    std::vector<std::shared_ptr<Lock>>locks = {};
    auto dt = 1/60.0f;
    ghost->update(game_resources,locks,dt);
}*/

// Fixture for Ghost Movement Tests
struct GhostMovementTest {
    GhostMovementTest() {
        // Initialize Ghost
        ghost = std::make_shared<Ghost>();
        ghost->setPosition(initialX, initialY);
        ghost->setType(Type::Red);
        ghost->assignCorner(480.0f, 240.0f);  // Updated to consider only non-negative coordinates
        ghost->setMode(Mode::Scatter);

        // Set up environment (mocked maze and locks)
        locks = {std::make_shared<Lock>(), std::make_shared<Lock>()};
        maze = {std::make_shared<GameWorldResources>(), std::make_shared<GameWorldResources>()};
    }

    std::shared_ptr<Ghost> ghost;
    std::vector<std::shared_ptr<Lock>> locks;
    std::vector<std::shared_ptr<GameWorldResources>> maze;
    const float initialX = 249.0f;
    const float initialY = 105.0f;
};


TEST_CASE("Test Ghost Initial Position") {
    auto ghost = std::make_unique<Ghost>();
    ghost->setPosition(249.0f, 105.0f);
    auto [xPos, yPos] = ghost->getPosition();
    CHECK_EQ(xPos, 249.0f);
    CHECK_EQ(yPos, 105.0f);
}


/*TEST_CASE("Test Ghost Moves to Scatter Corner") {
    auto ghost = std::make_unique<Ghost>();
    ghost->assignCorner(480.0f, 240.0f);  // Updated to valid non-negative coordinates
    ghost->moveToCorner();
    auto [xPos, yPos] = ghost->getPosition();  // Get current position after movement
    CHECK_EQ(xPos, 480.0f);
    CHECK_EQ(yPos, 240.0f);
}*/

TEST_CASE("Test Ghost Mode Switching to Chase") {
    auto ghost = std::make_unique<Ghost>();
    ghost->setMode(Mode::Chase);
    CHECK_EQ(ghost->getMode(), Mode::Chase);
}

TEST_CASE("Test Ghost Mode Switching to Frightened") {
    auto ghost = std::make_unique<Ghost>();
    ghost->setMode(Mode::Frightened);
    CHECK_EQ(ghost->getMode(), Mode::Frightened);
}


TEST_CASE("Test Ghost Respawn Logic") {
    auto ghost = std::make_unique<Ghost>();
    ghost->respawn();
    auto [xPos, yPos] = ghost->getPosition();
    CHECK_EQ(xPos, 249.0f);
    CHECK_EQ(yPos, 105.0f);
    CHECK_EQ(ghost->getMode(), Mode::Scatter);
}

TEST_CASE("Test Ghost Just Respawned State") {
    auto ghost = std::make_unique<Ghost>();
    ghost->respawn();
    CHECK(ghost->isJustRespawned() == true);
}

TEST_CASE("Test Ghost Mode Switching on Player Power Pellet Consumption") {
    auto ghost = std::make_unique<Ghost>();
    ghost->setMode(Mode::Chase);
    ghost->setMode(Mode::Frightened);
    CHECK_EQ(ghost->getMode(), Mode::Frightened);
}

TEST_CASE("Test Ghost Can Use Door After Respawn") {
    auto ghost = std::make_unique<Ghost>();
    ghost->respawn();
    CHECK(ghost->getCanUseDoor() == true);
}

//////////////////////TEST THE SCORE//////////
TEST_CASE("Test Initial Score Values") {
    ScoreManager scoreManager;
    CHECK_EQ(scoreManager.getCurrentScore(), 0);
    CHECK_GE(scoreManager.getHighScore(), 0);
}

TEST_CASE("Test Update Current Score - Fruit") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::Fruit);
    CHECK_EQ(scoreManager.getCurrentScore(), 10);
}

TEST_CASE("Test Update Current Score - Key") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::Key);
    CHECK_EQ(scoreManager.getCurrentScore(), 50);
}

TEST_CASE("Test Update Current Score - SuperPellet") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::SuperPellet);
    CHECK_EQ(scoreManager.getCurrentScore(), 100);
}

TEST_CASE("Test Update Current Score - PowerPellet") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::PowerPellet);
    CHECK_EQ(scoreManager.getCurrentScore(), 500);
}

TEST_CASE("Test Update Current Score - FrightenedGhost") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::FrightenedGhost);
    CHECK_EQ(scoreManager.getCurrentScore(), 200);
}

TEST_CASE("Test Update Current Score - MazeMatchBonus") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::MazeMatchBonus);
    CHECK_EQ(scoreManager.getCurrentScore(), 5000);
}

TEST_CASE("Test Update Current Score - NoMazeMatchBonus") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::OtherMatchBonus);
    CHECK_EQ(scoreManager.getCurrentScore(), 2000);
}

TEST_CASE("Test Update High Score") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::PowerPellet);
    scoreManager.updateHighScore(scoreManager.getCurrentScore());
    CHECK_GE(scoreManager.getHighScore(), 500);
}


TEST_CASE("Test Negative Score Not Allowed Exception") {
    ScoreManager scoreManager;
    CHECK_THROWS_AS(scoreManager.updateHighScore(-100), NegativeScoreNotAllowed);
}

TEST_CASE("Test Multiple Score Updates") {
    ScoreManager scoreManager;
    scoreManager.updateCurrentScore(ScoreType::Fruit);
    scoreManager.updateCurrentScore(ScoreType::Key);
    scoreManager.updateCurrentScore(ScoreType::SuperPellet);
    CHECK_EQ(scoreManager.getCurrentScore(), 160);
}

TEST_CASE("Test High Score Persists Across Sessions") {
    {
        ScoreManager scoreManager;
        scoreManager.updateCurrentScore(ScoreType::PowerPellet);
        scoreManager.updateHighScore(scoreManager.getCurrentScore());
    }
    
    ScoreManager newScoreManager;
    CHECK_GE(newScoreManager.getHighScore(), 500);
}