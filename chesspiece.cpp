#include "chesspiece.h"
#include <QDebug>

bool ChessPiece::figureCanMove(const Cell *, const Cell *)
{
    return true;
}

ChessPiece::ChessPiece(int x, int y, bool color)
{
    this->setX(x);
    this->setY(y);
    this->color = color;
    this->setPos(x, y);
}
