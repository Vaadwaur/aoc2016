#include <regex>
#include <days.h>

namespace aoc2017 {

static const std::regex marker_re{ R"((\d+)x(\d+))" };

static auto
decompress(std::string_view const view)
{
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

static std::pair<uint64_t, uint64_t>
get_marker(std::string marker)
{
	auto it = std::sregex_iterator(marker.begin(), marker.end(), marker_re);
	std::smatch match = *it;
	return {std::stoul(match[1]), std::stoul(match[2])};
}

static uint64_t
decompress2(std::string_view view)
{
	size_t pos{}, pos2;
	if (std::string_view::npos == (pos = view.find('('))) {
		return view.size();
	}
	std::string_view marker;
	uint64_t counter{};
	uint64_t marker_amount, marker_repeat;
	while (std::string_view::npos != (pos = view.find('(', pos))) {
		counter += pos;
		pos2 = view.find(')', pos);
		marker = view.substr(pos, pos2 - pos - 1);
		std::tie(marker_amount, marker_repeat) = get_marker(marker.data());
		std::string substr;
		substr.reserve(marker_amount * marker_repeat);
		for (int i{}; i < marker_repeat; ++i) {
			substr += view.substr(pos2 + 1, marker_amount);
		}
		counter += decompress2(substr);
		view.remove_prefix(pos2 + 1 + marker_amount);
		pos = 0;
	}

	return counter;
}

static auto
part2(std::istream& _is)
{
	std::string data, marker;
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

} // namespace aoc2017
