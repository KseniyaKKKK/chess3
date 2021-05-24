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
#include <QPushButton>

class Board :  public QGraphicsScene
{
    Q_OBJECT
    Cell cells[8][8];
    Cell* pawnToReplace;
    QMap<Cell*, ChessPiece *> cellsToPieces;
    QMap<Cell*, ChessPiece *> cellsToPieces2;
    QPushButton *b1 = new QPushButton("Ферзь");
    QPushButton *b2 = new QPushButton("Ладья");
    QPushButton *b3 = new QPushButton("Конь");
    QPushButton *b4 = new QPushButton("Слон");
    QPushButton *n = new QPushButton("Шах");
    std::pair<Cell *, bool> pawnAtEnd(bool color);
    bool turn = true;
    bool compColor = false;

    bool wayIsFree(Cell * start, Cell * end);
    bool wayIsFree2(Cell * start, Cell * end);
    bool shah(QMap<Cell*, ChessPiece *> t,bool color);
    void replacePawn();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;

public:
    Board();
    Cell * clickedCell;
    Cell * previousClickedCell;
    bool mouseWasPressed;
    bool two = false;
    bool withComp = true;
    void drawCells();
    void addFigures();
    int sumW;
    int sumB;
    QVector<Move> possibleMoves;
    QVector<Move> getPossibleMoves(bool color);
    int countSum(QMap<Cell*, ChessPiece *> pieces, bool color);
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
    void shahSignal();
    void hideShah();
    void pat();
    void mat();
};

#endif // BOARD_H
