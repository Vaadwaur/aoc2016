#include <map>
#include <iomanip>
#include <sstream>
#include <days.h>

namespace aoc2016 {

namespace {

struct Node
{
	uint64_t avail;
	uint64_t used;
};

int smallest_node_size;
int max_x;
int max_y;

using tNodes = std::map<std::pair<int, int>, Node>;

}

static auto
part1(tNodes const& nodes)
{
	uint32_t counter{};
	for (auto const& node : nodes) {
		for (auto const& i_node : nodes) {
			if (node.first != i_node.first && node.second.used > 0 && node.second.used <= i_node.second.avail) {
				++counter;
			}
		}
	}

	return counter;
}

static auto
part2(tNodes const& nodes, std::ostream& _os)
{
	tNodes::const_iterator node_it;
	bool first{true};
	int empty_pos_x, empty_pos_y;
	_os << "\n   ";
	_os << std::right;
	for (int x{}; x <= max_x; ++x) {
		_os << std::setw(2) << x;
	}
	_os << '\n';

	for (int y{}; y <= max_y; ++y) {
		int x{};
		_os << std::setw(2) << y << ' ';
		for (x = 0; x <= max_x; ++x) {
			_os << ' ';
			node_it = nodes.find({ x, y });
			if (node_it->second.used == 0) {
				_os << '_';
				empty_pos_x = x;
				empty_pos_y = y;
			}
			else if (node_it->second.used > smallest_node_size) {
				_os << '#';
			}
			else if (x == 0 && y == 0) {
				_os << 'X';
			}
			else {
				_os << '.';
			}
		}
		if (first) {
			_os << "\bG";
			first = false;
		}
		_os << '\n';
	}
	_os << "Empty node (_) at pos " << empty_pos_x << ',' << empty_pos_y <<
		"\n1. Taxicab geometry - move _ to the top row. (diff x + diff y moves). # cannot be crossed.\n"
		"2. Then move _ all the way to the right where G is.\n"
		"3. Add (max_x - 1) * 5 = " << (max_x - 1) << " * 5 = " << ((max_x - 1) * 5);

	return std::string();
}

static auto
get_input(std::istream& _is)
{
	tNodes nodes;
	smallest_node_size = std::numeric_limits<int>::max();
	max_x = max_y = 0;
	std::string word;

	for (std::string line; std::getline(_is, line);) {
		if (line[0] != '/') {
			continue;
		}
		size_t pos = line.find('x');
		auto node_x = std::stoi(line.data() + pos + 1);
		max_x = std::max(max_x, node_x);
		pos = line.find('y');
		auto node_y = std::stoi(line.data() + pos + 1);
		max_y = std::max(max_y, node_y);
		std::stringstream ss{line};
		ss >> word;
		ss >> word;
		auto size = std::stoi(word);
		smallest_node_size = std::min(smallest_node_size, size);
		ss >> word;
		auto used = std::stoull(word);
		ss >> word;
		auto avail = std::stoull(word);
		nodes[{node_x, node_y}] = {avail, used};
	}

	return nodes;
}

template<> std::string
solve<kDay22>(bool _part1, std::istream& _is, std::ostream& _os)
{
	auto input = get_input(_is);
	return _part1 ? std::to_string(part1(input)) : part2(input, _os);
}

} // namespace aoc2016
