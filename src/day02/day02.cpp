#include <days.h>
#include <map>

namespace aoc2016 {

static std::string
part1(std::istream& is_)
{
    std::map<char, std::array<char, 9>> lookup = {{'D', {3, 4, 5, 6, 7, 8, 6, 7, 8}},
                                                  {'L', {0, 0, 1, 3, 3, 4, 6, 6, 7}},
                                                  {'R', {1, 2, 2, 4, 5, 5, 7, 8, 8}},
                                                  {'U', {0, 1, 2, 0, 1, 2, 3, 4, 5}}};
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
                break;
        }
    }

    return code;
}

static std::string
part2(std::istream& is_)
{
    std::map<char, std::array<char, 13>> lookup = {
        {'D', {0x2, 0x5, 0x6, 0x7, 0x4, 0x9, 0xa, 0xb, 0x8, 0x9, 0xc, 0xb, 0xc}},
        {'L', {0x0, 0x1, 0x1, 0x2, 0x4, 0x4, 0x5, 0x6, 0x7, 0x9, 0x9, 0xa, 0xc}},
        {'R', {0x0, 0x2, 0x3, 0x3, 0x5, 0x6, 0x7, 0x8, 0x8, 0xa, 0xb, 0xb, 0xc}},
        {'U', {0x0, 0x1, 0x0, 0x3, 0x4, 0x1, 0x2, 0x3, 0x8, 0x5, 0x6, 0x7, 0xa}}};
    std::map<char, char> keypad{{0x0, '1'}, {0x1, '2'}, {0x2, '3'}, {0x3, '4'}, {0x4, '5'},
                                {0x5, '6'}, {0x6, '7'}, {0x7, '8'}, {0x8, '9'}, {0x9, 'A'},
                                {0xa, 'B'}, {0xb, 'C'}, {0xc, 'D'}};
    char cur_pos{4};  // keypad 5 == position 4
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

template <>
std::string
solve<kDay02>(bool _part1, std::istream& _is, [[maybe_unused]] std::ostream& _os)
{
    return _part1 ? part1(_is) : part2(_is);
}

}  // namespace aoc2016
