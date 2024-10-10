#include "scoreManager.h"

ScoreManager::ScoreManager():
fruitScore{10},
keyScore{50},
starPoints{500},
frighenedGhostScore{200},
superPelletScore{100},
powerPelletScore{500},
mazeMatchStarBonus{5000},
otherMatchStarBonus{2000},
currentScore{0}
{
    updateHighScore(0);
}

int ScoreManager::getHighScore() const
{
    return highScore;
}

void ScoreManager::updateHighScore(const int currentScore_)
{
    if (currentScore_ < 0) throw NegativeScoreNotAllowed{};

    highScoreFile.open("../resources/high_score.txt");

    //update high score if previous high score is surpassed
    if(highScoreFile.is_open())
    {
        highScoreFile >> highScore;
        if (highScore < currentScore_)
            highScore = currentScore_;
    }

    highScoreFile.close();
    outFile.open("../resources/high_score.txt");
    if(outFile.is_open())
       outFile << highScore;

    outFile.close();
}

void ScoreManager::updateCurrentScore(const ScoreType scoreType)
{
    switch (scoreType)
    {
    case ScoreType::Fruit:
        currentScore += fruitScore;
        break;
    case ScoreType::Key:
        currentScore += keyScore;
        break;
    case ScoreType::FrightenedGhost:
        currentScore += frighenedGhostScore;
        break;
    case ScoreType::MazeMatchBonus:
        currentScore += mazeMatchStarBonus;
        break;
    case ScoreType::OtherMatchBonus:
         currentScore += otherMatchStarBonus;
         break;
    case ScoreType::SuperPellet:
         currentScore += superPelletScore;
         break;
    case ScoreType::PowerPellet:
         currentScore += powerPelletScore;
         break;
    case ScoreType::Star:
         currentScore += starPoints;
         break;
    default:
        break;
    }
    updateHighScore(currentScore);
}

int ScoreManager::getCurrentScore() const
{
    return currentScore;
}