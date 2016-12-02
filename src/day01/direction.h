#pragma once

namespace aoc2017 {

enum class Direction {
	kEast, kNorth, kWest, kSouth
};

Direction
operator--(Direction& dir);

Direction
operator++(Direction& dir);

} // namespace aoc2017
