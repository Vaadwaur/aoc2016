#pragma once
#include <array>
#include <fstream>
#include <string>

namespace aoc2017 {

enum eDay {
	kFIRST_DAY = 0, kDay01 = 0, kDay02, kDay03, kDay04, kDay05, kDay06, kDay07,
	kDay08, kDay09, kDay10, kDay11, kDay12, kDay13, kDay14,
	kDay15, kDay16, kDay17, kDay18, kDay19, kDay20, kDay21,
	kDay22, kDay23, kDay24, kDay25, kNUM_DAYS
};

template <eDay DAY>
std::string solve(bool part1, std::istream& is, std::ostream& os)
{
	os << " part " << (part1 ? '1' : '2') << " is not implemented";
	if (!is.bad()) {
		os << " and input file does not exist\n";
	}

	return "";
}

} // namespace aoc2017
