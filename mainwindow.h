/*has all of the ui things in it
 * gameloop.cpp contains all of the thins that are needed inside the game loop
 * mainwindow.cpp contains more of creation of buttons and snake board
 *
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.hh"
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QKeyEvent>
#include <deque>
#include "sstream"
#include <algorithm>
#include "QPushButton"
#include "qstring.h"
#include "qlabel.h"
#include "scoresaving.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void keyPressEvent(QKeyEvent* event) override;




private slots:
    void on_ShowScores_clicked();

    void on_BackToMain_clicked();

    void on_Play_clicked();

    //clear scores button
    void on_pushButton_clicked();

private:
    GameBoard* Game;

    unsigned long timePassedInMilliseconds=0;

    void drawGameBoard();

    std::string getGameState();

    void gameLoop();

    void timePassed();

    void gameWindowMainClicked();

    long unsigned int latestFoodPosition;
    bool isFoodEaten();

    void flashRedAndGreen();

    /*
     * Used to calculate position of head and new food particles
     */
    void GetPosition(qreal&x,qreal&y,std::string SNAKEPART);

    void addBodyPart(qreal x, qreal y);

    void deleteLastBodyPart();

    void moveFood();


    void pause();

    void reset();

    void initGameBoard();

    void gameOver(bool isRestart, bool mainButtonCLicked);

    int score =0;

    void createButtonsAndScoreBoard();
    QPushButton* pause_button;
    QPushButton* pauseButton;
    QPushButton* resetButton;
    QPushButton* backToMainButton;
    QPalette pal;
    QLabel *TimeCount;
    QLabel *ScoreBoard;
    QLabel *PlayerName;
    Ui::MainWindow *ui;
    const int SCORE_BOARD = 1;
    const int SNAKE_BOARD = 2;
    const int MAIN_WINDOW = 0;
    GameBoard* gameboard;
    int boardWidth = 30;
    int boardHeight = 30;
    scoreSaving scoreBoard;
    std::deque<QGraphicsEllipseItem*> bodyParts;


    std::string movingDirection ="w";
    const std::string SNAKEHEAD_CHARACTER="@";
    const std::string FOOD_CHARACTER="*";


    QTimer timePassedTimer;
    QTimer timer;



    bool isGreen=true;
    QGraphicsScene* scene_;




             // how much to move at a time
    const int DURATION = 200;      // how many milliseconds a move takes
    const int PARTSIZE=20;
    const std::string SNAKEHEAD = ":/snakehead.png";
    const std::string FOOD = ":/orange.png";
    QGraphicsPixmapItem* snakeHead = nullptr;
    QGraphicsPixmapItem* Food = nullptr;


};


#endif // MAINWINDOW_H


