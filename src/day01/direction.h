#pragma once

namespace aoc2016 {

enum class Direction {
	kEast, kNorth, kWest, kSouth
};

Direction
operator--(Direction& dir);

Direction
operator++(Direction& dir);

} // namespace aoc2016
