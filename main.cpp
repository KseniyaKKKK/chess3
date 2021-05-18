#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "board.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Board * board = new Board();
    QGraphicsView * view = new QGraphicsView(board);
    board->drawCells();
    board->addFigures();
    board->menu->setGeometry(800,0,100,100);
    board->addWidget(board->menu);
    view->resize(900,800);
    view->show();

    return app.exec();
}
