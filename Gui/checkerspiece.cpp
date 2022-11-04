#include "checkerspiece.h"
#include "checkersbox.h"
#include "mainwindow.h"
#include "piece.h"
extern class MainWindow *mainWindow;

//Constructor de la clase
checkerspiece::checkerspiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

//
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

//Funcion para asignar la box en la que se encuentra la ficha
void checkerspiece::setCurrentBox(CheckersBox *box)
{
    currentBox = box;
}

//FUncion para obtener al box en la que se encuentra la ficha
CheckersBox *checkerspiece::getCurrentBox()
{
    return currentBox;
}

//Funcion para saber si la pieza es negra o blanca
QString checkerspiece::getSide()
{
    return side;
}

//FUncion para definir el lado de la pieza
void checkerspiece::setSide( QString value)
{
    side = value;
}

//Funcion para saber si lapieza esta colocada
bool checkerspiece::getIsPlaced()
{
    return isPlaced;
}

//Funcion que establece si una pieza esta colocada
void checkerspiece::setIsPlaced(bool value)
{
    isPlaced = value;

}

//
QList<CheckersBox *> checkerspiece::moveLocation()
{
    return location;
}


//FUncion para regresar al color original
void checkerspiece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}


//Funcion que cambia los valores de las boxes a las que pueda moverse
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






