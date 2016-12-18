#include <regex>
#include <days.h>

namespace aoc2016 {

namespace {

std::regex const marker_re{R"(\((\d+)x(\d+)\))", std::regex::optimize};

}

static uint64_t
simple_decompress(std::string_view const view)
{
	std::cmatch matches;
	if (!std::regex_search(view.data(), view.data() + view.length(), matches, marker_re)) {
		return view.length();
	}
	auto const marker_begin{matches.position()};
	auto const marker_end{marker_begin + matches.length()};
	auto const amount{std::stoul(matches[1])};
	auto const repeats{std::stoul(matches[2])};

	auto const size = simple_decompress(view.substr(marker_end + amount));

	return size + marker_begin + amount * repeats;
}

static uint64_t
part1(std::istream& _is)
{
	uint64_t counter{};
	for (std::string line; std::getline(_is, line);) {
		counter += simple_decompress(line);
	}

	return counter;
}

static uint64_t
recursive_decompress(std::string_view const view)
{
	std::cmatch matches;
	if (!std::regex_search(view.data(), view.data() + view.length(), matches, marker_re)) {
		return view.length();
	}
	auto const marker_begin{matches.position()};
	auto const marker_end{marker_begin + matches.length()};
	auto const amount{std::stoul(matches[1])};
	auto const repeats{std::stoul(matches[2])};

	auto const recursive_size = recursive_decompress(view.substr(marker_end, amount));
	auto const size = recursive_decompress(view.substr(marker_end + amount));

	return size + recursive_size * repeats;
}

static uint64_t
part2(std::istream& _is)
{
	uint64_t counter{};
	for (std::string line; std::getline(_is, line);) {
		counter += recursive_decompress(line);
	}

	return counter;
}

template<> std::string
solve<kDay09>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1(_is) : part2(_is));
}

} // namespace aoc2016
