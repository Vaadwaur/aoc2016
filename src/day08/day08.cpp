#include <bitset>
#include <numeric>
#include <regex>
#include <days.h>

namespace aoc2016 {

static constexpr const size_t COLS = 50;
static constexpr const size_t ROWS = 6;
static constexpr const size_t CHAR_WIDTH = 5;
static constexpr const size_t CHAR_HEIGHT = ROWS;
static constexpr const size_t NUM_CHARS = COLS / CHAR_WIDTH;
using tDisplay = std::array<std::bitset<COLS>, ROWS>;
using tDisplayChar = std::bitset<CHAR_WIDTH * CHAR_HEIGHT>;

static void
rotate_row(tDisplay& display, char row, char amount)
{
	display[row] = display[row] << amount | display[row] >> (COLS - amount);
}

static void
rotate_col(tDisplay& display, char col, char amount)
{
	std::bitset<ROWS> bits;
	char counter{};
	for (auto const& row : display) {
		bits.set(counter++, row[col]);
	}
	bits = bits << amount | bits >> (ROWS - amount);
	counter = 0;
	for(auto& row : display) {
		row.set(col, bits[counter++]);
	}
}

static void
paint_rect(tDisplay& display, char x_size, char y_size)
{
	for (char y{}; y < y_size; ++y) {
		for (char x{}; x < x_size; ++x) {
			display[y].set(x);
		}
	}
}

static auto
part1(std::istream& _is, tDisplay& display)
{
	std::string line;
	std::regex re_rect{R"(^rect (\d+)x(\d+)$)"};
	std::regex re_rotate_row{R"(^rotate row y=(\d+) by (\d+)$)"};
	std::regex re_rotate_col{R"(^rotate column x=(\d+) by (\d+)$)"};
	while (std::getline(_is, line)) {
		std::smatch matches;
		if (std::regex_match(line, matches, re_rect)) {
			auto x = std::stoi(matches[1]);
			auto y = std::stoi(matches[2]);
			paint_rect(display, x, y);
		}
		else if (std::regex_match(line, matches, re_rotate_row)) {
			auto row = std::stoi(matches[1]);
			auto amount = std::stoi(matches[2]);
			rotate_row(display, row, amount);
		}
		else if (std::regex_match(line, matches, re_rotate_col)) {
			auto col = std::stoi(matches[1]);
			auto amount = std::stoi(matches[2]);
			rotate_col(display, col, amount);
		}
	}

	size_t sum = std::accumulate(std::cbegin(display), std::cend(display), size_t(0), [](size_t init, auto const& arr) {
		return init + arr.count();
	});

	return sum;
}

static std::array<tDisplayChar, 26> lookup_table{
	0b01100'10010'10010'11110'10010'10010, // A
	0b11100'10010'11100'10010'10010'11100, // B
	0b01100'10010'10000'10000'10010'01100, // C
	0b11100'10010'10010'10010'10010'11100, // D (not confirmed)
	0b11110'10000'11100'10000'10000'11110, // E
	0b11110'10000'11100'10000'10000'10000, // F
	0b01100'10010'10000'10110'10010'01110, // G
	0b10010'10010'11110'10010'10010'10010, // H
	0b01110'00100'00100'00100'00100'01110, // I
	0b00110'00010'00010'00010'10010'01100, // J
	0b10010'10100'11000'10100'10100'10010, // K
	0b10000'10000'10000'10000'10000'11110, // L
	0b10001'11011'10101'10001'10001'10001, // M (not confirmed)
	0b10001'11001'10101'10011'10001'10001, // N (not confirmed)
	0b01100'10010'10010'10010'10010'01100, // O
	0b11100'10010'10010'11100'10000'10000, // P
	0b01110'10001'10001'10101'10010'01101, // Q (not confirmed)
	0b11100'10010'10010'11100'10100'10010, // R
	0b01110'10000'10000'01100'00010'11100, // S
	0b11111'00100'00100'00100'00100'00100, // T (not confirmed)
	0b10010'10010'10010'10010'10010'01100, // U
	0b10001'10001'10001'01010'01010'00100, // V (not confirmed)
	0b10001'10001'10101'10101'10101'01010, // W (not confirmed)
	0b10001'01010'00100'01010'10001'10001, // X (not confirmed)
	0b10001'10001'01010'00100'00100'00100, // Y
	0b11110'00010'00100'01000'10000'11110  // Z
};

static tDisplayChar
get_display_char_data(tDisplay const& display, size_t pos)
{
	tDisplayChar ch;
	size_t ch_bit_pos = ch.size();
	size_t start_x{pos * CHAR_WIDTH}, end_x{(pos + 1) * CHAR_WIDTH};
	for (size_t row{}; row < display.size(); ++row) {
		for (auto x{start_x}; x < end_x; ++x) {
			ch[--ch_bit_pos] = display[row][x];
		}
	}

	return ch;
}

static std::string
translate_display(tDisplay display)
{
	std::string answer;
	for (size_t pos{}; pos < NUM_CHARS; ++pos) {
		auto display_char = get_display_char_data(display, pos);
		char real_char = 'A';
		for (auto const& lookup : lookup_table) {
			if (display_char == lookup) {
				answer += real_char;
				break;
			}
			++real_char;
		}
	}

	return answer;
}

static auto
part2(std::istream& _is, std::ostream& _os, tDisplay& display)
{
	part1(_is, display);
#ifdef DAY08_DISPLAY_PIXELS
	for (auto const& row : display) {
		_os << '\n';
		for (size_t i{}; i < row.size(); ++i) {
			_os << (row[i] ? '*' : ' ');
		}
	}
#endif
	return translate_display(display);
}

template<> std::string
solve<kDay08>(bool _part1, std::istream& _is, std::ostream& _os)
{
	tDisplay display{};
	return _part1 ? std::to_string(part1(_is, display)) : part2(_is, _os, display);
}

} // namespace aoc2016
