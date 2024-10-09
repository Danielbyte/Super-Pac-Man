#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <sstream>
#include <fstream>

class NegativeScoreNotAllowed{};
enum class ScoreType{Fruit, Key, SuperPellet, PowerPellet, MazeMatchBonus, NoMazeMatchBonus, FrightenedGhost};

class ScoreManager
{
    public:
        ScoreManager();
        int getHighScore() const;
        void updateHighScore(const int currentScore);
        void updateCurrentScore(const ScoreType scoreType);
    private:
        int highScore;
        int fruitScore;
        int keyScore;
        int frighenedGhostScore;
        int superPelletScore;
        int powerPelletScore;
        int mazeMatchStarBonus;
        int noMazeMatchStarBonus;
        int currentScore;

        std::ifstream highScoreFile;
        std::ofstream outFile;
};
#endif