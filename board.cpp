#include "board.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPushButton>

Board::Board()
{
    mouseWasPressed = false;
    previousClickedCell = NULL;
    clickedCell = NULL;
    possibleMoves.push_back({nullptr, nullptr, 0});
    connect(this, &Board::secondClick, this, &Board::move);
    connect(this, &Board::compMove, this, &Board::move);
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    previousClickedCell = clickedCell;
    if (previousClickedCell != NULL) previousClickedCell->setBrush(Qt::transparent);
    clickedCell = clickedCell = &cells[(int(event->scenePos().x() - 39 )/ 90)][(int(event->scenePos().y() - 39 ) / 90)];
    clickedCell->setBrush(Qt::red);
    if (mouseWasPressed) {
        mouseWasPressed = false;
        emit secondClick();
    }
    else {
        mouseWasPressed = true;
    }
}

void Board::drawCells()
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,800,800);
    rect->setBrush(QImage(":/images/board.png").scaled(800,800));
    this->addItem(rect);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cells[i][j].setX(39 + i*90);
            cells[i][j].setY(39 + j*90);
            QRectF * rect = new QRectF();
            rect->setWidth(90);
            rect->setHeight(90);
            cells[i][j].setRect(*rect);
            cells[i][j].setX(39 + i*90);
            cells[i][j].setY(39 + j*90);
            cells[i][j].column = i;
            cells[i][j].row = j;
            this->addItem(&cells[i][j]);
        }
    }
}

void Board::addFigures()
{
    for (int i = 0; i < 8; ++i) {
        cellsToPieces[&cells[i][6]] = new Pawn(cells[i][6].x(), cells[i][6].y(), true);
        this->addItem(cellsToPieces.value(&cells[i][6]));
    }
    for (int i = 0; i < 8; ++i) {
        cellsToPieces[&cells[i][1]] = new Pawn(cells[i][1].x(), cells[i][1].y(), false);
        this->addItem(cellsToPieces.value(&cells[i][1]));
    }

    for (int j = 0; j < 8; j = j+7) {
        cellsToPieces[&cells[j][7]] = new Rook(cells[j][7].x(), cells[j][7].y(), true);
        this->addItem(cellsToPieces.value(&cells[j][7]));
    }
    for (int j = 0; j < 8; j = j+7) {
        cellsToPieces[&cells[j][0]] = new Rook(cells[j][0].x(), cells[j][0].y(), false);
        this->addItem(cellsToPieces.value(&cells[j][0]));
    }

    cellsToPieces[&cells[4][7]] = new King(cells[4][7].x(), cells[4][7].y(), true);
    this->addItem(cellsToPieces.value(&cells[4][7]));

    cellsToPieces[&cells[4][0]] = new King(cells[4][0].x(), cells[4][0].y(), false);
    this->addItem(cellsToPieces.value(&cells[4][0]));

    cellsToPieces[&cells[3][7]] = new Queen(cells[3][7].x(), cells[3][7].y(), true);
    this->addItem(cellsToPieces.value(&cells[3][7]));

    cellsToPieces[&cells[3][0]] = new Queen(cells[3][0].x(), cells[3][0].y(), false);
    this->addItem(cellsToPieces.value(&cells[3][0]));

    for (int j = 1; j < 8; j = j+5) {
    cellsToPieces[&cells[j][0]] = new Knight(cells[j][0].x(), cells[j][0].y(), false);
    this->addItem(cellsToPieces.value(&cells[j][0]));
    }

    for (int j = 1; j < 8; j = j+5) {
    cellsToPieces[&cells[j][7]] = new Knight(cells[j][7].x(), cells[j][7].y(), true);
    this->addItem(cellsToPieces.value(&cells[j][7]));
    }

    for (int j = 2; j < 8; j = j+3) {
    cellsToPieces[&cells[j][0]] = new Bishop(cells[j][0].x(), cells[j][0].y(), false);
    this->addItem(cellsToPieces.value(&cells[j][0]));
    }

    for (int j = 2; j < 8; j = j+3) {
    cellsToPieces[&cells[j][7]] = new Bishop(cells[j][7].x(), cells[j][7].y(), true);
    this->addItem(cellsToPieces.value(&cells[j][7]));
    }
}

