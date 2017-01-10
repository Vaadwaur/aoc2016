#include <days.h>
#include <regex>
#include "scrambler.h"

namespace aoc2016 {

namespace {

std::regex const swap_pos_re{R"(swap position (\d+) with position (\d+))",
                             std::regex_constants::optimize};
std::regex const swap_ch_re{R"(swap letter (.) with letter (.)$)", std::regex_constants::optimize};
std::regex const rotate_dir_re{R"(^rotate (\w+) (\d+) steps?$)", std::regex_constants::optimize};
std::regex const rotate_pos_re{R"(^rotate based on position of letter (.)$)",
                               std::regex_constants::optimize};
std::regex const reverse_pos_re{R"(^reverse positions (\d+) through (\d+)$)",
                                std::regex_constants::optimize};
std::regex const move_pos_re{R"(^move position (\d+) to position (\d+)$)",
                             std::regex_constants::optimize};
}

std::vector<std::string>
get_instructions(std::istream& _is)
{
    std::vector<std::string> instructions;
    for (std::string line; std::getline(_is, line);) {
        instructions.push_back(line);
    }

    return instructions;
}

static std::string
scramble(std::vector<std::string> const& instructions, std::string str, bool const reverse = false)
{
    Scrambler scrambler{str, reverse};

    std::smatch matches;
    for (auto it = instructions.cbegin(); it != instructions.cend(); ++it) {
        auto const& instruction = *it;
        if (std::regex_match(instruction, matches, swap_pos_re)) {
            scrambler.SwapPos(std::stoull(matches[1]), std::stoull(matches[2]));
        }
        else if (std::regex_match(instruction, matches, swap_ch_re)) {
            scrambler.SwapCh(matches[1].first[0], matches[2].first[0]);
        }
        else if (std::regex_match(instruction, matches, rotate_dir_re)) {
            auto dir =
                (matches[1] == "left") ? Scrambler::Direction::LEFT : Scrambler::Direction::RIGHT;
            scrambler.RotateDir(dir, std::stoull(matches[2]));
        }
        else if (std::regex_match(instruction, matches, rotate_pos_re)) {
            scrambler.RotateChPos(matches[1].first[0]);
        }
        else if (std::regex_match(instruction, matches, reverse_pos_re)) {
            scrambler.ReversePos(std::stoull(matches[1]), std::stoull(matches[2]));
        }
        else if (std::regex_match(instruction, matches, move_pos_re)) {
            scrambler.MovePos(std::stoull(matches[1]), std::stoull(matches[2]));
        }
    }

    return *scrambler;
}

template <>
std::string
solve<kDay21>(bool _part1, std::istream& _is, std::ostream& _os)
{
    auto instructions = get_instructions(_is);
    if (_part1) {
        std::string const str{"abcdefgh"};
        return scramble(instructions, str);
    }
    else {
        std::string const scrambled{"fbgdceah"};
        std::reverse(std::begin(instructions), std::end(instructions));
        return scramble(instructions, scrambled, true);
    }
}

}  // namespace aoc2016
