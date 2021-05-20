#ifndef PAWN_H
#define PAWN_H
#include <chesspiece.h>

class Pawn : public ChessPiece, public QGraphicsRectItem
{
public:
    Pawn(int x, int y, bool color);
    QImage *whiteImage = new QImage(":/images/pawn-white.png");
    QImage *blackImage = new QImage(":/images/pawn-black.png");
    virtual bool figureCanMove(const Cell * start, const Cell * end) override;

    bool P(const Cell * start, const Cell * end, bool);

    bool hasMoved = false;
    int TWO = 1;

    bool forpawn = false;
    bool taking_on_the_aisle = false;
};

#endif // PAWN_H
