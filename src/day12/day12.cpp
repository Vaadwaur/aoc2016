#include <cassert>
#include <cstdlib>
#include <vector>
#include <days.h>

namespace aoc2016 {


namespace {

	struct Instruction
	{
		enum Type {kCopyReg, kCopyVal, kJumpReg, kJumpVal, kInc, kDec};
		Type type;
		int op1;
		int op2;

	};

	using tInstructions = std::vector<Instruction>;

	struct CPU {
		std::array<int, 4> regs;
		int next;

		void Execute(tInstructions const& program) {
			Instruction const& in = program[next];
			switch (in.type) {
			case Instruction::kCopyReg:
				regs[in.op2] = regs[in.op1];
				break;
			case Instruction::kCopyVal:
				regs[in.op2] = in.op1;
				break;
			case Instruction::kJumpReg:
				if (regs[in.op1] != 0) {
					next += in.op2 - 1;
				}
				break;
			case Instruction::kJumpVal:
				if (in.op1 != 0) {
					next += in.op2 - 1;
				}
				break;
			case Instruction::kInc:
				++regs[in.op1];
				break;
			case Instruction::kDec:
				--regs[in.op1];
			}

			++next;
		}
	};

}


static auto
load_program(std::istream& _is)
{
	tInstructions instructions;

	for (std::string line; std::getline(_is, line);) {
		decltype(line)::value_type const* p = line.c_str();
		Instruction instr;
		auto ch = *p;
		char* end;
		p += 4;
		switch (ch) {
		case 'c':
			if (*p < 'a') {
				instr.type = Instruction::kCopyVal;
				instr.op1 = 0;
				while (*p != ' ') {
					instr.op1 = instr.op1 * 10 + (*p++ - '0');
				}
			}
			else {
				instr.type = Instruction::kCopyReg;
				instr.op1 = *p++ - 'a';
			}
			instr.op2 = *++p - 'a';
			break;
		case 'i':
			instr.type = Instruction::kInc;
			instr.op1 = *p - 'a';
			break;
		case 'd':
			instr.type = Instruction::kDec;
			instr.op1 = *p - 'a';
			break;
		case 'j':
			if (*p < 'a') {
				instr.type = Instruction::kJumpVal;
				instr.op1 = 0;
				while (*p != ' ') {
					instr.op1 = instr.op1 * 10 + (*p++ - '0');
				}
			}
			else {
				instr.type = Instruction::kJumpReg;
				instr.op1 = *p++ - 'a';
			}
			instr.op2 = 0;
			++p;
			instr.op2 = std::strtol(p, &end, 10);
			break;
		default:
			assert(false);
			break;
		}

		instructions.push_back(instr);
	}

	return instructions;
}

static auto
part1(tInstructions const& program)
{
	CPU cpu{};
	while (cpu.next < program.size()) {
		cpu.Execute(program);
	}

	return cpu.regs[0];
}

static auto
part2(tInstructions const& program)
{
	CPU cpu{};
	cpu.regs[2] = 1; // set register c
	while (cpu.next < program.size()) {
		cpu.Execute(program);
	}

	return cpu.regs[0];
}

template<> std::string
solve<kDay12>(bool _part1, std::istream& _is, std::ostream& _os)
{
	auto program = load_program(_is);
	return std::to_string(_part1 ? part1(program) : part2(program));
}

} // namespace aoc2016
