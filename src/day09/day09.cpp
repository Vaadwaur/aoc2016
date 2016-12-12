#include <regex>
#include <days.h>

namespace aoc2016 {

static auto
decompress(std::string_view const view)
{
	static const std::regex marker_re{R"(^(\d+)x(\d+))"};
	auto pos = view.find_first_of(")");
	uint64_t counter{pos + 1};
	std::string marker(view.data() + 1, pos - 1);
	auto it = std::sregex_iterator(marker.begin(), marker.end(), marker_re);
	std::smatch match = *it;
	auto num_chars = std::stoul(match[1]);
	auto repeats = std::stoul(match[2]);

	return std::make_pair(counter + num_chars, num_chars * repeats);
}

static auto
part1(std::istream& _is)
{
	uint64_t counter{};
	uint64_t move_size;
	for (std::string line; std::getline(_is, line);) {
		for (size_t i{}; i < line.length(); i += move_size) {
			if (line[i] == '(') {
				uint64_t result_size;
				std::tie(move_size, result_size) = decompress(std::string_view(line.data() + i));
				counter += result_size;
				continue;
			}
			move_size = 1;
			++counter;
		}
	}

	return counter;
}

std::string operator*(std::string_view const str, size_t repeats)
{
	std::string result;
	result.reserve(repeats * str.length());
	for (size_t i{}; i < repeats; ++i) {
		result += str;
	}

	return result;
}

static uint64_t
decompress2(std::string_view view)
{
	size_t marker_begin{};
	if (std::string_view::npos == (marker_begin = view.find('('))) {
		return view.size();
	}
	uint64_t counter{};
	while (std::string_view::npos != (marker_begin = view.find('(', marker_begin))) {
		decltype(view)::value_type const *p = view.data() + marker_begin;
		counter += marker_begin;

		size_t amount{}, repeat{};
		while (*++p != 'x') {
			amount = amount * 10 + (*p - '0');
		}
		while (*++p != ')') {
			repeat = repeat * 10 + (*p - '0');
		}

		ptrdiff_t marker_end = p - view.data() + 1;
		std::string substr{view.substr(marker_end, amount) * repeat};
		counter += decompress2(substr);
		view.remove_prefix(marker_end + amount);
		marker_begin = 0;
	}

	return counter;
}

static auto
part2(std::istream& _is)
{
	std::string data;
	for (std::string line; std::getline(_is, line);) {
		data += line;
	}

	return decompress2(data);
}

template<> std::string
solve<kDay09>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1(_is) : part2(_is));
}

} // namespace aoc2016
