#include <memory>
#include <vector>
#include <days.h>

namespace aoc2016 {

namespace {

using tBlockRange = std::pair<uint32_t, uint32_t>;
using tBlockRanges = std::vector<tBlockRange>;

}

static uint32_t 
part1(tBlockRanges const& ranges)
{
	// ranges must be sorted
	uint32_t counter{};
	auto it = ranges.cbegin();
	while (counter >= it->first) {
		counter = std::max(counter, it->second + 1);
		++it;
	}

	return counter;
}

static uint32_t
part2(tBlockRanges const& ranges)
{
	constexpr uint64_t const len = (uint64_t(1) << 32);

	// vector<bool> requires 1/8th of the memory. If you can spare the memory,
	// array of bool is much faster to execute than vector<bool>
	//std::vector<bool> availability(len, true);
	auto availability = std::make_unique<bool[]>(len);
	std::fill_n(availability.get(), len, true);

	for (auto const& range : ranges) {
		for (uint64_t i{range.first}; i <= range.second; ++i) {
			availability[i] = false;
		}
	}

	uint32_t counter{};
	for (uint64_t i{}; i < len; ++i) {
		if (availability[i]) {
			++counter;
		}
	}

	return counter;
}

static tBlockRanges
get_ranges(std::istream& _is)
{
	tBlockRanges ranges;
	for (std::string line; std::getline(_is, line);) {
		auto pos = line.find('-');
		uint32_t first = std::stoul(line.substr(0, pos));
		uint32_t second = std::stoul(line.substr(pos + 1));
		ranges.emplace_back(first, second);
	}
	std::sort(std::begin(ranges), std::end(ranges));

	return ranges;
}

template<> std::string
solve<kDay20>(bool _part1, std::istream& _is, std::ostream& _os)
{
	auto ranges = get_ranges(_is);

	return std::to_string(_part1 ? part1(ranges) : part2(ranges));
}

} // namespace aoc2016
