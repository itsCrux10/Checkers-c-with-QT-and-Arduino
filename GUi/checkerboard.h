#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QGraphicsRectItem>
#include "checkersbox.h"
#include "checkerspiece.h"





class CheckerBoard
{
public:
    CheckerBoard();



    void drawBox(int x, int y);

    void setUpWhite();
    void setUpBlack();

    void addChessPiece();
    void reset();


private:

    QList <CheckerBoard *> white;
    QList <CheckerBoard *> black;

};

#endif // CHECKERBOARD_H
