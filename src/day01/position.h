#pragma once

namespace aoc2017 {

struct Position
{
	int x, y;

	Position
	operator+=(Position const& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	bool
	operator <(Position const& rhs) const {
		return y < rhs.y || (y == rhs.y && x < rhs.x);
	}
};

}
