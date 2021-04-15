#include "pawn.h"

Pawn::Pawn(int x, int y, bool color) : ChessPiece(x, y, color)
{
    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }
}

bool Pawn::figureCanMove(const Cell *start, const Cell *end)
{
    if (start->column == end->column)
    {
        if (!this->color &&  (end->row - start->row == 1 || (end->row - start->row == 2 && !hasMoved))) {
            hasMoved = true;
            return true;
        }
        else if (((start->row - end->row == 2 && !hasMoved) || start->row - end->row == 1)) {
             hasMoved = true;
            return true;
        }
    }
    return false;
}
