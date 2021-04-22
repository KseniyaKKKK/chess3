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

    virtual void SumPrise (Cell *star, Cell *end);
    QVector <double> CountPriseB;
    QVector <double> CountPriseW;

   // enum Price {King = 0, Pawn = 1, Knight = 3, Bishop = 3, Rook = 5, Queen = 9}; стоимость меняется, так что низя
};

#endif // CHESSPIECE_H
