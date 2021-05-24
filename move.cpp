#include "move.h"

bool Move::operator<(const Move &other) const {
        return  this->difference < other.difference;
}
