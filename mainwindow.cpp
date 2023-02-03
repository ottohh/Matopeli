#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "qdebug.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->Pages->setCurrentIndex(MAIN_WINDOW

                               );

    connect(&timer, &QTimer::timeout, this, &MainWindow::gameLoop);
    connect(&timePassedTimer, &QTimer::timeout, this, &MainWindow::timePassed);
    createButtonsAndScoreBoard();








}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_ShowScores_clicked()
{
    ui->Pages->setCurrentIndex(SCORE_BOARD);
    scoreBoard.printScores(ui->scoreBoard);

}


void MainWindow::on_BackToMain_clicked()
{
    TimeCount->hide();
    ScoreBoard->hide();
    PlayerName->hide();
    pauseButton->hide();
    resetButton->hide();
    backToMainButton->hide();
    ui->Pages->setCurrentIndex(MAIN_WINDOW

                               );
}


void MainWindow::on_Play_clicked()
{

    if(ui->PlayerName->text()==""){
        QMessageBox::critical(0,
                                              "!!!!",
                                                 "Enter name!",
                                                 QMessageBox::Yes
                                                 );

        return;
    }


    ui->Pages->setCurrentIndex(SNAKE_BOARD);

    //creating the gameboard object with user given values
    boardHeight=ui->GameHeigth->value();
    boardWidth=ui->GameWidth->value();
    gameboard = new GameBoard(boardWidth,boardHeight,ui->SemenValue->value());
    latestFoodPosition =getGameState().find(FOOD_CHARACTER);

    initGameBoard();

     timer.start(DURATION);
     timePassedTimer.start(100);
     // and show it
     pauseButton->show();
     resetButton->show();
     ScoreBoard->show();
     TimeCount->show();
     PlayerName->show();
     backToMainButton->show();

     QString Playername="Player:";
     Playername.append(ui->PlayerName->text());
     PlayerName->setText(Playername);
     score=0;

     QString Score = "Score:0";
     ScoreBoard->setText(Score);






}


void MainWindow::initGameBoard()
{
    scene_ = new QGraphicsScene(this);

    // Calculating the size for board in pixels
    int graphicViewHeight =(boardHeight)*(PARTSIZE);
    int graphicViewWidth = (boardWidth)*(PARTSIZE);

    //to center the graphicsView
    int left_margin = (this->width()-graphicViewWidth)/2; // x coordinate
    int top_margin = (this->height()-graphicViewHeight)/2; // y coordinate

    scene_->setSceneRect(0,0,graphicViewWidth,graphicViewHeight);
    ui->graphicsView->setGeometry(left_margin,top_margin, graphicViewWidth+2, graphicViewHeight+2);
    ui->graphicsView->setScene(scene_);

    // set green background to snake window
    pal = QPalette();
    pal.setColor(QPalette::Window, Qt::green);
    ui->gameTab->setAutoFillBackground(true);
    ui->gameTab->setPalette(pal);

    //Create snake head
    QPixmap head(QString::fromStdString(SNAKEHEAD));
    head = head.scaled(PARTSIZE, PARTSIZE);
    snakeHead =scene_->addPixmap(head);

     //Create food
    QPixmap food(QString::fromStdString(FOOD));
    food = food.scaled(PARTSIZE, PARTSIZE);
    Food =scene_->addPixmap(food);

    //Move snake head to start position
    qreal x,y;
    GetPosition(x,y,SNAKEHEAD_CHARACTER);
    snakeHead->setX(x);
    snakeHead->setY(y);

     moveFood();









}

void MainWindow::timePassed()
{

        timePassedInMilliseconds+=1;
        QString timePassedText;
        timePassedText.append("Time:");
        timePassedText.append(QString::number(timePassedInMilliseconds/10));
        timePassedText.append(".");
        timePassedText.append(QString::number(timePassedInMilliseconds%10));
        timePassedText.append(QString("0").repeated(1-QString::number(timePassedInMilliseconds%10).size()));
        TimeCount->setText(timePassedText);




}

void MainWindow::gameOver(bool isRestart,bool mainButtonCLicked)
{

    scoreBoard.saveScore(score,ui->PlayerName->text().toStdString());
    timer.stop();
    timePassedTimer.stop();
    timePassedInMilliseconds=0;

    bool gameWon=gameboard->gameWon();

    delete gameboard;
    delete scene_;
    bodyParts.clear();

    if(mainButtonCLicked){
        on_BackToMain_clicked();
        return;

    }

    if(isRestart){

        on_Play_clicked();


        return;
    }


    QTimer flash;
    connect(&flash, &QTimer::timeout, this, &MainWindow::flashRedAndGreen);
    flash.start(300);


    QString gameText= "GG";
    if(gameWon){
        gameText.append(" you won!");
    }else{
        gameText.append(" you lost :(");
    }
    int messageBoxResult = QMessageBox::question(0,
                                          gameText,
                                             "Wanna play again?",
                                             QMessageBox::Yes,
                                             QMessageBox::No);

    flash.stop();

    if(messageBoxResult==QMessageBox::Yes){
        on_Play_clicked();
    }else{
        on_BackToMain_clicked();
    }



}




void MainWindow::createButtonsAndScoreBoard()
{

    pauseButton = new QPushButton("Pause", this);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pause);
    pauseButton->hide();

    resetButton = new QPushButton("Restart", this);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::reset);
    resetButton->hide();

    backToMainButton=new QPushButton("Main", this);
    connect(backToMainButton, &QPushButton::clicked, this, &MainWindow::gameWindowMainClicked);
    backToMainButton->hide();

    resetButton->setGeometry(0, 0, 50, 20);
    pauseButton->setGeometry(0, 20, 50, 20);
    backToMainButton->setGeometry(50,0,50,20);

    PlayerName = new QLabel(this);


    PlayerName->setAlignment(Qt::AlignBottom | Qt::AlignCenter);

    QFont font = PlayerName->font();
    font.setPointSize(10);
    font.setBold(true);

    PlayerName->setFont(font);
    PlayerName->setGeometry(width()/2-100,10 ,200,20);



    ScoreBoard = new QLabel(this);
    ScoreBoard->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    ScoreBoard->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    //Here is how to change position:

    ScoreBoard->setFont(font);
    ScoreBoard->setGeometry(width()/2-300,10 ,90,20);

    TimeCount = new QLabel(this);


    TimeCount->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    //Here is how to change position:

    TimeCount->setFont(font);
    TimeCount->setGeometry(width()/2+200,10 ,90,20);
    TimeCount->hide();
    ScoreBoard->hide();
    PlayerName->hide();


}







void MainWindow::keyPressEvent(QKeyEvent* event) {



    if(event->key() == Qt::Key_W) {
        movingDirection="w";
    }else if(event->key() == Qt::Key_A){
        movingDirection="a";
    }else if(event->key() == Qt::Key_D){
        movingDirection="d";
    }else if(event->key() == Qt::Key_S){
        movingDirection="s";
    }


}


void MainWindow::on_pushButton_clicked()
{
    scoreBoard.clearScores(ui->scoreBoard);
}

