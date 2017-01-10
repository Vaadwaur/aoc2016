#include "direction.h"

namespace aoc2016 {

Direction operator--(Direction& dir)
{
    switch (dir) {
        case Direction::kEast:
            dir = Direction::kNorth;
            break;
        case Direction::kNorth:
            dir = Direction::kWest;
            break;
        case Direction::kWest:
            dir = Direction::kSouth;
            break;
        case Direction::kSouth:
            dir = Direction::kEast;
            break;
    }

    return dir;
}

Direction operator++(Direction& dir)
{
    switch (dir) {
        case Direction::kEast:
            dir = Direction::kSouth;
            break;
        case Direction::kSouth:
            dir = Direction::kWest;
            break;
        case Direction::kWest:
            dir = Direction::kNorth;
            break;
        case Direction::kNorth:
            dir = Direction::kEast;
            break;
    }

    return dir;
}

}  // namespace aoc2016
