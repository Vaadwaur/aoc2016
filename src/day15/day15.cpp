#include <regex>
#include <days.h>

namespace aoc2016 {

namespace {

struct Disc
{
	char positions;
	char start_pos;
};

using tDiscs = std::vector<Disc>;

}


static uint64_t
part1(tDiscs const& discs)
{
	uint64_t counter{};
	bool successful;
	size_t const num_discs = discs.size();
	do {
		successful = true;
		for (size_t i{}; i < num_discs && successful; ++i) {
			successful &= (counter + discs[i].start_pos + i + 1) % discs[i].positions == 0;
		}

		++counter;
	} while (!successful);

	return counter - 1;
}

static auto
part2(tDiscs& discs)
{
	discs.push_back({ 11, 0 });
	return part1(discs);
}

static auto
read_input(std::istream& _is)
{
	tDiscs discs;
	static std::regex const input_re{R"(^Disc #\d+ has (\d+) positions; at time=0, it is at position (\d+).$)", std::regex_constants::optimize};
	std::smatch matches;
	for (std::string line; std::getline(_is, line); ) {
		if (std::regex_match(line, matches, input_re)) {
			char num_positions = static_cast<char>(std::stoi(matches[1]));
			char start_pos = static_cast<char>(std::stoi(matches[2]));
			discs.push_back({num_positions, start_pos});
		}
	}

	return discs;
}

template<> std::string
solve<kDay15>(bool _part1, std::istream& _is, std::ostream& _os)
{
	auto discs = read_input(_is);
	return std::to_string(_part1 ? part1(discs) : part2(discs));
}

} // namespace aoc2016
