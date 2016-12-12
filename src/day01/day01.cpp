#include <iostream>
#include <set>
#include "position.h"
#include "direction.h"
#include <days.h>

namespace aoc2016 {

Position
follow_instruction(Direction const dir, std::string const& steps)
{
	Position pos{};
	auto nSteps = std::stoi(steps);
	switch (dir)
	{
	case Direction::kEast:
		pos.x += nSteps;
		break;
	case Direction::kNorth:
		pos.y += nSteps;
		break;
	case Direction::kWest:
		pos.x -= nSteps;
		break;
	case Direction::kSouth:
		pos.y -= nSteps;
		break;
	}

	return pos;
}

Position
follow_instruction(Direction const dir, std::string const& steps, Position& cur_pos, std::set<Position>& visited)
{
	auto nSteps = std::stoi(steps);
	do {
		switch (dir)
		{
		case Direction::kEast:
			++cur_pos.x;
			break;
		case Direction::kNorth:
			++cur_pos.y;
			break;
		case Direction::kWest:
			--cur_pos.x;
			break;
		case Direction::kSouth:
			--cur_pos.y;
			break;
		}
		auto lb = visited.lower_bound(cur_pos);
		if (lb != visited.end() && !(visited.key_comp()(cur_pos, *lb))) {
			// found already visited place
			throw std::overflow_error("found already visited place");
		}
		visited.insert(lb, cur_pos);
	} while (--nSteps > 0);
}


Position
part1(std::istream& file)
{
	char instruction;
	std::string steps;
	Position pos{};
	Direction dir{ Direction::kNorth };
	while (file.get(instruction)) {
		switch (instruction) {
		case 'L':
			--dir;
			break;
		case 'R':
			++dir;
			break;
		case ',':
			pos += follow_instruction(dir, steps);
			steps.clear();
			break;
		default:
			if (instruction >= '0' && instruction <= '9') {
				steps += instruction;
			}
		}
	}
	pos += follow_instruction(dir, steps);

	return pos;
}


Position
part2(std::istream& file)
{
	char instruction;
	std::string steps;
	Position pos{};
	Direction dir{ Direction::kNorth };
	std::set<Position> visited;
	visited.insert(pos);
	try {
		while (file.get(instruction)) {
			switch (instruction) {
			case 'L':
				--dir;
				break;
			case 'R':
				++dir;
				break;
			case ',': {
				follow_instruction(dir, steps, pos, visited);
				steps.clear();
				break;
			}
			default:
				if (instruction >= '0' && instruction <= '9') {
					steps += instruction;
				}
			}
		}
	}
	catch (std::overflow_error const&) {
		return pos;
	}
	follow_instruction(dir, steps, pos, visited);

	return pos;
}


template<> std::string
solve<kDay01>(bool _part1, std::istream& _is, std::ostream& _os)
{
	Position pos = _part1 ? part1(_is) : part2(_is);

	_os << (pos.x + pos.y) << " {" << pos.x << ',' << pos.y << '}';

	return "";
}

} // namespace aoc2016
