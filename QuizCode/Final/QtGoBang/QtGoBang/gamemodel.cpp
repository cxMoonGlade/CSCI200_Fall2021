#include <utility>
#include <stdlib.h>
#include <time.h>
#include "gamemodel.h"

GameModel::GameModel()
{

}

void GameModel::startGame(GameType type)
{
    gameType = type;
    // initlize the chess board
    gameMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < kBoardSizeNum; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }

    // If this a PVE game, initalize a importance map for AI (no needed for PVP model)
    if (gameType == P1_VS_COM)
    {
        scoreMapVec.clear();
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            std::vector<int> lineScores;
            for (int j = 0; j < kBoardSizeNum; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
        }
    }

    // mine is true, opponent is false
    playerFlag = true;


}

void GameModel::updateGameMap(int row, int col)
{
    if (playerFlag)
        gameMapVec[row][col] = 1;
    else
        gameMapVec[row][col] = -1;

    // change player
    playerFlag = !playerFlag;
}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row, col);
}

void GameModel::actionByAI(int &clickRow, int &clickCol)
{
    // get the importance score
    calculateScore();

    // find the most important place (has highest score)
    int maxScore = 0;
    std::vector<std::pair<int, int>> maxPoints;

    for (int row = 1; row < kBoardSizeNum; row++)
        for (int col = 1; col < kBoardSizeNum; col++)
        {
            // This coordinate must be empty
            if (gameMapVec[row][col] == 0)
            {
                // find the highest score
                if (scoreMapVec[row][col] > maxScore)
                {
                    maxPoints.clear();
                    maxScore = scoreMapVec[row][col];
                    maxPoints.push_back(std::make_pair(row, col));
                }
                // if there are multiple places have the highest score, save them all
                else if (scoreMapVec[row][col] == maxScore)
                    maxPoints.push_back(std::make_pair(row, col));
            }
        }

    // if there are multiple highest places, choose a random one.
    srand((unsigned)time(0));
    int index = arc4random() % maxPoints.size();

    std::pair<int, int> pointPair = maxPoints.at(index);
    // mark the chess set place.
    clickRow = pointPair.first;
    clickCol = pointPair.second;
    updateGameMap(clickRow, clickCol);
}

// calculate the highest score
void GameModel::calculateScore()
{
    // statiste the linked chesses of player or computer
    // @personNum: Player Linked Chesses
    // @botNum: AI Linked Chesses
    // @emptyNum: how many empty places neaby
    int personNum = 0;
    int botNum = 0;
    int emptyNum = 0;

    // empty the importance score vector<vector>>
    scoreMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> lineScores;
        for (int j = 0; j < kBoardSizeNum; j++)
            lineScores.push_back(0);
        scoreMapVec.push_back(lineScores);
    }

    // score
    for (int row = 0; row < kBoardSizeNum; row++)
        for (int col = 0; col < kBoardSizeNum; col++)
        {
            // empty place
            if (row > 0 && col > 0 &&
                gameMapVec[row][col] == 0)
            {
                // traversal all eight diretions
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // reset
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // not incluing the origin place
                        if (!(y == 0 && x == 0))
                        {
                            // 4 places for every direction
                            // score for WHITE
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                    col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                    gameMapVec[row + i * y][col + i * x] == 1) // Player Chess
                                {
                                    personNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                         col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                         gameMapVec[row + i * y][col + i * x] == 0) // Empty
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                // out of boundary
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                    col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                    gameMapVec[row - i * y][col - i * x] == 1)
                                // Player Chess
                                {
                                    personNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                         col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                         gameMapVec[row - i * y][col - i * x] == 0)
                                // empty
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                // out of boundary
                                    break;
                            }

                            if (personNum == 1)
                            // block for 2
                                scoreMapVec[row][col] += 10;
                            else if (personNum == 2)
                            // block for 3
                            {
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 40;
                            }
                            else if (personNum == 3)
                            // block for 4
                            {
                                // diffrent priority for different emtpy numbers
                                if (emptyNum == 1)
                                    scoreMapVec[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreMapVec[row][col] += 110;
                            }
                            else if (personNum == 4)
                            // block for 5
                                scoreMapVec[row][col] += 10100;

                            // reset
                            emptyNum = 0;

                            // score for BLACK
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                    col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                    gameMapVec[row + i * y][col + i * x] == 1)
                                // player chess
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < kBoardSizeNum &&
                                         col + i * x > 0 && col + i * x < kBoardSizeNum &&
                                         gameMapVec[row +i * y][col + i * x] == 0)
                                // empty
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                // out of bounday
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                    col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                    gameMapVec[row - i * y][col - i * x] == -1)
                                 // AI chess
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < kBoardSizeNum &&
                                         col - i * x > 0 && col - i * x < kBoardSizeNum &&
                                         gameMapVec[row - i * y][col - i * x] == 0)
                                // empty
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                // out of boundary
                                    break;
                            }

                            if (botNum == 0)
                            //noraml place
                                scoreMapVec[row][col] += 5;
                            else if (botNum == 1)
                            // link for 2
                                scoreMapVec[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)
                                // block for 3
                                    scoreMapVec[row][col] += 25;
                                else if (emptyNum == 2)
                                // link for 3
                                    scoreMapVec[row][col] += 50;
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)
                                // block for 4
                                    scoreMapVec[row][col] += 55;
                                else if (emptyNum == 2)
                                // link for 4
                                    scoreMapVec[row][col] += 100;
                            }
                            else if (botNum >= 4)
                                // link for 5
                                scoreMapVec[row][col] += 10000;
                        }
                    }

            }
        }
}

bool GameModel::isWin(int row, int col)
{
    // traveral all 4 directions and count 5 places
    // horizontal
    for (int i = 0; i < 5; i++)
    {
        if (col - i > 0 &&
            col - i + 4 < kBoardSizeNum &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
            return true;
    }

    // vertical
    for (int i = 0; i < 5; i++)
    {
        if (row - i > 0 &&
            row - i + 4 < kBoardSizeNum &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
            return true;
    }

    // left tilted
    for (int i = 0; i < 5; i++)
    {
        if (row + i < kBoardSizeNum &&
            row + i - 4 > 0 &&
            col - i > 0 &&
            col - i + 4 < kBoardSizeNum &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 1][col - i + 1] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 2][col - i + 2] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 3][col - i + 3] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 4][col - i + 4])
            return true;
    }

    // right tilted
    for (int i = 0; i < 5; i++)
    {
        if (row - i > 0 &&
            row - i + 4 < kBoardSizeNum &&
            col - i > 0 &&
            col - i + 4 < kBoardSizeNum &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col - i + 1] &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col - i + 2] &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col - i + 3] &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col - i + 4])
            return true;
    }

    return false;
}

bool GameModel::isDeadGame()
{
    // if all the places are placed
    for (int i = 1; i < kBoardSizeNum; i++)
        for (int j = 1; j < kBoardSizeNum; j++)
        {
            if (!(gameMapVec[i][j] == 1 || gameMapVec[i][j] == -1))
                return false;
        }
    return true;
}
