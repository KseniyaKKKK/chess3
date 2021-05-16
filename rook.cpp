#include "rook.h"

Rook::Rook(int x, int y, bool color) : ChessPiece(x, y, color)
{
    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }

    weight = 5;
}

bool Rook::figureCanMove(const Cell *start, const Cell *end)
{
    if (start->column == end->column || start->row == end->row)
    {
        FirstMoveRook = true;
        return true;
    }
    return false;
}
