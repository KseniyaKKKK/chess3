#include "board.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Board::Board()
{
    mouseWasPressed = false;
    previousClickedCell = NULL;
    clickedCell = NULL;
    connect(this, &Board::secondClick, this, &Board::move);
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

//тут какую-нибуд  проверку возможен ли ход
void Board::move()
{
    if (cellsToPieces.contains(previousClickedCell) &&
            cellsToPieces[previousClickedCell]->figureCanMove(previousClickedCell, clickedCell) &&
            (typeid(cellsToPieces[previousClickedCell]).name() != "Knight"  && wayIsFree(previousClickedCell, clickedCell)))
    {
        if (cellsToPieces.contains(clickedCell) && cellsToPieces[previousClickedCell]->color != cellsToPieces[clickedCell]->color) {
            //если клетка не пустая и в ней фигурка другого цвета
            cellsToPieces[clickedCell]->setPixmap(QPixmap());
            cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
            cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
            cellsToPieces.remove(previousClickedCell);
        } else if (!cellsToPieces.contains(clickedCell)){
            // если пустая клетка
            cellsToPieces[previousClickedCell]->setPos(clickedCell->pos());
            cellsToPieces.insert(clickedCell, cellsToPieces[previousClickedCell]);
            cellsToPieces.remove(previousClickedCell);
        }
    }
}

bool Board::wayIsFree(Cell * start, Cell * end) {
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

    else if (abs(start->column - end->column) == abs(start->row - end->row))
    {
        temp.push_back(&cells[end->column][end->row]);
    }

    for (auto cell : temp)
    {
        if (cellsToPieces.contains(cell))
            return false;
    }
    return true;
}