void Board::move()
{
    if (withComp && turn == compColor)
    {
        if (clickedCell != NULL)
        {
            clickedCell->setBrush(Qt::transparent);
        }
        possibleMoves = getPossibleMoves(turn);
        if (possibleMoves.length() == 0) {
            if (this->shah(cellsToPieces,turn))
            {
                qDebug() << "mat" << Qt::endl;
                emit mat();
                return;
            }
            else
            {
                qDebug() << "pat" << Qt::endl;
                emit pat();
                return;
            }
        }
        std::sort(possibleMoves.begin(), possibleMoves.end());
        if (possibleMoves[possibleMoves.length() - 1].difference == 0) {
            int index = rand() % possibleMoves.length();
            previousClickedCell = possibleMoves[index].start;
            clickedCell = possibleMoves[index].end;
        }
        else {
            previousClickedCell = possibleMoves[possibleMoves.length() - 1].start;
            clickedCell = possibleMoves[possibleMoves.length() - 1].end;
        }
    }
    else
    {
        possibleMoves = getPossibleMoves(turn);
        if (possibleMoves.length() == 0) {
            if (this->shah(cellsToPieces,turn))
            {
                emit mat();
                return;
            }
            else
            {
                emit pat();
                return;
            }
        }
    }

    //если в начальной клетке есть фигурка
    if (cellsToPieces.contains(previousClickedCell) && cellsToPieces[previousClickedCell]->color == turn)
    {
        if (cellsToPieces[previousClickedCell]->name == "Knight")
        {
            if (cellsToPieces[previousClickedCell]->figureCanMove(previousClickedCell, clickedCell))
            {
                if (cellsToPieces.contains(clickedCell))
                {
                    if (cellsToPieces[previousClickedCell]->color != cellsToPieces[clickedCell]->color)
                    {
                        cellsToPieces2 = cellsToPieces;
                        cellsToPieces2.detach();
                        cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces2.remove(previousClickedCell);
                        //pohodi
                        if (!shah(cellsToPieces2, turn))
                        {
                            cellsToPieces[clickedCell]->setPixmap(QPixmap());
                            cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                            cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                            cellsToPieces.remove(previousClickedCell);
                            turn = !turn;
                        }
                    }
                }
                else
                {
                    cellsToPieces2 = cellsToPieces;
                    cellsToPieces2.detach();
                    cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                    cellsToPieces2.remove(previousClickedCell);
                    if (!shah(cellsToPieces2, turn))
                    {
                        //pohodi
                        cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                        cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces.remove(previousClickedCell);
                        turn = !turn;
                    }
                }
            }
        }
        else if (cellsToPieces[previousClickedCell]->name == "Pawn")
        {
            if (abs(previousClickedCell->column - clickedCell->column) == abs(previousClickedCell->row - clickedCell->row) )
            {
                if (cellsToPieces.contains(clickedCell))
                    static_cast<Pawn*>(cellsToPieces[previousClickedCell])->forpawn = true;
                else
                    static_cast<Pawn*>(cellsToPieces[previousClickedCell])->forpawn = false;
            }

            if (previousClickedCell->column == clickedCell->column )
            {
                if (cellsToPieces.contains(clickedCell))
                    static_cast<Pawn*>(cellsToPieces[previousClickedCell])->pered = true;
                else
                    static_cast<Pawn*>(cellsToPieces[previousClickedCell])->pered = false;
            }

            if ((abs(previousClickedCell->column - clickedCell->column) == abs(previousClickedCell->row - clickedCell->row)) && !cellsToPieces.contains(clickedCell) )
            {
                if (cellsToPieces.contains(&cells[previousClickedCell->column + 1][previousClickedCell->row]) ||
                    cellsToPieces.contains(&cells[previousClickedCell->column - 1][previousClickedCell->row]))
                {
                    if  (cellsToPieces.contains(&cells[previousClickedCell->column + 1][previousClickedCell->row]) &&
                         (cellsToPieces[&cells[previousClickedCell->column + 1][previousClickedCell->row]]->name == "Pawn") &&
                          (cellsToPieces[previousClickedCell]->color != cellsToPieces[&cells[previousClickedCell->column + 1][previousClickedCell->row]]->color))
                    {
                        static_cast<Pawn*>(cellsToPieces[previousClickedCell])-> taking_on_the_aisle = true;
                        two =false;

                        if (clickedCell->column == (previousClickedCell->column + 1))
                        {
                             if (static_cast<Pawn*>(cellsToPieces[&cells[previousClickedCell->column + 1][previousClickedCell->row]])-> TWO == 2)
                                 two = true;
                        }
                        else if (clickedCell->column == (previousClickedCell->column - 1))
                        {
                             if (static_cast<Pawn*>(cellsToPieces[&cells[previousClickedCell->column - 1][previousClickedCell->row]])-> TWO == 2)
                                 two = true;
                        }
                        if ((static_cast<Pawn*>(cellsToPieces[previousClickedCell])->P(previousClickedCell, clickedCell, two))
                                && wayIsFree(previousClickedCell, clickedCell))
                        {
                             //pohodi
                            cellsToPieces2 = cellsToPieces;
                            cellsToPieces2.detach();
                            cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                            cellsToPieces2.remove(previousClickedCell);
                            if (!shah(cellsToPieces2, turn))
                            {
                                static_cast<Pawn*>(cellsToPieces[previousClickedCell])->hasMoved = true;
                                cellsToPieces[&cells[previousClickedCell->column + 1][previousClickedCell->row]]->setPixmap(QPixmap());
                                cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                                cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                                cellsToPieces.remove(previousClickedCell);
                                turn = !turn;
                            }
                        }
                    }
                    else if (cellsToPieces.contains(&cells[previousClickedCell->column - 1][previousClickedCell->row]) &&
                             (cellsToPieces[&cells[previousClickedCell->column - 1][previousClickedCell->row]]->name == "Pawn") &&
                              (cellsToPieces[previousClickedCell]->color != cellsToPieces[&cells[previousClickedCell->column - 1][previousClickedCell->row]]->color))
                    {
                        static_cast<Pawn*>(cellsToPieces[previousClickedCell])-> taking_on_the_aisle = true;
                        if ((static_cast<Pawn*>(cellsToPieces[previousClickedCell])->P(previousClickedCell, clickedCell, two))
                               ) //&& wayIsFree(previousClickedCell, clickedCell))
                        {
                             //pohodi
                            cellsToPieces2 = cellsToPieces;
                            cellsToPieces2.detach();
                            cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                            cellsToPieces2.remove(previousClickedCell);
                            if (!shah(cellsToPieces2, turn))
                            {
                                static_cast<Pawn*>(cellsToPieces[previousClickedCell])->hasMoved = true;
                                cellsToPieces[&cells[previousClickedCell->column + 1][previousClickedCell->row]]->setPixmap(QPixmap());
                                cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                                cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                                cellsToPieces.remove(previousClickedCell);
                                turn = !turn;
                            }
                        }
                    }
                }
                else
                {
                    static_cast<Pawn*>(cellsToPieces[previousClickedCell])-> taking_on_the_aisle = false;
                }
            }

            else
            {
                if (cellsToPieces[previousClickedCell]->figureCanMove(previousClickedCell, clickedCell) &&
                        wayIsFree(previousClickedCell, clickedCell))
                {
                    if (cellsToPieces.contains(clickedCell))
                    {
                        if ((cellsToPieces[previousClickedCell]->color != cellsToPieces[clickedCell]->color) && (abs (previousClickedCell->column - clickedCell->column) == abs(clickedCell->row - previousClickedCell->row)))
                        {
                             //pohodi
                            cellsToPieces2 = cellsToPieces;
                            cellsToPieces2.detach();
                            cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                            cellsToPieces2.remove(previousClickedCell);
                            if (!shah(cellsToPieces2, turn))
                            {
                                static_cast<Pawn*>(cellsToPieces[previousClickedCell])->hasMoved = true;
                                cellsToPieces[clickedCell]->setPixmap(QPixmap());
                                cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                                cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                                cellsToPieces.remove(previousClickedCell);
                                turn = !turn;
                            }
                        }
                    }
                    else
                    {
                         //pohodi
                        cellsToPieces2 = cellsToPieces;
                        cellsToPieces2.detach();
                        cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces2.remove(previousClickedCell);
                        if (!shah(cellsToPieces2, turn))
                        {
                            static_cast<Pawn*>(cellsToPieces[previousClickedCell])->hasMoved = true;
                            cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                            cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                            cellsToPieces.remove(previousClickedCell);
                            turn = !turn;
                        }
                    }
                }
            }
        }
        else if (cellsToPieces.contains(clickedCell) && cellsToPieces[clickedCell]->name  == "King" && cellsToPieces[previousClickedCell]->name  == "Rook")
        {
            qDebug() << 0 << Qt::endl;
            if ((static_cast<Rook*>(cellsToPieces[previousClickedCell]) -> FirstMoveRook == false) && (static_cast<King*>(cellsToPieces[clickedCell]) ->FirstMoveKing == false))
            {
                qDebug() << 1 << Qt::endl;
                if (turn == cellsToPieces[previousClickedCell]->color && turn == cellsToPieces[clickedCell]->color)
                {
                     qDebug() << 2 << Qt::endl;
                     if (previousClickedCell->column == 0 && previousClickedCell->row == 7)
                     {
                          qDebug() << 3 << Qt::endl;
                          //pohodi
                         cellsToPieces2 = cellsToPieces;
                         cellsToPieces2.detach();
                         cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                         cellsToPieces2.remove(previousClickedCell);
                         if (!shah(cellsToPieces2, turn))
                         {
                             cellsToPieces[previousClickedCell]->setPos((&cells[3][7])->pos());
                             cellsToPieces.insert(&cells[3][7], cellsToPieces[previousClickedCell]);
                             cellsToPieces[clickedCell]->setPos((&cells[2][7])->pos());
                             cellsToPieces.insert(&cells[2][7], cellsToPieces[clickedCell]);
                             cellsToPieces.remove(previousClickedCell);
                             cellsToPieces.remove(clickedCell);
                             turn = !turn;
                        }
                      }

                      else if (previousClickedCell->column == 7 && previousClickedCell->row == 7)
                      {
                          //pohodi
                         cellsToPieces2 = cellsToPieces;
                         cellsToPieces2.detach();
                         cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                         cellsToPieces2.remove(previousClickedCell);
                         if (!shah(cellsToPieces2, turn))
                         {
                             cellsToPieces[previousClickedCell]->setPos((&cells[5][7])->pos());
                             cellsToPieces[clickedCell]->setPos((&cells[6][7])->pos());
                             cellsToPieces.insert(&cells[6][7], cellsToPieces[clickedCell]);
                             cellsToPieces.insert(&cells[5][7], cellsToPieces[previousClickedCell]);
                             cellsToPieces.remove(previousClickedCell);
                             cellsToPieces.remove(clickedCell);
                             turn = !turn;
                        }
                      }

                    else if (previousClickedCell->column == 0 && previousClickedCell->row == 0)
                    {
                        //pohodi
                         cellsToPieces2 = cellsToPieces;
                         cellsToPieces2.detach();
                        cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces2.remove(previousClickedCell);
                        if (!shah(cellsToPieces2, turn))
                        {
                            cellsToPieces[previousClickedCell]->setPos((&cells[3][0])->pos());
                            cellsToPieces[clickedCell]->setPos((&cells[2][0])->pos());
                            cellsToPieces.insert(&cells[2][0], cellsToPieces[clickedCell]);
                            cellsToPieces.insert(&cells[3][0], cellsToPieces[previousClickedCell]);
                            cellsToPieces.remove(previousClickedCell);
                            cellsToPieces.remove(clickedCell);
                            turn = !turn;
                       }
                     }

                     else if (previousClickedCell->column == 7 && previousClickedCell->row == 0)
                     {
                        //pohodi
                         cellsToPieces2 = cellsToPieces;
                         cellsToPieces2.detach();
                        cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces2.remove(previousClickedCell);
                        if (!shah(cellsToPieces2, turn))
                        {
                            cellsToPieces[previousClickedCell]->setPos((&cells[5][0])->pos());
                            cellsToPieces[clickedCell]->setPos((&cells[6][0])->pos());
                            cellsToPieces.insert(&cells[6][0], cellsToPieces[clickedCell]);
                            cellsToPieces.insert(&cells[5][0], cellsToPieces[previousClickedCell]);
                            cellsToPieces.remove(previousClickedCell);
                            cellsToPieces.remove(clickedCell);
                            turn = !turn;
                        }
                     }
                  }
              }
        }
        else
        {
            if (cellsToPieces[previousClickedCell]->figureCanMove(previousClickedCell, clickedCell) &&
                    wayIsFree(previousClickedCell, clickedCell))
            {
                if (cellsToPieces.contains(clickedCell))
                {
                    if (cellsToPieces[previousClickedCell]->color != cellsToPieces[clickedCell]->color)
                    {

                     //pohodi
                        cellsToPieces2 = cellsToPieces;
                        cellsToPieces2.detach();
                        cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces2.remove(previousClickedCell);
                        if (!shah(cellsToPieces2, turn))
                        {
                            cellsToPieces[clickedCell]->setPixmap(QPixmap());
                            cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                            cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                            cellsToPieces.remove(previousClickedCell);
                            turn = !turn;
                        }
                    }
                }
                else
                {
                    //pohodi
                    cellsToPieces2 = cellsToPieces;
                    cellsToPieces2.detach();
                    cellsToPieces2.insert(clickedCell, cellsToPieces[previousClickedCell]);
                    cellsToPieces2.remove(previousClickedCell);
                    if (!shah(cellsToPieces2, turn))
                    {
                        cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
                        cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
                        cellsToPieces.remove(previousClickedCell);
                        turn = !turn;
                    }
                }
            }
        }
    }

    std::pair<Cell*, bool> temp = this->pawnAtEnd(!turn);
    if (temp.second && ((withComp && turn == compColor) || !withComp)) {
        pawnToReplace = temp.first;
        this->replacePawn();
    }
    else if (temp.second && withComp && turn != compColor) {
        pawnToReplace = temp.first;
        cellsToPieces[pawnToReplace]->setPixmap(QPixmap());
        cellsToPieces.remove(pawnToReplace);
        cellsToPieces[pawnToReplace] = new Queen(pawnToReplace->x(), pawnToReplace->y(), !turn);
        this->addItem(cellsToPieces.value(pawnToReplace));
    }

    if (this->shah(cellsToPieces, turn)) {
        emit shahSignal();
    }
    else {
        emit hideShah();
    }

    if (withComp && compColor == turn) {
        emit compMove();
    }
}

