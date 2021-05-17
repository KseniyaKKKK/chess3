#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <QGraphicsPixmapItem>
#include <cell.h>
#include <QString>

class ChessPiece : public QGraphicsPixmapItem
{

public:
    bool color;
    virtual bool figureCanMove(const Cell * start, const Cell * end);
    ChessPiece(int x, int y, bool color);
    int weight = 1;
    QString name = " ";
};

#endif // CHESSPIECE_H
