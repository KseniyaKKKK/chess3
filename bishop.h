#ifndef BISHOP_H
#define BISHOP_H
#include <chesspiece.h>

class Bishop : public ChessPiece, public QGraphicsRectItem
{
public:
    Bishop(int x, int y, bool color);
    QImage *whiteImage = new QImage(":/images/bishop-white.png");
    QImage *blackImage = new QImage(":/images/bishop-black.png");
    virtual bool figureCanMove(const Cell * start, const Cell * end) override;
    bool color;
};

#endif // BISHOP_H
