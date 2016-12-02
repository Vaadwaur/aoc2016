#include <days.h>
#include <map>

namespace aoc2017 {

void
move_left(char& button) {
	switch (button) {
	case 2:
	case 3:
	case 5:
	case 6:
	case 8:
	case 9:
		button -= 1;
		break;
	}
}

void move_right(char& button) {
	switch (button) {
	case 1:
	case 2:
	case 4:
	case 5:
	case 7:
	case 8:
		button += 1;
		break;
	}
}

void move_up(char& button) {
	if (button >= 4 && button <= 9) {
		button -= 3;
	}
}

void move_down(char& button) {
	if (button >= 1 && button <= 6) {
		button += 3;
	}
}
std::string
part1(std::istream& is_)
{
	std::string code;
	char button{5};
	char instruction;
	while (is_.get(instruction)) {
		switch (instruction) {
		case 'L':
			move_left(button);
			break;
		case 'R':
			move_right(button);
			break;
		case 'U':
			move_up(button);
			break;
		case 'D':
			move_down(button);
			break;
		case '\n':
			code += button + 0x30;
			break;
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


template<> void solve<kDay02>(bool part1_, std::istream& is_, std::ostream& os_)
{
	os_ << "day02:";
	if(part1_) {
		os_ << "part1:" << part1(is_);
	}
	else {
		os_ << "part2:" << part2(is_);
	}
}

} // namespace aoc2017
