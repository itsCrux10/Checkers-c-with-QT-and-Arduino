#include "mainwindow.h"
#include <QPixmap>
#include<QDebug>
#include<QGraphicsScene>
#include<QGraphicsView>
#include "button.h"
#include "ArduinoHandler.h"

ArduinoHandler arduinoHandler;

//Constructor de la clase main Window
MainWindow::MainWindow(QWidget *parent) : QGraphicsView(parent)
{
    gamescene= new QGraphicsScene();
    gamescene->setSceneRect(0,0,1400,900);


    setFixedSize(1400,900);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

//Funcion utilizada para aniadir a la escena objetos de qt
void MainWindow::addToScene(QGraphicsItem *item)
{
    gamescene->addItem(item);
}

//Funcion encargada de crear el tablero de juego
void MainWindow::drawCheckerBoard(){
    checkers= new CheckerBoard;
   drawStatsHolder(1110,0, Qt::darkBlue);
   checkers->drawBox(1400/2-400,50 );

}

//Funcion la cual se encarga de "crear" el fondo
void MainWindow::drawStatsHolder(int x, int y, QColor color)
{
    statHolder = new QGraphicsRectItem(QRectF(x,y,300,900));
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    statHolder->setBrush(brush);
    setBackgroundBrush(brush);
}

//Funcion encargada de cambiar de turno
void MainWindow::changeTurn()
{
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText("Turn : " + getTurn());
}

//Funcion encargada de remover de escena  objetos
void MainWindow::removeFromScene(QGraphicsItem *item)
{
    gamescene->removeItem(item);

}

//Metodo para obtener el turno
QString MainWindow::getTurn()
{
    return turn;
}

//MEtodo para defenir de quien es el turno
void MainWindow::setTurn(QString value)
{
    turn = value;
}

//Funcion que da inicio a los elementos de la pantalla de juego
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

    QGraphicsTextItem *index= new QGraphicsTextItem();
    index->setPos(250,75);
    index->setZValue(1);
    index->setDefaultTextColor(Qt::white);
    index->setFont(QFont("",20));
    index->setPlainText("1");
    addToScene(index);

    QGraphicsTextItem *index2= new QGraphicsTextItem();
    index2->setPos(250,175);
    index2->setZValue(1);
    index2->setDefaultTextColor(Qt::white);
    index2->setFont(QFont("",20));
    index2->setPlainText("2");
    addToScene(index2);

    QGraphicsTextItem *index3= new QGraphicsTextItem();
    index3->setPos(250,275);
    index3->setZValue(1);
    index3->setDefaultTextColor(Qt::white);
    index3->setFont(QFont("",20));
    index3->setPlainText("3");
    addToScene(index3);

    QGraphicsTextItem *index4= new QGraphicsTextItem();
    index4->setPos(250,375);
    index4->setZValue(1);
    index4->setDefaultTextColor(Qt::white);
    index4->setFont(QFont("",20));
    index4->setPlainText("4");
    addToScene(index4);

    QGraphicsTextItem *index5= new QGraphicsTextItem();
    index5->setPos(250,475);
    index5->setZValue(1);
    index5->setDefaultTextColor(Qt::white);
    index5->setFont(QFont("",20));
    index5->setPlainText("5");
    addToScene(index5);

    QGraphicsTextItem *index6= new QGraphicsTextItem();
    index6->setPos(250,575);
    index6->setZValue(1);
    index6->setDefaultTextColor(Qt::white);
    index6->setFont(QFont("",20));
    index6->setPlainText("6");
    addToScene(index6);

    QGraphicsTextItem *index7= new QGraphicsTextItem();
    index7->setPos(250,675);
    index7->setZValue(1);
    index7->setDefaultTextColor(Qt::white);
    index7->setFont(QFont("",20));
    index7->setPlainText("7");
    addToScene(index7);

    QGraphicsTextItem *index8= new QGraphicsTextItem();
    index8->setPos(250,775);
    index8->setZValue(1);
    index8->setDefaultTextColor(Qt::white);
    index8->setFont(QFont("",20));
    index8->setPlainText("8");
    addToScene(index8);


    QGraphicsTextItem *indexa= new QGraphicsTextItem();
    indexa->setPos(325,855);
    indexa->setZValue(1);
    indexa->setDefaultTextColor(Qt::white);
    indexa->setFont(QFont("",20));
    indexa->setPlainText("A");
    addToScene(indexa);

    QGraphicsTextItem *indexb= new QGraphicsTextItem();
    indexb->setPos(425,855);
    indexb->setZValue(1);
    indexb->setDefaultTextColor(Qt::white);
    indexb->setFont(QFont("",20));
    indexb->setPlainText("B");
    addToScene(indexb);

    QGraphicsTextItem *indexC= new QGraphicsTextItem();
    indexC->setPos(525,855);
    indexC->setZValue(1);
    indexC->setDefaultTextColor(Qt::white);
    indexC->setFont(QFont("",20));
    indexC->setPlainText("C");
    addToScene(indexC);

    QGraphicsTextItem *indexD= new QGraphicsTextItem();
    indexD->setPos(625,855);
    indexD->setZValue(1);
    indexD->setDefaultTextColor(Qt::white);
    indexD->setFont(QFont("",20));
    indexD->setPlainText("D");
    addToScene(indexD);

    QGraphicsTextItem *indexE= new QGraphicsTextItem();
    indexE->setPos(735,855);
    indexE->setZValue(1);
    indexE->setDefaultTextColor(Qt::white);
    indexE->setFont(QFont("",20));
    indexE->setPlainText("E");
    addToScene(indexE);

    QGraphicsTextItem *indexF= new QGraphicsTextItem();
    indexF->setPos(825,855);
    indexF->setZValue(1);
    indexF->setDefaultTextColor(Qt::white);
    indexF->setFont(QFont("",20));
    indexF->setPlainText("F");
    addToScene(indexF);

    QGraphicsTextItem *indexG= new QGraphicsTextItem();
    indexG->setPos(925,855);
    indexG->setZValue(1);
    indexG->setDefaultTextColor(Qt::white);
    indexG->setFont(QFont("",20));
    indexG->setPlainText("G");
    addToScene(indexG);

    QGraphicsTextItem *indexH= new QGraphicsTextItem();
    indexH->setPos(1025,855);
    indexH->setZValue(1);
    indexH->setDefaultTextColor(Qt::white);
    indexH->setFont(QFont("",20));
    indexH->setPlainText("H");
    addToScene(indexH);



}

//Funcion encargada de mostrar en pantalla el menu de inicio
void MainWindow::displayMainMenu()
{

    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Checkers");
    QFont titleFont("arial" , 50);
    titleText->setFont( titleFont);
    titleText->setDefaultTextColor(Qt::darkGray);

    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);


    //create Button
    Button * playButton = new Button("Play 1 vs PC");
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

//Funcion encargada de acabar el juego
void MainWindow::gameOver()
{
    //removeAll();
    setTurn("WHITE");
    alivePiece.clear();
    checkers->reset();
}

//Funcion encargada de remover elementos de la pantalla
void MainWindow::removeAll(){
    QList<QGraphicsItem*> itemsList = gamescene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}

//Funcion para obtener el movimiento de las piezas
int MainWindow::getMove(){

    int* checker = arduinoHandler.getCheckerCoord();
    // Aqui iría la función para iluminar los posibles movimientos
    cout << "[" << checker[0] << ", " << checker[1] << "]"<< endl;
    int* move = arduinoHandler.getMoveCoord();
    if (*move == 9) return getMove();
    else{
        cout << "[" << move[0] << ", " << move[1] << ", " << move[2] << ", " << move[3] << "]"<< endl;
        return 0;
    }
}





