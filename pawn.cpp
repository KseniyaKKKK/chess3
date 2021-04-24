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
        else if (this->color && ((start->row - end->row == 2 && !hasMoved) || start->row - end->row == 1)) {
             hasMoved = true;
            return true;
        }
    }
    return false;
}

//void Pawn :: SumPrise(Cell * start, Cell * end) {
////Он как-то должен пробегать по клеткам и смотреть на позиции фигур

//    if (!this->color)
//    {
//        if (end->row == 6) SumB += 1;
//        if (end->row == 5) SumB +=1,5;
//        if (end->row == 4) SumB +=2;
//        if (end->row == 3) SumB +=3;
//        if (end->row == 2) SumB +=3,5;
//        if (end->row == 1) SumB +=4;
//        CountPriseB.push_back(SumB);
//    }

//    if (this->color)
//    {
//        if (end->row == 1) SumW += 1;
//        if (end->row == 2) SumW +=1,5;
//        if (end->row == 3) SumW +=2;
//        if (end->row == 4) SumW +=3;
//        if (end->row == 5) SumW +=3,5;
//        if (end->row == 6) SumW +=4;
//        CountPriseW.push_back(SumW);
//    }


//        //return VALUE + 1 * (8-y if color == WHITE else y)
//}
