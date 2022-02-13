#include <days.h>
#include <utils/assembunny.h>

namespace aoc2016 {

namespace asmb = assembunny;

static auto
part1(asmb::tInstructions const& program)
{
    asmb::CPU cpu{};
    while (cpu.next < program.size()) {
        cpu.Execute(program);
    }

    return cpu.regs[0];
}

static auto
part2(asmb::tInstructions const& program)
{
    asmb::CPU cpu{};
    cpu.regs[2] = 1;  // set register c
    while (cpu.next < program.size()) {
        cpu.Execute(program);
    }

    return cpu.regs[0];
}

template <>
std::string
solve<kDay12>(bool _part1, std::istream& _is, [[maybe_unused]] std::ostream& _os)
{
    auto program = asmb::load_program(_is);
    return std::to_string(_part1 ? part1(program) : part2(program));
}

}  // namespace aoc2016
