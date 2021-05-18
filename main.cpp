#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "board.h"
#include <QPushButton>

Board * board;

class Menu : public QObject {
public:
    QPushButton * b1;
    QPushButton * b2;
    QGraphicsView * view;
public slots:
    void setBlackCompColor() {
        b1->hide();
        b2->hide();
        board->setBlackCompColor();
        board->addFigures();
    }
    void setWhiteCompColor() {
        b1->hide();
        b2->hide();
        board->setWhiteCompColor();
        board->addFigures();

        emit board->compMove();
    }
public:
    Menu(QGraphicsView * view) {
        b1 = new QPushButton("White", view);
        b2 = new QPushButton("Black", view);
        b1->setGeometry(900,150,70,30);
        b2->setGeometry(900,250,70,30);
        connect(b1, &QPushButton::clicked, this, &Menu::setBlackCompColor);
        connect(b2, &QPushButton::clicked, this, &Menu::setWhiteCompColor);
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    board = new Board();
    QGraphicsView * view = new QGraphicsView(board);
    board->drawCells();
    view->resize(1000,800);
    Menu *menu = new Menu(view);
    board->addWidget(menu->b1);
    board->addWidget(menu->b2);

    view->show();

    return app.exec();
}
