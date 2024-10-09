#include "scoreManager.h"

ScoreManager::ScoreManager(){}

int ScoreManager::getHighScore() const
{
    return highScore;
}

void ScoreManager::updateHighScore(const int currentScore)
{
    if (currentScore < 0) throw NegativeScoreNotAllowed{};

    highScoreFile.open("../resources/high_score.txt");

    //update high score if previous high score is surpassed
    if(highScoreFile.is_open())
    {
        highScoreFile >> highScore;
        if (highScore < currentScore)
            highScore = currentScore;
    }

    highScoreFile.close();
    outFile.open("../resources/high_score.txt");
    if(outFile.is_open())
       outFile << highScore;

    outFile.close();
}