#include <days.h>
#include <intrin.h>

namespace aoc2016 {

static uint32_t
part1(uint32_t const _num_elves)
{
    // Josephus problem.
    // answer = move highest order bit in num_elves and place it first
    // e.g. 1100011 -> 1000111
    uint32_t highest_order_set_bit = 31 - _lzcnt_u32(_num_elves);
    uint32_t answer = _num_elves - (1 << highest_order_set_bit);  // remove highest order set bit
    answer <<= 1;                                                 // shift to the left
    answer += 1;  // add the highest order set bit to the start

    return answer;
}

static uint32_t
part2(uint32_t const _num_elves)
{
    uint32_t chooser{1};
    uint32_t next{1};
    uint32_t prev{1};
    for (uint32_t i{1}; i <= _num_elves + 1; ++i) {
        if (chooser >= prev) {
            next = 2;
        }
        chooser += next;
        if (chooser > (i - 1)) {
            prev = i - next;
            chooser = next = 1;
        }
    }

    return chooser;
}

template <>
std::string
solve<kDay19>(bool _part1, std::istream& _is, [[maybe_unused]] std::ostream& _os)
{
    std::string input;
    _is >> input;
    auto elves = std::stoul(input);

    return std::to_string(_part1 ? part1(elves) : part2(elves));
}

}  // namespace aoc2016
