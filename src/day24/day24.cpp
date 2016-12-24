#include <algorithm>
#include <map>
#include <vector>
#include <days.h>

namespace aoc2016 {

namespace {

enum eRoomType : uint8_t { UNCHECKED = 0xfe, WALL = 0xff };
uint8_t rooms_x{};
uint8_t rooms_y{};
using tDungeonMap = std::vector<std::vector<uint8_t>>;

}


static constexpr uint32_t
shortest_path_neighbour(tDungeonMap const& dungeon, int const pos_x, int const pos_y)
{
	uint8_t min = WALL;
	if (pos_y > 0) {
		// check row above
		auto test = std::min(dungeon[pos_y - 1][pos_x], min);
		min = std::min(test, min);
	}
	if (pos_x > 0) {
		// check room to the left
		auto test = std::min(dungeon[pos_y][pos_x - 1], min);
		min = std::min(test, min);
	}
	if (pos_x < rooms_x - 1) {
		// check room to the right
		auto test = std::min(dungeon[pos_y][pos_x + 1], min);
		min = std::min(test, min);
	}
	if (pos_y < rooms_y- 1) {
		// check room to the below
		auto test = std::min(dungeon[pos_y + 1][pos_x], min);
		min = std::min(test, min);
	}

	return min;
}

static tDungeonMap
get_path(tDungeonMap dungeon, uint32_t const start_pos_x, uint32_t const start_pos_y)
{
	// for each room...
	// calculate least number of steps required from starting position
	uint32_t counter{ 1 };
	dungeon[start_pos_y][start_pos_x] = 0;
	while (counter > 0) {
		counter = 0;
		for (uint8_t y{}; y < rooms_y; ++y) {
			for (uint8_t x{}; x < rooms_x; ++x) {
				auto room_value = dungeon[y][x];
				if (room_value < 0xff) {
					auto new_value = shortest_path_neighbour(dungeon, x, y) + 1;
					if (new_value < room_value) {
						// count number of rooms with improved score since last run
						++counter;
						dungeon[y][x] = new_value;
					}
				}
			}
		}
	}

	return dungeon;
}

static tDungeonMap
get_map(std::istream& _is)
{
	tDungeonMap dungeon;
	for (std::string line; std::getline(_is, line);) {
		std::vector<uint8_t> row;
		for (auto room : line) {
			switch (room) {
			case '#':
				room = WALL;
				break;
			case '.':
				room = UNCHECKED;
				break;
			}
			row.push_back(room);
		}
		dungeon.push_back(row);
	}

	return dungeon;
}

struct Pos
{
	uint8_t x;
	uint8_t y;
	bool operator<(Pos const& rhs) const {
		return y < rhs.y || (y == rhs.y && x < rhs.x);
	}
};

static auto
part1(std::istream& _is, std::ostream& _os)
{
	auto dungeon = get_map(_is);
	Pos entrance_pos;
	rooms_x = static_cast<uint8_t>(dungeon.begin()->size());
	rooms_y = static_cast<uint8_t>(dungeon.size());
	std::vector<Pos> interest_points;
	for (uint8_t y{}; y < rooms_y; ++y) {
		auto &row = dungeon[y];
		for (uint8_t x{}; x < rooms_x; ++x) {
			if (row[x] >= '0' && row[x] <= '9') {
				if (row[x] == '0') {
					entrance_pos.x = x;
					entrance_pos.y = y;
				}
				else {
					interest_points.push_back({x, y});
				}
				row[x] = UNCHECKED;
			}
		}
	}
	std::sort(interest_points.begin(), interest_points.end());

	std::map<Pos, tDungeonMap> maps;
	for (auto const& ip : interest_points) {
		auto path = get_path(dungeon, ip.x, ip.y);
		maps[ip] = std::move(path);
	}
	maps[entrance_pos] = get_path(dungeon, entrance_pos.x, entrance_pos.y);

	uint32_t best_path = std::numeric_limits<uint32_t>::max();
	_os << '\n';
	uint64_t counter{}, counter2{};
	do {
		uint32_t num_steps{};
		auto starting_point = entrance_pos;
		for (auto const& ip : interest_points) {
			auto const& path = maps[starting_point];
			num_steps += path[ip.y][ip.x];
			starting_point = ip;
		}
		//auto const& last_ip = interest_points.rbegin();
		//num_steps += path[last_ip.y][last_ip.x];
		++counter2;
		if (num_steps < best_path) {
			_os << "Counter:" << ++counter << ":" << counter2 << ", steps:" << num_steps << '\n';
		}
		best_path = std::min(best_path, num_steps);
	} while (std::next_permutation(std::begin(interest_points), std::end(interest_points)));

	return best_path;
}

static auto
part2(std::istream& _is, std::ostream& _os)
{
	auto dungeon = get_map(_is);
	Pos entrance_pos;
	rooms_x = static_cast<uint8_t>(dungeon.begin()->size());
	rooms_y = static_cast<uint8_t>(dungeon.size());
	std::vector<Pos> interest_points;
	for (uint8_t y{}; y < rooms_y; ++y) {
		auto &row = dungeon[y];
		for (uint8_t x{}; x < rooms_x; ++x) {
			if (row[x] >= '0' && row[x] <= '9') {
				if (row[x] == '0') {
					entrance_pos.x = x;
					entrance_pos.y = y;
				}
				else {
					interest_points.push_back({x, y});
				}
				row[x] = UNCHECKED;
			}
		}
	}
	std::sort(interest_points.begin(), interest_points.end());

	std::map<Pos, tDungeonMap> maps;
	for (auto const& ip : interest_points) {
		auto path = get_path(dungeon, ip.x, ip.y);
		maps[ip] = std::move(path);
	}
	maps[entrance_pos] = get_path(dungeon, entrance_pos.x, entrance_pos.y);

	uint32_t best_path = std::numeric_limits<uint32_t>::max();
	_os << '\n';
	uint64_t counter{}, counter2{};
	do {
		uint32_t num_steps{};
		auto starting_point = entrance_pos;
		for (auto const& ip : interest_points) {
			auto const& path = maps[starting_point];
			num_steps += path[ip.y][ip.x];
			starting_point = ip;
		}
		auto const last_ip = *interest_points.rbegin();
		num_steps += maps[last_ip][entrance_pos.y][entrance_pos.x];
		++counter2;
		if (num_steps < best_path) {
			_os << "Counter:" << ++counter << ":" << counter2 << ", steps:" << num_steps << '\n';
		}
		best_path = std::min(best_path, num_steps);
	} while (std::next_permutation(std::begin(interest_points), std::end(interest_points)));

	return best_path;
}

template<> std::string
solve<kDay24>(bool _part1, std::istream& _is, std::ostream& _os)
{
	if(_part1) {
		return "";
	}
	return std::to_string(_part1 ? part1(_is, _os) : part2(_is, _os));
}

} // namespace aoc2016
