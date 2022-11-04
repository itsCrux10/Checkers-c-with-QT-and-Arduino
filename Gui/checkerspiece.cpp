#include "checkerspiece.h"
#include "checkersbox.h"
#include "mainwindow.h"
#include "piece.h"
extern class MainWindow *mainWindow;

checkerspiece::checkerspiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void checkerspiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == mainWindow->piecetomove){
        mainWindow->piecetomove->getCurrentBox()->resetOriginalColor();
        mainWindow->piecetomove->decolor();
        mainWindow->piecetomove = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced() )|| ( (mainWindow->getTurn() != this->getSide())&& (!mainWindow->piecetomove)) )
        return;
    //selecting
    if(!mainWindow->piecetomove){

        mainWindow->piecetomove = this;
        mainWindow->piecetomove->getCurrentBox()->setColor(Qt::red);
        mainWindow->piecetomove->moves();
    }
    //Consuming counterPart of the CHessBox
    else if(this->getSide() != mainWindow->piecetomove->getSide()){
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


bool checkerspiece::boxSetting(CheckersBox *box)
{
    if(box->getHasChekcerPiece()) {


            box->setColor(Qt::blue);
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}






