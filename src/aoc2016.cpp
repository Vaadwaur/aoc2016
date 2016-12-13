#include <chrono>
#include <iostream>
#include <regex>
#include "days.h"

namespace aoc2016 {

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

extern template std::string solve<kDay01>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay02>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay03>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay04>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay05>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay06>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay07>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay08>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay09>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay10>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay11>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay12>(bool, std::istream&, std::ostream&);
extern template std::string solve<kDay13>(bool, std::istream&, std::ostream&);

template<typename T>
class ScopedTimer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start_;
	uint64_t &time_;
public:
	ScopedTimer(uint64_t& time) : time_(time), start_(std::chrono::high_resolution_clock::now()) {}
	~ScopedTimer() { time_ += std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - start_).count(); }
};

uint64_t
run(eDay day, bool part1, std::ostream& os)
{
	std::string filename{ "./input/" + day_to_string(day) + ".txt" };
	std::ifstream is{filename};
		
	std::string(*func)(bool, std::istream&, std::ostream&);
	switch (day) {
	case kDay01: func = &solve<kDay01>; break;
	case kDay02: func = &solve<kDay02>; break;
	case kDay03: func = &solve<kDay03>; break;
	case kDay04: func = &solve<kDay04>; break;
	case kDay05: func = &solve<kDay05>; break;
	case kDay06: func = &solve<kDay06>; break;
	case kDay07: func = &solve<kDay07>; break;
	case kDay08: func = &solve<kDay08>; break;
	case kDay09: func = &solve<kDay09>; break;
	case kDay10: func = &solve<kDay10>; break;
	case kDay11: func = &solve<kDay11>; break;
	case kDay12: func = &solve<kDay12>; break;
	case kDay13: func = &solve<kDay13>; break;
	default:
		func = nullptr;
	}
	uint64_t time{};
	std::string result;
	if (func != nullptr) {
		os << day_to_string(day) << ":part" << (part1 ? '1' : '2') << ':';
		{
			ScopedTimer<std::chrono::microseconds> timer(time);
			result = func(part1, is, os);
		}
		os << result << '\n';
	}

	return time;
}

} // namespace aoc2016

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
	using namespace aoc2016;
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
