#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// @DOC: GoBang Game Models Basic Info
#include <vector>

// 2 Game types
// @P1_VS_P2 means person versus person
// @P1_VS_COM means person versus AI
enum GameType
{
    P1_VS_P2,
    P1_VS_COM
};

// 3 Game Status
// @PLAYING means this match has started but not ended.
// @WIN means somethone wins the match
// @DEAD means this match cannot continue
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD
};

// Chess Board Size, as required, 9 x 9;
// if this size is not big enough, change here to 16 for the classic board size
const int kBoardSizeNum = 10;

class GameModel
{
public:
    bool playerFlag; // Who is playing
    GameType gameType; // Game type; P1_VS_P2 | P1_VS_COM
    GameStatus gameStatus; // Game Status

    std::vector<std::vector<int>> gameMapVec; // save current game board and chess status; no chess = 0, white = 1, black = -1
    std::vector<std::vector<int>> scoreMapVec; // save the current chess's importance score for AI's decision.
    

public:
    GameModel();
    void startGame(GameType type); // Game Begins
    void calculateScore(); // calculate the importance score
    void actionByPerson(int row, int col); // player placing chess
    void actionByAI(int &clickRow, int &clickCol); // computer placing chess
    void updateGameMap(int row, int col); // update two vec<vec<>>s  after every chess placment
    bool isWin(int row, int col); // Judge the result after this action.
    bool isDeadGame(); // Judge is this mathc a tie
};

#endif // GAMEMODEL_H
