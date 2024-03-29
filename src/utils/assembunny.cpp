#include "assembunny.h"
#include <cassert>
#include <fstream>
#include <string>
#include <type_traits>

namespace aoc2016::assembunny {

void
CPU::Execute(tInstructions& program)
{
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
        case Instruction::kToggle: {
            auto target = next + regs[in.op1];
            if (target >= std::make_signed_t<decltype(program.size())>(program.size())) {
                break;
            }
            auto& target_in = program[target];
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

void
CPU::Execute(tInstructions const& program)
{
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

tInstructions
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

}  // namespace aoc2016::assembunny
