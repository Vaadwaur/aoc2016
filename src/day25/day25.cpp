#include <cassert>
#include <vector>
#include <days.h>

namespace aoc2016 {

namespace {

struct Instruction
{
	enum Type {kCopyReg, kCopyVal, kJumpReg, kJumpVal, kJumpValReg, kInc, kDec, kToggle, kInvalid, kOutReg, kOutVal};
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

	void Execute(tInstructions& program) {
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
		case Instruction::kJumpValReg:
			if (in.op1 != 0) {
				next += regs[in.op2] - 1;
			}
			break;
		case Instruction::kInc:
			++regs[in.op1];
			break;
		case Instruction::kDec:
			--regs[in.op1];
			break;
		case Instruction::kToggle:
		{
			auto target = next + regs[in.op1];
			if (target >= program.size()) {
				break;
			}
			auto &target_in = program[target];
			switch (target_in.type) {
			case Instruction::kJumpReg:
				target_in.type = Instruction::kCopyReg;
				break;
			case Instruction::kJumpVal:
				// "cpy val -> val" is not valid
				target_in.type = Instruction::kInvalid;
				break;
			case Instruction::kJumpValReg:
				target_in.type = Instruction::kCopyVal;
				break;
			case Instruction::kCopyReg:
				target_in.type = Instruction::kJumpReg;
				break;
			case Instruction::kCopyVal:
				target_in.type = Instruction::kJumpVal;
				break;
			case Instruction::kInc:
				target_in.type = Instruction::kDec;
				break;
			default:
				target_in.type = Instruction::kInc;
				break;
			}
			break;
		}
		case Instruction::kOutReg:
			output = regs[in.op1] + 0x30;
			++output_counter;
			break;
		case Instruction::kOutVal:
			output = in.op1 + 0x30;
			++output_counter;
			break;
		default:
			break;
		}

		++next;
	}
};

} // anonymous internal namespace


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
				instr.op1 = std::strtol(p, &end, 10);
				p = end;
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
				instr.op1 = std::strtol(p, &end, 10);
				p = end;
			}
			else {
				instr.type = Instruction::kJumpReg;
				instr.op1 = *p++ - 'a';
			}
			++p;
			instr.op2 = std::strtol(p, &end, 10);
			if (p == end) {
				instr.type = Instruction::kJumpValReg;
				instr.op2 = *p - 'a';
			}
			break;
		case 'o':
			if (*p < 'a') {
				instr.type = Instruction::kOutVal;
				instr.op1 = std::strtol(p, &end, 10);
			}
			else {
				instr.type = Instruction::kOutReg;
				instr.op1 = *p - 'a';
			}
			break;
		case 't':
			instr.type = Instruction::kToggle;
			instr.op1 = *p - 'a';
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
part1(tInstructions& program)
{
	std::string output, expected_output;
	constexpr size_t const output_size = 10;
	output.reserve(output_size);
	expected_output.reserve(output_size);
	{
		// generate expected answer "01010101010101..."
		char out{'0'};
		for(int i{}; i < output_size; ++i) {
			out = (out == '0') ? '1' : '0';
			expected_output += out;
		}
	}
	auto expected_output2 = expected_output;
	std::rotate(expected_output2.begin(), expected_output2.begin() + 1, expected_output2.end());

	CPU cpu{};
	int reg_a_test_value{};
	size_t const size = program.size();
	while(true) {
		cpu.regs = {};
		cpu.regs[0] = reg_a_test_value;
		cpu.next = 0;
		cpu.output_counter = 0;
		output.clear();

		uint64_t prev_output_counter = 0;
		while (cpu.next < size && cpu.output_counter < output_size) {
			cpu.Execute(program);
			if(cpu.output_counter > prev_output_counter) {
				prev_output_counter = cpu.output_counter;
				output += cpu.output;
			}
		}
		if(output == expected_output || output == expected_output2) {
			break;
		}
		++reg_a_test_value;
	}

	return reg_a_test_value;
}

template<> std::string
solve<kDay25>(bool _part1, std::istream& _is, std::ostream& _os)
{
	using namespace std::string_literals;

	auto program = load_program(_is);
	if(_part1) {
		return std::to_string(part1(program));
	}

	return "There is not part2 for day25."s;
}

} // namespace aoc2016
