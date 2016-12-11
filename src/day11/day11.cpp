#include <vector>
#include <days.h>

namespace aoc2017 {

using tFloorMap = std::vector<char>;

static auto
get_items(std::istream& _is)
{
	tFloorMap floor_map;
	//int floor{}; // assume first line is first floor and counting up for each line
	for (std::string line; std::getline(_is, line); /*++floor*/) {
		auto count = std::count(std::cbegin(line), std::cend(line), ',');
		bool found_something = std::string::npos == line.find("nothing");
		if (found_something) {
			++count; // number of items = number of commas + 1
		}
		floor_map.push_back(count);
	}
	
	return floor_map;
}

static auto
get_steps(std::istream& _is, tFloorMap _floor_map)
{
	/* my input was 10 items in total
	F4
	F3   TM
	F2   TG RG RM CG CM
	F1 E SG SM PG PM
	*/
	size_t moves_required{};
	for (size_t start{}; start < _floor_map.size() - 1; ++start) {
		auto items_on_current_floor = _floor_map[start];
		// steps required to move current floors items up one floor
		moves_required += 2 * (items_on_current_floor - 1) - 1;
		// add items on current floor to floor above
		_floor_map[start + 1] += items_on_current_floor;
	}

	return moves_required;
}

template<> std::string
solve<kDay11>(bool _part1, std::istream& _is, std::ostream& _os)
{
	auto floor_map = get_items(_is);
	size_t answer;
	if (_part1) {
		answer = get_steps(_is, floor_map);
	}
	else {
		floor_map[0] += 4; // found 4 extra items on first floor
		answer = get_steps(_is, floor_map);
	}

	return std::to_string(answer);
}

} // namespace aoc2017
