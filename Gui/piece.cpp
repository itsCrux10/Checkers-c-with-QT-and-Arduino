#include "piece.h"
#include "checkersbox.h"
#include "mainwindow.h"
#include <QDebug>


extern class MainWindow *mainWindow;

//Constructor de la clase
piece::piece(QString team,QGraphicsItem *parent):checkerspiece(team,parent)
{

    setImage();

}
//Se selecciona una imagen a cargar
void piece::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap("/home/cruz/Downloads/Checkers-c-with-QT-and-Arduino-master/GUi/white.png"));
    else
        setPixmap(QPixmap("/home/cruz/Downloads/Checkers-c-with-QT-and-Arduino-master/GUi/black.png"));
}


//FUncion que determina los movimientos de la pieza
void piece::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //Arriba a la izquierda

    if(int i = row-1 && j = col-1) {
       if(mainWindow->collection[i][j]->getChessPieceColor() == team ) {
           break;
       }
       else
       {
           location.append(mainWindow->collection[i][j]);
           if(boxSetting(location.last()) ){
               break;
           }
       }
    }

     //arriba a la derecha

    if(int i = row-1 && j = col+1){
        if(mainWindow->collection[i][j]->getChessPieceColor() == team ) {
            break;

        }
        else if()
        {
            location.append(mainWindow->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

      //Abajo a la derecha

    if(int i = row+1 && j = col+1) {
         if(mainWindow->collection[i][j]->getChessPieceColor() == team ) {
             break;

         }
         else
         {
             location.append(mainWindow->collection[i][j]);
             if(boxSetting(location.last())){
                 break;
             }
         }
      }

       //Abajo a la izquierda

    if(int i = row+1 && j = col-1) {
          if(mainWindow->collection[i][j]->getChessPieceColor() == team ) {
              break;

          }
          else
          {
              location.append(mainWindow->collection[i][j]);
              if(boxSetting(location.last())){
                  break;
              }

          }
       }
}
