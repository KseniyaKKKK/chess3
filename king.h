#ifndef KING_H
#define KING_H
#include <chesspiece.h>

class King : public ChessPiece, public QGraphicsRectItem
{
public:
    King(int x, int y, bool color);
        QImage *whiteImage = new QImage(":/images/king-white.png");
        QImage *blackImage = new QImage(":/images/king-black.png");
};

#endif // KING_H
