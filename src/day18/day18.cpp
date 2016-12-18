#include <days.h>

namespace aoc2016 {

namespace {

enum Symbols : char {SAFE = '.', TRAP = '^'};

}

static auto
count_safe_tiles(std::istream& _is, std::string prev_row, uint64_t const kNumRows)
{
	uint64_t safe_counter{};

	// Pad with virtual safe rooms on left and right side.
	// These are removed in the end when counting safe rooms (reduce with kNumRows * 2).
	prev_row.insert(std::begin(prev_row), SAFE);
	uint8_t const row_len = static_cast<uint8_t const>(prev_row.length());
	prev_row += SAFE;
	std::string next_row{prev_row};

	std::array<char, 3> comp;
	constexpr std::array<decltype(comp), 4> const trap_combos{
		{
			{TRAP, TRAP, SAFE},
			{SAFE, TRAP, TRAP},
			{TRAP, SAFE, SAFE},
			{SAFE, SAFE, TRAP}
		}
	};

	uint64_t row{1};
	do {
		safe_counter += std::count(std::cbegin(prev_row), std::cend(prev_row), '.');
		for (uint8_t i{1}; i < row_len; ++i) {
			comp[0] = prev_row[i - 1];
			comp[1] = prev_row[i];
			comp[2] = prev_row[i + 1];

			auto is_trap = (comp == trap_combos[0]);
			is_trap |= (comp == trap_combos[1]);
			is_trap |= (comp == trap_combos[2]);
			is_trap |= (comp == trap_combos[3]);
			//auto  is_trap = std::any_of(std::cbegin(trap_combos), std::cend(trap_combos), [&](decltype(comp) const& trap) -> bool {
			//	return trap == comp;
			//});

			next_row[i] = (is_trap) ? TRAP : SAFE;
		}
		prev_row = next_row;
	} while (++row < kNumRows);
	safe_counter += std::count(std::cbegin(prev_row), std::cend(prev_row), '.');
	safe_counter -= kNumRows << 1; // do not count virtual safe rooms

	return safe_counter;
}

template<> std::string
solve<kDay18>(bool _part1, std::istream& _is, std::ostream& _os)
{
	std::string input;
	_is >> input;
	return std::to_string(_part1 ? count_safe_tiles(_is, input, 40) : count_safe_tiles(_is, input, 400000));
}

} // namespace aoc2016
