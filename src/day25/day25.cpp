#include <days.h>
#include <utils/assembunny.h>

#include <algorithm>
#include <type_traits>

namespace aoc2016 {

namespace asmb = assembunny;

static auto
part1(asmb::tInstructions& program)
{
    std::string output, expected_output;
    constexpr size_t const output_size = 10;
    output.reserve(output_size);
    expected_output.reserve(output_size);
    {
        // generate expected answer "01010101010101..."
        char out{'0'};
        for (size_t i{}; i < output_size; ++i) {
            out = (out == '0') ? '1' : '0';
            expected_output += out;
        }
    }
    std::string expected_output2 = expected_output;
    std::rotate(expected_output2.begin(), expected_output2.begin() + 1, expected_output2.end());

    asmb::CPU cpu{};
    int reg_a_test_value{};
    auto const size = std::make_signed_t<decltype(program.size())>(program.size());
    while (true) {
        cpu.regs = {};
        cpu.regs[0] = reg_a_test_value;
        cpu.next = 0;
        cpu.output_counter = 0;
        output.clear();

        uint64_t prev_output_counter = 0;
        while (cpu.next < size && cpu.output_counter < output_size) {
            cpu.Execute(program);
            if (cpu.output_counter > prev_output_counter) {
                prev_output_counter = cpu.output_counter;
                output += cpu.output;
            }
        }
        if (output == expected_output || output == expected_output2) {
            break;
        }
        ++reg_a_test_value;
    }

    return reg_a_test_value;
}

template <>
std::string
solve<kDay25>(bool _part1, std::istream& _is, [[maybe_unused]] std::ostream& _os)
{
    using namespace std::string_literals;

    auto program = asmb::load_program(_is);
    if (_part1) {
        return std::to_string(part1(program));
    }

    return "There is no part2 for day25."s;
}

}  // namespace aoc2016
