#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
//#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include "board.h"

class MyButton : public QWidget {
public:
    MyButton(QWidget *perent = 0);
};

MyButton :: MyButton (QWidget *perent) : QWidget (perent){
    QPushButton *quitBtn = new QPushButton ("White", this);
    quitBtn->setGeometry(100,140,75,30);

    connect (quitBtn, &QPushButton ::clicked, qApp, &QApplication :: quit);

    QPushButton *quitBtn2 = new QPushButton ("Black", this);
    quitBtn2->setGeometry(150,140,75,30);

    connect (quitBtn2, &QPushButton ::clicked, qApp, &QApplication :: quit);

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyButton window;

    window.resize(600, 400);
    window.setWindowTitle("Chess");
    window.show();
    //QGraphicsScene* scene = new QGraphicsScene();
    //QGraphicsView * view2 = new QGraphicsView(scene);
    //view2->show();


    Board * board = new Board();
    QGraphicsView * view = new QGraphicsView(board);
    board->drawCells();
    board->addFigures();
    view->resize(800,800);
    view->show();

    return app.exec();
}
