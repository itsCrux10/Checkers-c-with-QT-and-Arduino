#ifndef CHECKERSPIECE_H
#define CHECKERSPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>


class CheckersBox;
class checkerspiece:public QGraphicsPixmapItem
{
public:
    checkerspiece(QString team = "",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(CheckersBox *box);

    CheckersBox *getCurrentBox() ;

    QString getSide() ;
    void setSide( QString value);
    virtual void setImage() = 0;

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <CheckersBox *> moveLocation();
    virtual void moves() = 0;
    void decolor();

    bool firstMove;

    bool boxSetting(CheckersBox *box);

protected:
    CheckersBox *currentBox;
    QString side;
    bool isPlaced;
    QList <CheckersBox *> location;

};

#endif // CHECKERSPIECE_H
