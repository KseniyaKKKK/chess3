#ifndef MOVE_H
#define MOVE_H
#include "cell.h"


class Move
{
public:
    Cell* start;
    Cell* end;
    int difference;
    bool operator<(const Move &other) const;
};

#endif // MOVE_H
