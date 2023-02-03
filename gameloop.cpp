#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "qdebug.h"


std::string MainWindow::getGameState()
{
    std::stringstream s;
    gameboard->print(s);
    std::string str= s.str();
    //remove newlines
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
    return str;
}




bool MainWindow::isFoodEaten()
{

    if(latestFoodPosition!=getGameState().find(FOOD_CHARACTER)){
        //update food position
        latestFoodPosition=getGameState().find(FOOD_CHARACTER);
        return true;


    }else{
        return false;
    }

}

void MainWindow::flashRedAndGreen()
{
    if(isGreen){

        pal.setColor(QPalette::Window, Qt::red);
        ui->gameTab->setPalette(pal);
        isGreen=false;
    }else{
        pal.setColor(QPalette::Window, Qt::green);
        ui->gameTab->setPalette(pal);
        isGreen=true;
    }


}

void MainWindow::GetPosition(qreal &x, qreal &y, std::string SNAKEPART)
{
    int index = getGameState().find(SNAKEPART);
    //calculating the row and column in snakeboard according the boardwidth
    int Row=index/(boardWidth+2)-1;
    int Column =index%(boardWidth+2)-1;



     //calculating the position in pixels on game screen

       x=PARTSIZE*Column;
       y=PARTSIZE*Row;

}

void MainWindow::deleteLastBodyPart()
{
    delete bodyParts.back();
    bodyParts.pop_back();

}

void MainWindow::moveFood()
{
    qreal x, y;
    GetPosition(x,y,FOOD_CHARACTER);
    Food->setX(x);
    Food->setY(y);
}

void MainWindow::pause()
{
    timer.stop();
    timePassedTimer.stop();
    int messageBoxResult = QMessageBox::critical(0,
                                          "Pause.",
                                             "Click retry to continue or cancel to go back to main",
                                             QMessageBox::Cancel,
                                             QMessageBox::Retry);
    if(messageBoxResult==QMessageBox::Cancel){gameOver(false,true);}
    else{
        timer.start(DURATION);
        timePassedTimer.start(100);
    }


}

void MainWindow::reset()
{
    gameOver(true,false);
}

void MainWindow::gameWindowMainClicked()
{
    gameOver(false,true);
}

void MainWindow::addBodyPart(qreal x, qreal y)
{
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    bodyParts.push_front(scene_->addEllipse(x, y, PARTSIZE, PARTSIZE, blackPen, redBrush));

}

void MainWindow::gameLoop(){


    gameboard->moveSnake(this->movingDirection);
    if(gameboard->gameOver()){
        gameOver(false,false);
        return;
    }

    qreal newBodyPartX = snakeHead->x();
    qreal newBodyPartY = snakeHead->y();

    //add new bodypart to last snakehead position
    addBodyPart(newBodyPartX,newBodyPartY);

    qDebug() << newBodyPartY << " and before" << newBodyPartY<<"  key ";


    if(isFoodEaten()){
        score++;
        QString scoreText = "Score:";
        scoreText.append(QString::number(score));
        ScoreBoard->setText(scoreText);

        moveFood();


    }else{
        deleteLastBodyPart();
    }

    //set snake tail to blue
    if(bodyParts.size()>0)bodyParts.back()->setBrush(Qt::blue);

    // Calculating the displacement that can be either
    // positive or negative, depending on the direction
    qreal headY = 0;
    qreal headX = 0;
    if(movingDirection=="s"){
        headY=PARTSIZE;
    }else if(movingDirection=="w"){
        headY=-PARTSIZE;

    }else if(movingDirection=="d"){
        headX=PARTSIZE;
    }else if(movingDirection=="a"){
        headX=-PARTSIZE;

    }

        snakeHead->moveBy(headX, headY);

}