bool Board::wayIsFree(Cell * start, Cell * end) {
    QVector<Cell*> temp;

    if (cellsToPieces[start]->name == "Knight") {
        return true;
    }

    if (start->column == end->column)
    {
        for (int i = qMin(start->row, end->row) + 1; i < qMax(start->row, end->row); ++i)
        {
            temp.push_back(&cells[end->column][i]);
        }
    }

    else if (start->row == end->row)
    {
        for (int i = qMin(start->column, end->column) + 1; i < qMax(start->column, end->column); ++i)
        {
            temp.push_back(&cells[i][end->row]);
        }
    }
    else if (abs(start->column - end->column) == abs(start->row  - end->row))
    {
       if (start->column >= end->column) {
           if (start->row >= end->row) {
               for (int i = 1; i < start->column - end->column; ++i)
               {
                   temp.push_back(&cells[start->column - i][start->row - i]);
               }
           }
           else if (start->row < end->row){
               for (int i = 1; i < start->column - end->column; ++i)
               {
                   temp.push_back(&cells[end->column + i][end->row - i]);
               }
           }
       }
       else {
           if (start->row >= end->row) {
               for (int i = 1; i < end->column - start->column; ++i)
               {
                   temp.push_back(&cells[start->column + i][start->row - i]);
               }
           }
           else {
               for (int i = 1; i < end->column - start->column; ++i)
               {
                   temp.push_back(&cells[start->column + i][start->row + i]);
               }
           }
       }
    }

    for (auto cell : temp)
    {
        if (cellsToPieces.contains(cell)) {
            return false;
        }
    }
    return true;  
}

