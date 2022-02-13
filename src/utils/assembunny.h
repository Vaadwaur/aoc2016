#include <array>
#include <iosfwd>
#include <vector>

namespace aoc2016::assembunny {

struct Instruction
{
	enum Type { kCopyReg, kCopyVal, kJumpReg, kJumpVal, kJumpValReg, kInc, kDec, kToggle, kInvalid, kOutReg, kOutVal };
	Type type;
	int op1;
	int op2;
};

using tInstructions = std::vector<Instruction>;

struct CPU {
	std::array<int, 4> regs;
	int next;
	int output;
	uint64_t output_counter;

	void Execute(tInstructions& program);
	void Execute(tInstructions const& program);
};

tInstructions load_program(std::istream& _is);

} // namespace aoc2016::assembunny
