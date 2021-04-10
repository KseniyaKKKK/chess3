#include "queen.h"

Queen::Queen(int x, int y, bool color) : ChessPiece(x, y)
{
    this->color = color;
    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }
}

bool Queen::figureCanMove(const Cell *start, const Cell *end)
{
    if (abs(start->column - end->column) == abs(start->row - end->row) ||
            start->column == end->column || start->row == end->row)
    {
        return true;
    }
    return false;
}