bool Board::wayIsFree2(Cell * start, Cell * end) {
    QVector<Cell*> temp;

    if (start->column == end->column)
    {
        for (int i = qMin(start->row, end->row) + 1; i < qMax(start->row, end->row); ++i)
        {
            temp.push_back(&cells[end->column][i]);
        }
    }

    else if (start->row == end->row)
    {
        for (int i = qMin(start->column, end->column) + 1; i < qMax(start->column, end->column); ++i)
        {
            temp.push_back(&cells[i][end->row]);
        }
    }
    else if (abs(start->column - end->column) == abs(start->row  - end->row))
    {
       if (start->column >= end->column) {
           if (start->row >= end->row) {
               for (int i = 1; i < start->column - end->column; ++i)
               {
                   temp.push_back(&cells[start->column - i][start->row - i]);
               }
           }
           else if (start->row < end->row){
               for (int i = 1; i < start->column - end->column; ++i)
               {
                   temp.push_back(&cells[end->column + i][end->row - i]);
               }
           }
       }
       else {
           if (start->row >= end->row) {
               for (int i = 1; i < end->column - start->column; ++i)
               {
                   temp.push_back(&cells[start->column + i][start->row - i]);
               }
           }
           else {
               for (int i = 1; i < end->column - start->column; ++i)
               {
                   temp.push_back(&cells[start->column + i][start->row + i]);
               }
           }
       }
    }

    for (auto cell : temp)
    {
        if (cellsToPieces2.contains(cell))
            return false;
    }
    return true;
}


