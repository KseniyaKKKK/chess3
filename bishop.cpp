#include "bishop.h"

Bishop::Bishop(int x, int y, bool color) : ChessPiece(x, y, color)
{
    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }

    weight = 4;
    name = "Bishop";
}

bool Bishop::figureCanMove(const Cell *start, const Cell *end)
{
    if (abs(start->column - end->column) == abs(start->row - end->row)) {
        return true;
    }
    return false;
}
