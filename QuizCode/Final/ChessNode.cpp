#include <stdio.h>

class ChessNode{
    private:
    int location_x;
    int location_y;
    int player;


    public: 
    ChessNode(){
        location_x = 0;
        location_y = 0;
        player = -1;
    };

    void setNode(int x, int y, int id){
        location_x = x;
        location_y = y;
        player = id;
    }

    void SetLocation(int x, int y){
        location_x = x;
        location_y = y;
    };

    void setPlayer(int id){
        player = id;
    };

    int GetLocationX(){
        return location_x;
    };

    int GetLocationY(){
        return location_y;
    };

    int GetPlayer(){
        return player;
    };
};