int Board::countSum(QMap<Cell*, ChessPiece *> pieces, bool color) {
    int sum = 0;
    for (int i = 0; i < 8; i++) {
        for  (int j = 0; j < 8; j ++) {
            if (pieces.contains(&cells[i][j])) {
                if (pieces[&cells[i][j]]->color == color) {
                    sum += pieces[&cells[i][j]]->weight;
                }
            }
        }
    }

    return sum;
}


QVector<Move> Board::getPossibleMoves(bool color) {
    QVector<Move> result;
    for (auto it = cellsToPieces.begin(); it != cellsToPieces.end(); it++)
    {
        if (it.value()->color == color)
        {
            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 8; ++j)
                {
                    cellsToPieces2 = cellsToPieces;
                    cellsToPieces2.detach();
                    cellsToPieces2.insert(&cells[i][j], cellsToPieces[it.key()]);
                    cellsToPieces2.remove(it.key());
                    if (cellsToPieces[it.key()]->name == "Pawn")
                    {
                        if (abs(it.key()->column - (&cells[i][j])->column) == abs(it.key()->row - (&cells[i][j])->row) )
                        {
                            if (cellsToPieces.contains(&cells[i][j]))
                                static_cast<Pawn*>(cellsToPieces[it.key()])->forpawn = true;
                            else
                                static_cast<Pawn*>(cellsToPieces[it.key()])->forpawn = false;
                        }

                        if (it.key()->column == (&cells[i][j])->column )
                        {
                            if (cellsToPieces.contains(&cells[i][j]))
                                static_cast<Pawn*>(cellsToPieces[it.key()])->pered = true;
                            else
                                static_cast<Pawn*>(cellsToPieces[it.key()])->pered = false;
                        }
                    }
                    if (cellsToPieces[it.key()]->figureCanMove(it.key(), &cells[i][j]) && wayIsFree(it.key(), &cells[i][j]) &&
                            ((cellsToPieces.contains(&cells[i][j]) && cellsToPieces[it.key()]->color != cellsToPieces[&cells[i][j]]->color) || !cellsToPieces.contains(&cells[i][j]))
                            && !shah(cellsToPieces2, color))
                    {
                        int difference  = countSum(cellsToPieces, !color) - countSum(cellsToPieces2, !color);
                        if (shah(cellsToPieces2, color)) {
                            difference = 100;
                        }
                        result.push_back({it.key(), &cells[i][j], (int)difference});
                    }
                }
            }
        }
    }

    return result;
}

