#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <QGraphicsPixmapItem>
#include <cell.h>


class ChessPiece : public QGraphicsPixmapItem
{

public:
    bool color;
    virtual bool figureCanMove(const Cell * start, const Cell * end);
    ChessPiece(int x, int y, bool color);
};

#endif // CHESSPIECE_H
