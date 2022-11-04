#ifndef PIECE_H
#define PIECE_H

#include "checkerspiece.h"

class piece:public checkerspiece
{
public:
    piece(QString team,QGraphicsItem *parent = 0);
    void setImage();

    void moves();
};

#endif // PIECE_H
