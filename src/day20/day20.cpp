#include <memory>
#include <vector>
#include <days.h>

namespace aoc2016 {

namespace {

using tBlockRange = std::pair<uint64_t, uint64_t>;
using tBlockRanges = std::vector<tBlockRange>;

}

static uint64_t 
part1(tBlockRanges const& ranges)
{
	// ranges must be sorted
	uint64_t counter{};
	auto it = ranges.cbegin();
	while (counter >= it->first) {
		counter = std::max(counter, it->second + 1);
		++it;
	}

	return counter;
}

static tBlockRanges
compress_ranges(tBlockRanges const& ranges)
{
	tBlockRanges compressed;
	for (auto const& range : ranges) {
		bool merged{};
		for (auto& comp : compressed) {
			if (range.first >= comp.first && range.first <= (comp.second + 1)) {
				comp.second = std::max(comp.second, range.second);
				merged = true;
				break;
			}
		}
		if (!merged) {
			compressed.push_back(range);
		}
	}

	return compressed;
}

static uint64_t
part2(tBlockRanges& ranges)
{
	// ranges must be sorted and compressed
	ranges = compress_ranges(ranges);
	uint64_t counter{};
	tBlockRange prev{};
	for (auto range : ranges) {
		if (range.first > prev.second) {
			counter += (range.first - prev.second) - 1;
		}
		prev = range;
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
