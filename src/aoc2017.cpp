#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "days.h"

namespace aoc2017 {

std::string
day_to_string(eDay day)
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
extern template void solve<kDay03>(bool, std::istream&, std::ostream&);
extern template void solve<kDay04>(bool, std::istream&, std::ostream&);
extern template void solve<kDay05>(bool, std::istream&, std::ostream&);
extern template void solve<kDay06>(bool, std::istream&, std::ostream&);
extern template void solve<kDay07>(bool, std::istream&, std::ostream&);

uint64_t
run(eDay day, bool part1, std::ostream& os)
{
	using std::chrono::duration_cast;
	using std::chrono::microseconds;
	using std::chrono::high_resolution_clock;

	std::string filename{ "./input/" + day_to_string(day) + ".txt" };
	std::ifstream is{filename};
	auto start_time = high_resolution_clock::now();
	switch (day) {
	case kDay01:
		solve<kDay01>(part1, is, os);
		break;
	case kDay02:
		solve<kDay02>(part1, is, os);
		break;
	case kDay03:
		solve<kDay03>(part1, is, os);
		break;
	case kDay04:
		solve<kDay04>(part1, is, os);
		break;
	case kDay05:
		solve<kDay05>(part1, is, os);
		break;
	case kDay06:
		solve<kDay06>(part1, is, os);
		break;
	case kDay07:
		solve<kDay07>(part1, is, os);
		break;
	default:
		return 0;
	}
	auto diff_time = std::chrono::duration_cast<microseconds>(high_resolution_clock::now() - start_time);
	os << '\n';

	return diff_time.count();
}

} // namespace aoc2017

void
print_duration(std::ostream& _os, uint64_t const microseconds)
{
	if (microseconds > 0) {
		_os << "\tElapsed time:" << microseconds / 1.0e6 << "s\n";
	}
}

int
main(int _argc, char** _argv)
{
	using namespace aoc2017;
	std::regex filter{".*"};
	if (_argc > 1) {
		filter = std::regex{_argv[1]};
	}
	uint64_t total_time{};
	for(int day{kFIRST_DAY}; day != kNUM_DAYS; ++day) {
		eDay solver { static_cast<eDay>(day) };
		if (!std::regex_search(day_to_string(solver), filter)) {
			continue;
		}
		auto duration1 = run(solver, true, std::cout);
		print_duration(std::cout, duration1);
		auto duration2 = run(solver, false, std::cout);
		print_duration(std::cout, duration2);

		total_time += duration1 + duration2;
	}

	std::cout << "\nTotal elapsed time:" << total_time / 1.0e6 << "s\n";

	return EXIT_SUCCESS;
}
