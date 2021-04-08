#include "king.h"

King::King(int x, int y, bool color) : ChessPiece(x, y)
{
    this->color = color;

    if (color) {
        this->setPixmap(QPixmap::fromImage(*whiteImage).scaled(90,90));
    }
    else {
        this->setPixmap(QPixmap::fromImage(*blackImage).scaled(90,90));
    }
}

//Мы лучшие!!!!!
