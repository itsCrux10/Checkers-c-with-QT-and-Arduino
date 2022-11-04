#include "checkersbox.h"
#include "mainwindow.h"
#include <QDebug>

extern class MainWindow *mainWindow;

//Constructor de la clase
CheckersBox::CheckersBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //making the Square CHess Box
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasCheckerPiece(false);
    setCheckerPieceColor("NONE");
    currentPiece = NULL;
}

//destructor de la clase
CheckersBox::~CheckersBox()
{
    delete this;
}


void CheckersBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      //  qDebug() << getChessPieceColor();
        //Deselecting counter part of ChessPiece
        if(currentPiece == mainWindow->piecetomove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(mainWindow->piecetomove){
            //if same team
            if(this->getChessPieceColor() == mainWindow->piecetomove->getSide())
                return;
            //removing the eaten piece
            QList <CheckersBox *> movLoc = mainWindow->piecetomove->moveLocation();
            //TO make sure the selected box is in move zone
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;

                }
            }
            // if not prsent return
            if(check == 0)
                return;
            //change the color back to normal
             mainWindow->piecetomove->decolor();
             //make the first move false applicable for pawn only
             mainWindow->piecetomove->firstMove = false;
             //this is to eat or consume the enemy present inn the movable region
            if(this->getHasChekcerPiece()){
                this->currentPiece->setIsPlaced(false);
                this->currentPiece->setCurrentBox(NULL);


            }
            //changing the new stat and resetting the previous left region
            mainWindow->piecetomove->getCurrentBox()->setHasCheckerPiece(false);
            mainWindow->piecetomove->getCurrentBox()->currentPiece = NULL;
            mainWindow->piecetomove->getCurrentBox()->resetOriginalColor();
            placePiece(mainWindow->piecetomove);

            mainWindow->piecetomove = NULL;
            //changing turn
            mainWindow->changeTurn();
            checkForCheck();
        }
        //Selecting couterpart of the chessPiece
        else if(this->getHasChekcerPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }
}

//Funcion para pintar de cierto colo la pieza del tablero
void CheckersBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

//Funcion para colocar una pieza de juego en una cuadricula del tablero de juego
void CheckersBox::placePiece(checkerspiece *piece)
{

    piece->setPos(x()+50- piece->pixmap().width()/2  ,y()+50-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasCheckerPiece(true,piece);
    currentPiece = piece;


}

//Funcion para devolver al color original la cuadricula del tablero de juego
void CheckersBox::resetOriginalColor()
{
    setColor(originalColor);
}

//Funcion para definir el color original de la cuadricula
void CheckersBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

//FUncion vacia
void CheckersBox::checkForCheck()
{



}

//Funcion que consulta si existe alguna pieza coloda en la cuadricula de juego
bool CheckersBox::getHasChekcerPiece()
{
    return hasChessPiece;
}

//Funcion encargada de establecer si existe alguna pieza en el lugar
void CheckersBox::setHasCheckerPiece(bool value, checkerspiece *piece)
{
    hasChessPiece = value;
    if(value)
        setCheckerPieceColor(piece->getSide());
    else
        setCheckerPieceColor("NONE");
}

//FUncion que detecta de que color es la pieza seleccionada
void CheckersBox::setCheckerPieceColor(QString value)
{
    chessPieceColor = value;
}

//Funcion para obtener el color de la pieza seleccionada
QString CheckersBox::getChessPieceColor()
{
    return chessPieceColor;
}






