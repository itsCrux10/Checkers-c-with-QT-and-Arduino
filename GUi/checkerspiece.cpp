#include "checkerspiece.h"
#include "mainwindow.h"

extern MainWindow *MainWindow;
checkerspiece::checkerspiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void checkerspiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == MainWindow->piecetomove){
        MainWindow->piecetomove->getCurrentBox()->resetOriginalColor();
        MainWindow->piecetomove->decolor();
        MainWindow->piecetomove = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced() )|| ( (MainWindow->getTurn() != this->getSide())&& (!MainWindow->piecetomove)) )
        return;
    //selecting
    if(!MainWindow->piecetomove){

        MainWindow->piecetomove = this;
        MainWindow->piecetomove->getCurrentBox()->setColor(Qt::red);
        MainWindow->piecetomove->moves();
    }
    //Consuming counterPart of the CHessBox
    else if(this->getSide() != MainWindow->piecetomove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }
}

void checkerspiece::setCurrentBox(CheckersBox *box)
{
    currentBox = box;
}

CheckersBox *checkerspiece::getCurrentBox()
{
    return currentBox;
}

QString checkerspiece::getSide()
{
    return side;
}


void checkerspiece::setSide( QString value)
{
    side = value;
}

bool checkerspiece::getIsPlaced()
{
    return isPlaced;
}

void checkerspiece::setIsPlaced(bool value)
{
    isPlaced = value;

}

QList<CheckersBox *> checkerspiece::moveLocation()
{
    return location;
}

void checkerspiece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}






