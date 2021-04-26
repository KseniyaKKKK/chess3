#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();
     QGraphicsView * view2 = new QGraphicsView(scene);
    view2->show();

    Board * board = new Board();
    QGraphicsView * view = new QGraphicsView(board);
    board->drawCells();
    board->addFigures();
    view->resize(800,800);
    view->show();
    return app.exec();
}
