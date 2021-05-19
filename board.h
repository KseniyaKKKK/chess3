#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsScene>
#include <QMap>
#include "cell.h"
#include "chesspiece.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"
#include "move.h"
//#include "menu.h"
#include <QPushButton>

class Board :  public QGraphicsScene
{
    Q_OBJECT
    Cell cells[8][8];
    QMap<Cell*, ChessPiece *> cellsToPieces;
    bool turn = true;
    bool shah(bool color);
    std::pair<Cell *, bool> pawnAtEnd(bool color);
    void replacePawn();
    QPushButton *b1 = new QPushButton("Ферзь");
    QPushButton *b2 = new QPushButton("Ладья");
    QPushButton *b3 = new QPushButton("Конь");
    QPushButton *b4 = new QPushButton("Слон");
    QPushButton *n = new QPushButton("Шах");
virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    bool wayIsFree(Cell * start, Cell * end);
    bool compColor = false;
    Cell* pawnToReplace;
public:
    Board();
    Cell * clickedCell;
    Cell * previousClickedCell;
    bool mouseWasPressed;
    void drawCells();
    void addFigures();
    int sumW;
    int sumB;
    int countSum(bool color);
    QVector<Move> possibleMoves;
    QVector<Move> getPossibleMoves(bool color);
    bool withComp = true;
public slots:
    void move();
    void setBlackCompColor();
    void setWhiteCompColor();
    void addQueen();
    void addKnight();
    void addRook();
    void addBishop();
    void closeShahWindow();
signals:
    void secondClick();
    void compMove();
};

#endif // BOARD_H
