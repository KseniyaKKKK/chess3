#ifndef KNIGHT_H
#define KNIGHT_H
#include <chesspiece.h>

class Knight: public ChessPiece, public QGraphicsRectItem
{
public:
    Knight(int x, int y, bool color);
    QImage *whiteImage = new QImage(":/images/knight-white.png");
    QImage *blackImage = new QImage(":/images/knight-black.png");
     virtual bool figureCanMove(const Cell * start, const Cell * end)override;
    bool color;
};

#endif // KNIGHT_H
