#ifndef ROOK_H
#define ROOK_H
#include <chesspiece.h>

class Rook : public ChessPiece, public QGraphicsRectItem
{
public:
    Rook(int x, int y, bool color);
    QImage *whiteImage = new QImage(":/images/rook-white.png");
    QImage *blackImage = new QImage(":/images/rook-black.png");
    virtual bool figureCanMove(const Cell * start, const Cell * end) override;
    bool color;
};

#endif // ROOK_H
