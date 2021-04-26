#include "knight.h"

Knight::Knight(int x, int y, bool color) : ChessPiece(x, y, color)
{
    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }

    weight = 3;
}

bool Knight::figureCanMove(const Cell * start, const Cell * end)
{
    if((start->row-1 ==end->row  &&  start->column+ 2 ==end->column ) || (start->row - 1 ==end->row  && start->column - 2 ==end->column) ||
              (start->row + 1 == end->row && start->column + 2 == end->column) || (start->row + 1 == end->row && start->column - 2 ==end->column )||
              (start->row - 2 == end->row && start->column + 1 == end->column) || (start->row - 2 == end->row && start->column - 1 == end->column) ||
              (start->row + 2 == end->row && start->column + 1 == end->column) || (start->row + 2 == end->row && start->column - 1 == end->column))
    {
        return true;
    }
    return false;


}
