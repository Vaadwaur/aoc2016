#include <algorithm>
#include <array>
#include <fstream>
#include <string_view>
#include <vector>
#include <days.h>

namespace aoc2017 {

static bool
contains_abba(std::string_view const view)
{
	int bracket{};
	bool found_abba{};
	decltype(view)::value_type last{}, cur;
	for (size_t i{1}; i < view.size() - 1; ++i, last = cur) {
		cur = view[i];
		if(last == cur) {
			auto next = view[i + 1];
			if (cur != next && view[i - 2] == next) {
				// found "ABBA"
				if (bracket) {
					return false;
				}
				found_abba = true;
			}
		}
		bracket += char(cur == '[') - char(cur == ']');
	}

	return found_abba;
}

static auto
part1(std::istream& _is)
{
	std::string line;
	size_t counter{};
	while (std::getline(_is, line)) {
		counter += contains_abba(line);
	}

	return counter;
}

static auto
find_aba(std::string_view const view)
{
	std::vector<std::array<char,2>> aba_found;
	int bracket{};
	decltype(view)::value_type last{}, cur;
	for (size_t i{}; i < view.size() - 1; ++i, last = cur) {
		cur = view[i];
		if (bracket == 0) {
			auto next = view[i + 1];
			if (cur != next && next == last) {
				aba_found.push_back({ last, cur });
			}
		}
		bracket += char(cur == '[') - char(cur == ']');
	}
	return aba_found;
}

static auto
find_bab(std::string_view const view, char a, char b)
{
	int bracket{};
	decltype(view)::value_type last{}, cur;
	for (size_t i{}; i < view.size() - 1; ++i, last = cur) {
		cur = view[i];
		if(bracket > 0) {
			if (cur == a && view[i + 1] == b && last == b) {
				return true;
			}
		}
		bracket += char(cur == '[') - char(cur == ']');
	}

	return false;
}

static auto
part2(std::istream& _is)
{
	std::string line;
	size_t counter{};
	while (std::getline(_is, line)) {
		auto all_aba_found = find_aba(line);
		for (auto const aba : all_aba_found) {
			if (find_bab(line, aba[0], aba[1])) {
				++counter;
				break;
			}
		}
	}
	return counter;
}

template<> std::string
solve<kDay07>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1(_is) : part2(_is));
}

} // namespace aoc2017
