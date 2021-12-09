#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamemodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    // Draw
    void paintEvent(QPaintEvent *event);
    // monite the movement of mouse, to see where to set the chess on the board picture
    void mouseMoveEvent(QMouseEvent *event);
    // after the click, draw the chess.
    void mouseReleaseEvent(QMouseEvent *event);

private:
    GameModel *game; // the pointer of game, for later options
    GameType game_type; // Save game type
    int clickPosRow, clickPosCol; // Save the place to be clicked
    void initGame(); // initalize the match.
    void checkGame(int y, int x);

private slots:
    void chessOneByPerson(); // Person plays a chess
    void chessOneByAI(); // AI plays a chess

    void initPVPGame(); // initalize a person versus person match
    void initPVEGame(); // initalize a person versus computer match
};

#endif // MAINWINDOW_H
