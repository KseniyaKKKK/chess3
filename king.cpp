#include "king.h"

King::King(int x, int y, bool color) : ChessPiece(x, y, color)
{
    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }
    name = "King";
}

bool King::figureCanMove(const Cell *start, const Cell *end)
{
    if (pow(start->column-end->column, 2) + pow(start->row-end->row, 2) <= 2)
    {
       return true;
    }
    return false;
}

//Мы лучшие!!!!!
