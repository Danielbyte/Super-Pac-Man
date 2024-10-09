#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <sstream>
#include <fstream>

class NegativeScoreNotAllowed{};
enum class ScoreType{Fruit, Key, Lock, SuperPellet, PowerPellet, Star, MazeMatchBonus, NoMazeMatchBonus};

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
        int lockScore;
        int superPelletScore;
        int powerPelletScore;
        int starScore;
        int mazeMatchBonus;
        int noMazeMatchBonus;

        std::ifstream highScoreFile;
        std::ofstream outFile;
};
#endif