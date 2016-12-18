#include <functional>
#include <utility>
#include <days.h>

namespace aoc2016 {

namespace {

using tData = std::array<std::array<char, 26>, 8>;
using tDataDataIt = tData::value_type::const_iterator;

}


static tData
get_data(std::istream& _is)
{
	tData data{};
	std::string line;
	while (std::getline(_is, line)) {
		for (int i{}; i < 8; ++i) {
			++data[i][line[i] - 'a'];
		}
	}

	return data;
}

static std::string
get_code(tData const& data, std::function<tDataDataIt(tDataDataIt,tDataDataIt)> const& fun)
{
	std::string code;
	for (size_t i{}; i < data.size(); ++i) {
		auto it = fun(std::cbegin(data[i]), std::cend(data[i]));
		char diff = static_cast<char>(std::distance(std::cbegin(data[i]), it));
		code += 'a' + diff;
	}

	return code;
}

static auto
part1(std::istream& _is)
{
	auto data = get_data(_is);
	auto code = get_code(data, [](tDataDataIt first, tDataDataIt last) {
		return std::max_element(first, last);
	});

	return code;
}

static auto
part2(std::istream& _is)
{
	auto data = get_data(_is);
	auto code = get_code(data, [](tDataDataIt first, tDataDataIt last) {
		return std::min_element(first, last);
	});

	return code;
}

template<> std::string
solve<kDay06>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return _part1 ? part1(_is) : part2(_is);
}

} // namespace aoc2016