void Board::setBlackCompColor() {
    compColor = false;
}

void Board::setWhiteCompColor() {
    compColor = true;
}

void Board::addQueen()
{
    cellsToPieces[pawnToReplace]->setPixmap(QPixmap());
    cellsToPieces.remove(pawnToReplace);
    cellsToPieces[pawnToReplace] = new Queen(pawnToReplace->x(), pawnToReplace->y(), withComp ? turn : !turn);
    this->addItem(cellsToPieces.value(pawnToReplace));
    b1->hide();
    b2->hide();
    b3->hide();
    b4->hide();
}

void Board::addRook()
{
    cellsToPieces[pawnToReplace]->setPixmap(QPixmap());
    cellsToPieces.remove(pawnToReplace);
    cellsToPieces[pawnToReplace] = new Rook(pawnToReplace->x(), pawnToReplace->y(), withComp ? turn : !turn);
    this->addItem(cellsToPieces.value(pawnToReplace));
    b1->hide();
    b2->hide();
    b3->hide();
    b4->hide();
}

void Board::addKnight()
{
    cellsToPieces[pawnToReplace]->setPixmap(QPixmap());
    cellsToPieces.remove(pawnToReplace);
    cellsToPieces[pawnToReplace] = new Knight(pawnToReplace->x(), pawnToReplace->y(), withComp ? turn : !turn);
    this->addItem(cellsToPieces.value(pawnToReplace));
    b1->hide();
    b2->hide();
    b3->hide();
    b4->hide();
}

