#include "mainwindow.h"
#include <QPixmap>
#include<QDebug>
#include<QGraphicsScene>
#include<QGraphicsView>
#include "button.h"

MainWindow::MainWindow(QWidget *parent) : QGraphicsView(parent)
{
    gamescene= new QGraphicsScene();
    gamescene->setSceneRect(0,0,1400,900);

    setFixedSize(1400,900);
    setScene(gamescene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    piecetomove = NULL;


    //display turn
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Turn : WHITE");

}

void MainWindow::addToScene(QGraphicsItem *item)
{
    gamescene->addItem(item);
}


void MainWindow::drawCheckerBoard(){
    checkers= new CheckerBoard;
   drawStatsHolder(600,0, Qt::green);
   checkers->drawBox(400,50 );
}


void MainWindow::drawStatsHolder(int x, int y, QColor color)
{
    statHolder = new QGraphicsRectItem(QRectF(x,y,300,900));
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    statHolder->setBrush(brush);
    addToScene(statHolder);
}

void MainWindow::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);

    addToScene(turnDisplay);
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

    blackPiece->setPos(1170,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::black);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    checkers->addChessPiece();
}


void MainWindow::displayMainMenu()
{
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem();
    p->setPixmap(QPixmap(":/images/king1.png"));
    p->setPos(420,170);
    addToScene(p);
    listG.append(p);

    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/images/king.png"));
    p1->setPos(920,170);
    addToScene(p1);
    listG.append(p1);
    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Chess Pro");
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);
    //create Button
    Button * playButton = new Button("Play 2 v 2");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 300;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);

    //Create Quit Button
    Button * quitButton = new Button("Quit");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 375;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    drawCheckerBoard();
    listG.append(quitButton);
}


void MainWindow::gameOver()
{
    //removeAll();
    setTurn("WHITE");
    alivePiece.clear();
    checkers->reset();
}


void MainWindow::removeAll(){
    QList<QGraphicsItem*> itemsList = gamescene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}






