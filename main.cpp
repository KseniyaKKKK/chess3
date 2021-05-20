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
    QPushButton * b3;
    QGraphicsView * view;
    QPushButton * b4;
public slots:
    void setBlackCompColor() {
        b1->hide();
        b2->hide();
        b3->hide();
        board->setBlackCompColor();
        board->addFigures();
    }
    void setWhiteCompColor() {
        b1->hide();
        b2->hide();
        b3->hide();
        board->setWhiteCompColor();
        board->addFigures();

        emit board->compMove();
    }
    void setOneOnOne() {
        b1->hide();
        b2->hide();
        b3->hide();
        board->withComp = false;
        board->addFigures();
    }
    void shah() {
        board->addWidget(b4);
        b4->show();
    }
    void hideShah() {
        b4->hide();
    }
public:
    Menu(QGraphicsView * view) {
        b1 = new QPushButton("White", view);
        b2 = new QPushButton("Black", view);
        b3 = new QPushButton("1 vs 1", view);
        b4 = new QPushButton("Шах", view);
        b1->setGeometry(900,150,70,30);
        b2->setGeometry(900,250,70,30);
        b3->setGeometry(900,350,70,30);
        b4->setGeometry(900,450,70,30);
        connect(b1, &QPushButton::clicked, this, &Menu::setBlackCompColor);
        connect(b2, &QPushButton::clicked, this, &Menu::setWhiteCompColor);
        connect(b3, &QPushButton::clicked, this, &Menu::setOneOnOne);
        connect(b4, &QPushButton::clicked, this, &Menu::hideShah);
        connect(board, &Board::shahSignal, this, &Menu::shah);
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
    board->addWidget(menu->b3);
    view->show();
    return app.exec();
}
