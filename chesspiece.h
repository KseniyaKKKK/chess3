#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <QGraphicsPixmapItem>
#include <cell.h>


class ChessPiece : public QGraphicsPixmapItem
{

public:
    double SumB, SumW = 0.0;
    bool color;
    virtual bool figureCanMove(const Cell * start, const Cell * end);
    ChessPiece(int x, int y, bool color);
    int weight = 1;
};

#endif // CHESSPIECE_H
