#include <numeric>
#include <days.h>

namespace aoc2016 {

static auto
part1()
{
	std::array<char, 6> positions{ 7, 13, 3, 5, 17, 19 };
	std::array<char, 6> start{ 0, 0, 2, 2, 0, 7 };
	std::array<bool, 6> result{};
	uint64_t counter{};
	bool succeeded{};
	do {
		for (size_t i{}; i < positions.size(); ++i) {
			result[i] = (counter + start[i] + i + 1) % positions[i] == 0;
		}
		succeeded = std::accumulate(std::cbegin(result), std::cend(result), true, [](auto& init, auto const& val) {
			return init && val;
		});
		++counter;
	} while (!succeeded);

	return counter - 1;
}

static auto
part2()
{
	std::array<char, 7> positions{ 7, 13, 3, 5, 17, 19, 11 };
	std::array<char, 7> start{ 0, 0, 2, 2, 0, 7, 0 };
	std::array<bool, 7> result{};
	uint64_t counter{};
	bool succeeded{};
	do {
		for (size_t i{}; i < positions.size(); ++i) {
			result[i] = (counter + start[i] + i + 1) % positions[i] == 0;
		}
		succeeded = std::accumulate(std::cbegin(result), std::cend(result), true, [](auto& init, auto const& val) {
			return init && val;
		});
		++counter;
	} while (!succeeded);

	return counter - 1;
}

template<> std::string
solve<kDay15>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1() : part2());
}

} // namespace aoc2016