void Board::addBishop()
{
    cellsToPieces[pawnToReplace]->setPixmap(QPixmap());
    cellsToPieces.remove(pawnToReplace);
    cellsToPieces[pawnToReplace] = new Bishop(pawnToReplace->x(), pawnToReplace->y(), withComp ? turn : !turn);
    this->addItem(cellsToPieces.value(pawnToReplace));
    b1->hide();
    b2->hide();
    b3->hide();
    b4->hide();
}

void Board::closeShahWindow()
{
    n->hide();
}


bool Board::shah(QMap<Cell*, ChessPiece *> pieces, bool color) {
    Cell * kingCell;
    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if (it.value()->color == color && it.value()->name == "King") {
            kingCell = it.key();
        }
    }

    for (auto it = pieces.begin(); it != pieces.end(); ++it) {
        if (it.value()->color != color) {
            if (pieces[it.key()]->name == "Pawn") {
                if (abs(it.key()->column - kingCell->column) == abs(it.key()->row - kingCell->row) )
                {
                    if (pieces.contains(clickedCell))
                        static_cast<Pawn*>(pieces[it.key()])->forpawn = true;
                    else
                        static_cast<Pawn*>(pieces[it.key()])->forpawn = false;
                }

                if (it.key()->column == kingCell->column )
                {
                    if (pieces.contains(kingCell))
                        static_cast<Pawn*>(pieces[it.key()])->pered = true;
                    else
                        static_cast<Pawn*>(pieces[it.key()])->pered = false;
                }
            }
            if (pieces[it.key()]->figureCanMove(it.key(), kingCell) &&
                    wayIsFree2(it.key(), kingCell)) {
                return true;
            }
        }
    }

    return false;
}

std::pair<Cell *, bool> Board::pawnAtEnd(bool color) {
    for (auto it = cellsToPieces.begin(); it != cellsToPieces.end(); ++it) {
        if (it.value()->color == color && it.value()->name == "Pawn") {
            if ((it.value()->color && it.key()->row == 0) || (!it.value()->color && it.key()->row == 7)) {
                return std::make_pair(it.key(), true);
            }
        }
    }
    return std::make_pair(nullptr, false);
}

void Board::replacePawn()
{
    QObject::connect(b1, &QPushButton::clicked, this, &Board::addQueen);
    b1->setGeometry(0,0,800,200);
    this->addWidget(b1);
    b1->show();
    QObject::connect(b2, &QPushButton::clicked, this, &Board::addRook);
    b2->setGeometry(0,200,800,200);
    this->addWidget(b2);
    b2->show();
    QObject::connect(b3, &QPushButton::clicked, this, &Board::addKnight);
    b3->setGeometry(0,400,800,200);
    b3->show();
    this->addWidget(b3);
    QObject::connect(b4, &QPushButton::clicked, this, &Board::addBishop);
    b4->setGeometry(0,600,800,200);
    b4->show();
    this->addWidget(b4);
}

