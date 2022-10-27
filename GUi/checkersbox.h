#ifndef CHECKERSBOX_H
#define CHECKERSBOX_H
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include "checkerspiece.h"

class checkerspiece;
class CheckersBox:public QGraphicsRectItem
{
public:

    CheckersBox(QGraphicsItem *parent=0);
    ~CheckersBox();


    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(checkerspiece *piece);


    void resetOriginalColor();
    void setOriginalColor(QColor value);

    bool getHasChekcerPiece();
    void setHasCheckerPiece(bool value,checkerspiece *piece = 0);

    void setCheckerPieceColor(QString value);

     QString getChessPieceColor() ;

    void checkForCheck();


    int rowLoc;
    int colLoc;

    checkerspiece * currentPiece;

private:

    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    QString chessPieceColor;

};

#endif // CHECKERSBOX_H
