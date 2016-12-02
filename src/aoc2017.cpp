#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "days.h"

namespace aoc2017 {

std::string day_to_string(eDay day)
{
	static const std::array<std::string, kNUM_DAYS> kDayLookup {
		"day01", "day02", "day03", "day04", "day05", "day06", "day07",
		"day08", "day09", "day10", "day11", "day12", "day13", "day14",
		"day15", "day16", "day17", "day18", "day19", "day20", "day21",
		"day22", "day23", "day24", "day25"
	};

	return kDayLookup[day];
}

extern template void solve<kDay01>(bool, std::istream&, std::ostream&);
extern template void solve<kDay02>(bool, std::istream&, std::ostream&);

void run(eDay day, bool part1, std::ostream& os)
{
	std::string filename{ "./input/" + day_to_string(day) + ".txt" };
	std::ifstream is{filename};
	switch (day) {
	case kDay01:
		solve<kDay01>(part1, is, os);
		break;
	case kDay02:
		solve<kDay02>(part1, is, os);
		break;
	default:
		return;
	}
	os << '\n';
}

} // namespace aoc2017


int main(int _argc, char** _argv)
{
	using namespace aoc2017;
	std::regex filter{".*"};
	if (_argc > 1) {
		filter = std::regex{_argv[1]};
	}
	for(int day{kFIRST_DAY}; day != kNUM_DAYS; ++day) {
		eDay solver { static_cast<eDay>(day) };
		if (!std::regex_search(day_to_string(solver), filter)) {
			continue;
		}
		run(solver, true, std::cout);
		run(solver, false, std::cout);
	}

	return EXIT_SUCCESS;
}