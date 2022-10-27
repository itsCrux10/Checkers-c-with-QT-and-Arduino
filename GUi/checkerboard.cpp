#include "checkerboard.h"
#include "mainwindow.h"

extern MainWindow *MainWindow;

CheckerBoard::CheckerBoard(){
    setUpBlack();
    setUpWhite();
}
void CheckerBoard::drawBox(int x, int y){
    int SHIFT = 100;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            CheckersBox *box = new CheckersBox();
            MainWindow->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::lightGray);
            else
                box->setOriginalColor(Qt::darkGray);
            MainWindow->addToScene(box);

        }
    }
}

void CheckerBoard::addChessPiece() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            CheckersBox *box =MainWindow->collection[i][j];
            if(i < 2) {
                static int k;
                box->placePiece(black[k]);
                MainWindow->alivePiece.append(black[k]);
                MainWindow->addToScene(black[k++]);
            }
            if(i > 5) {
                static int h;
                box->placePiece(white[h]);
                MainWindow->alivePiece.append(white[h]);
                MainWindow->addToScene(white[h++]);
            }

        }
    }
}

void CheckerBoard::setUpWhite()
{
    piece *piece;
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
        white.append(piece);
    }
    piece = new Rook("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Queen("WHITE");
    white.append(piece);
    piece = new King("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Rook("WHITE");
    white.append(piece);

}


void ChessBoard::setUpBlack()
{
    ChessPiece *piece;
    piece = new Rook("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Queen("BLACK");
    black.append(piece);
    piece = new King("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Rook("BLACK");
    black.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        black.append(piece);
    }
}


void CheckerBoard::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            CheckersBox *box =MainWindow->collection[i][j];
            box->setHasCheckerPiece(false);
            box->setCheckerPieceColor("NONE");
            box->currentPiece = NULL;
            if(i < 2) {

                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                MainWindow->alivePiece.append(black[k++]);

            }
            if(i > 5) {

                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                MainWindow->alivePiece.append(white[h++]);

            }

        }
    }
}





