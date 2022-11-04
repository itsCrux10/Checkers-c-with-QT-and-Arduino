#include "checkerboard.h"
#include "mainwindow.h"
#include "checkersbox.h"
#include "piece.h"
#include <iostream>


using namespace std;

extern class MainWindow *mainWindow;

CheckerBoard::CheckerBoard(){
    setUpBlack();
    setUpWhite();
}
void CheckerBoard::drawBox(int x, int y){
    int ss = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            CheckersBox *box = new CheckersBox();
            mainWindow->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+ss*j,y+ss*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::white);
            else
                box->setOriginalColor(Qt::black);
            mainWindow->addToScene(box);
        }
    }

}

void CheckerBoard::addChessPiece() {

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            CheckersBox *box =mainWindow->collection[i][j];

            if(i <= 2) {
                static int k;


                 if(i==0 && j%2 != 0 ){

                     box->placePiece(black[k]);
                     mainWindow->alivePiece.append(black[k]);
                     mainWindow->addToScene(black[k++]);
                 }
                if(i==2 && j%2 != 0 ){

                    box->placePiece(black[k]);
                    mainWindow->alivePiece.append(black[k]);
                    mainWindow->addToScene(black[k++]);
                }
                if(i==1 && j%2==0){

                     box->placePiece(black[k]);
                     mainWindow->alivePiece.append(black[k]);
                     mainWindow->addToScene(black[k++]);
                 }

            }

            if(i >= 5) {
                static int h;
                if(i==7 && j%2 != 0 ){
                    box->placePiece(white[h]);
                    mainWindow->alivePiece.append(white[h]);
                    mainWindow->addToScene(white[h++]);
                }
                if( i==5 && j%2 !=0){
                    box->placePiece(white[h]);
                    mainWindow->alivePiece.append(white[h]);
                    mainWindow->addToScene(white[h++]);
                }
                if(i==6 && j%2==0){
                    box->placePiece(white[h]);
                    mainWindow->alivePiece.append(white[h]);
                    mainWindow->addToScene(white[h++]);
        }

     }
   }

 }
}

void CheckerBoard::setUpWhite()
{
        checkerspiece *checkerw;

        for(int i = 0; i < 12; i++) {
             checkerw = new piece("WHITE");
             white.append(checkerw) ;
            }
        }


void CheckerBoard::setUpBlack()
{
    checkerspiece *checkerb;

    for(int i = 0; i < 12; i++) {
         checkerb = new piece("BLACK");
         black.append(checkerb) ;
        }
}


void CheckerBoard::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            CheckersBox *box =mainWindow->collection[i][j];
            box->setHasCheckerPiece(false);
            box->setCheckerPieceColor("NONE");
            box->currentPiece = NULL;
            if(i < 2) {

                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                mainWindow->alivePiece.append(black[k++]);

            }
            if(i > 5) {

                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                mainWindow->alivePiece.append(white[h++]);

            }

        }
    }
}





