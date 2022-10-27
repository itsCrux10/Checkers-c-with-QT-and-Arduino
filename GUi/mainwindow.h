#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include<checkerboard.h>
#include "checkerspiece.h"
#include "button.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    //Constructor
    MainWindow(QWidget *parent = 0);

    //Metodos Publicos
    void drawStatsHolder(int x, int y, QColor color);
    void drawCheckerBoard();


    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    checkerspiece *piecetomove;

    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();



    CheckersBox *collection[8][8];
    QGraphicsTextItem *check;
    QList <checkerspiece *> alivePiece;
    void displayMainMenu();

    void gameOver();
    void removeAll();

public slots:
    void start();




private:
    QGraphicsScene *gamescene;
    QList <checkerspiece *> whiteDead;
    QList <checkerspiece *> blackDead;
    CheckerBoard *checkers;
    QGraphicsRectItem *statHolder;
    QString turn;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turnDisplay;

};

#endif // MAINWINDOW_H
