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

class Board :  public QGraphicsScene
{
    Q_OBJECT
    Cell cells[8][8];
    QMap<Cell*, ChessPiece *> cellsToPieces;
    bool turn = true;
virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    bool wayIsFree(Cell * start, Cell * end);
    bool compColor = false;
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
public slots:
    void move();
    void setBlackCompColor();
    void setWhiteCompColor();
signals:
    void secondClick();
    void compMove();
};

#endif // BOARD_H
