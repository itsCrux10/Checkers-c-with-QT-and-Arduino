#include "checkersbox.h"
#include "mainwindow.h"
#include <QDebug>

extern MainWindow *MainWindow;

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

CheckersBox::~CheckersBox()
{
    delete this;
}


void CheckersBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      //  qDebug() << getChessPieceColor();
        //Deselecting counter part of ChessPiece
        if(currentPiece == MainWindow->piecetomove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(MainWindow->piecetomove){
            //if same team
            if(this->getChessPieceColor() == MainWindow->piecetomove->getSide())
                return;
            //removing the eaten piece
            QList <CheckersBox *> movLoc = MainWindow->piecetomove->moveLocation();
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
             MainWindow->piecetomove->decolor();
             //make the first move false applicable for pawn only
             MainWindow->piecetomove->firstMove = false;
             //this is to eat or consume the enemy present inn the movable region
            if(this->getHasChekcerPiece()){
                this->currentPiece->setIsPlaced(false);
                this->currentPiece->setCurrentBox(NULL);


            }
            //changing the new stat and resetting the previous left region
            MainWindow->piecetomove->getCurrentBox()->setHasCheckerPiece(false);
            MainWindow->piecetomove->getCurrentBox()->currentPiece = NULL;
            MainWindow->piecetomove->getCurrentBox()->resetOriginalColor();
            placePiece(MainWindow->piecetomove);

            MainWindow->piecetomove = NULL;
            //changing turn
            MainWindow->changeTurn();
            checkForCheck();
        }
        //Selecting couterpart of the chessPiece
        else if(this->getHasChekcerPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }
}


void CheckersBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void CheckersBox::placePiece(checkerspiece *piece)
{

    piece->setPos(x()+50- piece->pixmap().width()/2  ,y()+50-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasCheckerPiece(true,piece);
    currentPiece = piece;


}

void CheckersBox::resetOriginalColor()
{
    setColor(originalColor);
}

void CheckersBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

bool CheckersBox::getHasChekcerPiece()
{
    return hasChessPiece;
}

void CheckersBox::setHasCheckerPiece(bool value, checkerspiece *piece)
{
    hasChessPiece = value;
    if(value)
        setCheckerPieceColor(piece->getSide());
    else
        setCheckerPieceColor("NONE");
}

void CheckersBox::setCheckerPieceColor(QString value)
{
    chessPieceColor = value;
}







