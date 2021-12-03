#include <iostream>
#include <stack>
#include <ChessNode.cpp>

using namespace std;
#define BOARD_SIZE 9
#define BLACK 1
#define WHITE 2

class CheckerBoard{
    public:
    static CheckerBoard* getInstance(){
        if (instance == nullptr){
            instance = new CheckerBoard();
        }
        return instance;
    }

    void PlaceNode(int x, int y, int player){
        if (x >= 1 && y >= 1 && x <= size && y <= size){
            board[x][y].setNode(x,y,player);
            AddStep(board[x][y]);
        }
        else{
             throw "OutBoundError -- void PlaceNode -- CheckerBoard.cpp";
        }
    }

    ChessNode ShowNode(int x, int y){
        if (x >= 1 && y >= 1 && x <= size && y <= size){
            return board[x][y];
        }
            return board[0][0];
    }

    void AddStep(ChessNode node){
        route.push(node);
    }

    ChessNode ShowRecentStep(){
        if (!route.empty()){
            return route.top();
        }
        return board[0][0];
    }

    void RepentStep(){
        if (!route.empty()){
            ChessNode temp = route.top();
            board[temp.GetLocationX()][temp.GetLocationY()].setNode(temp.GetLocationX(), temp.GetLocationY(), -1);
            route.pop();
            return;
        }
        cout << "Let's place a checker first!" << endl;
    }

    void Display(){
        cout << "\t";
        for (int i = 1; i <= size; i++){
            cout << i << "\t";
        }
        cout << endl;
        for (int i = 1; i <= size; i++){
            cout << i << "\t";
            for (int j = 1; j <= size; j++){

            }
        }
    }
    private:
    static CheckerBoard* instance;
    CheckerBoard(){
        this-> size = BOARD_SIZE;
        board = new ChessNode* [size + 2];
        for (int i = 0; i < size + 2; i++){
            board[i] = new ChessNode[size + 2];
            for (int j = 0; j < size + 2; j++){
                board[i][j].setNode(i, j, -1);
            }
        }
    }
    int size;
    ChessNode ** board;
    stack<ChessNode> route;
};