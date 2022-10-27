#include "piece.h"
#include "mainwindow.h"
#include <QDebug>


extern MainWindow *MainWindow;


piece::piece(QString team,QGraphicsItem *parent):checkerspiece(team,parent)
{
    setImage();
}

void piece::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/bishop1.png"));
    else
        setPixmap(QPixmap(":/images/bishop.png"));
}


void piece::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //For upper Left

     for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
       if(MainWindow->collection[i][j]->getChessPieceColor() == team ) {
           break;

       }
       else
       {
           location.append(MainWindow->collection[i][j]);
           if(boxSetting(location.last()) ){
               break;
           }
       }
    }

     //For upper right

      for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(MainWindow->collection[i][j]->getChessPieceColor() == team ) {
            break;

        }
        else
        {
            location.append(MainWindow->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

      //For downward right

       for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
         if(MainWindow->collection[i][j]->getChessPieceColor() == team ) {
             break;

         }
         else
         {
             location.append(MainWindow->collection[i][j]);
             if(boxSetting(location.last())){
                 break;
             }
         }
      }

       //For downward left

        for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
          if(MainWindow->collection[i][j]->getChessPieceColor() == team ) {
              break;

          }
          else
          {
              location.append(MainWindow->collection[i][j]);
              if(boxSetting(location.last())){
                  break;
              }

          }
       }
}
