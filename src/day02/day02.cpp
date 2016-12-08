#include <map>
#include <days.h>

namespace aoc2017 {

std::string
part1(std::istream& is_)
{
	std::map<char, std::array<char, 9>> lookup = {
		{'D', {3,4,5,6,7,8,6,7,8}},
		{'L', {0,0,1,3,3,4,6,6,7}},
		{'R', {1,2,2,4,5,5,7,8,8}},
		{'U', {0,1,2,0,1,2,3,4,5}}
	};
	std::string code;
	char instruction;
	char cur_pos{4};
	while (is_.get(instruction)) {
		switch (instruction) {
		case '\n':
			code += cur_pos + 0x31;
			break;
		default:
			cur_pos = lookup[instruction][cur_pos];
		}
	}

	return code;
}


std::string
part2(std::istream& is_)
{
	std::map<char, std::array<char, 13>> lookup = {
		{'D',{ 2, 5, 6, 7, 4, 9,10,11, 8, 9,12,11,12 }},
		{'L',{ 0, 1, 1, 2, 4, 4, 5, 6, 7, 9, 9,10,12 }},
		{'R',{ 0, 2, 3, 3, 5, 6, 7, 8, 8,10,11,11,12 }},
		{'U',{ 0, 1, 0, 3, 4, 1, 2, 3, 8, 5, 6, 7,10 }}
	};
	std::map<char, char> keypad{
		{0,'1'},
		{1,'2'},
		{2,'3'},
		{3,'4'},
		{4,'5'},
		{5,'6'},
		{6,'7'},
		{7,'8'},
		{8,'9'},
		{9,'A'},
		{10,'B'},
		{11,'C'},
		{12,'D'}
	};
	char cur_pos{4}; // keypad 5 == position 4
	char instruction;
	std::string code;
	while (is_.get(instruction)) {
		switch (instruction) {
		case '\n':
			code += keypad[cur_pos];
			break;
		default:
			cur_pos = lookup[instruction][cur_pos];
			break;
		}
	}

	return code;
}


template<> std::string
solve<kDay02>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return _part1 ? part1(_is) : part2(_is);
}

} // namespace aoc2017
