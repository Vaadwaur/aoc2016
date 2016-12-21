#include <algorithm>
#include <cassert>
#include "scrambler.h"

namespace aoc2016 {

void
Scrambler::MovePos(size_t pos1, size_t pos2)
{
	char ch = str_[pos1];
	str_.erase(str_.begin() + pos1);
	str_.insert(str_.begin() + pos2, ch);
}

void
Scrambler::ReversePos(size_t pos1, size_t pos2)
{
	auto beg = str_.begin();
	std::reverse(beg + pos1, beg + pos2 + 1);
}

void
Scrambler::RotateDir(Direction dir, size_t steps)
{
	steps %= str_.length();
	if (dir == Direction::LEFT) {
		std::rotate(str_.begin(), str_.begin() + steps, str_.end());
	}
	else {
		std::rotate(str_.rbegin(), str_.rbegin() + steps, str_.rend());
	}
}

void
Scrambler::RotateChPos(char letter)
{
	size_t steps = str_.find(letter) + 1;

	// rotate right
	if (steps > 4) {
		++steps;
	}
	steps %= str_.length();
	std::rotate(str_.rbegin(), str_.rbegin() + steps, str_.rend());
}

void
Scrambler::SwapPos(size_t pos1, size_t pos2)
{
	std::swap(str_[pos1], str_[pos2]);
}

void
Scrambler::SwapCh(char letter1, char letter2)
{
	size_t pos1 = str_.find(letter1);
	size_t pos2 = str_.find(letter2);
	std::swap(str_[pos1], str_[pos2]);
}

std::string
Scrambler::operator*() const
{
	return str_;
}

}
