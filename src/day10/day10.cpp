#include <map>
#include <regex>
#include <days.h>

namespace aoc2017 {

using tOutputId = int;

enum TargetType { kBot, kOutput };

struct Target
{
	TargetType type;
	tOutputId id;
};

struct Instruction
{
	static TargetType GetType(std::string const& str) {
		return (str == "bot") ? kBot : kOutput;
	}
	std::array<Target, 2> targets;
};

using tMicrochip = int;
using tMicrochips = std::vector<tMicrochip>;

using tOutputs = std::map<tOutputId, tMicrochips>;
using tBotInstructions = std::map<tOutputId, Instruction>;
using tTask = std::pair<tOutputId, tMicrochips>;
using tTasks = std::vector<tTask>;

tOutputs::mapped_type goal{ 17,61 };

static auto
read_instructions(std::istream& _is)
{
	static const std::regex give_re{ R"(^bot (\d+) gives low to (bot|output) (\d+) and high to (output|bot) (\d+)$)" };
	static const std::regex receive_re{ R"(^value (\d+) goes to bot (\d+)$)" };

	tBotInstructions instr;
	std::smatch matches;
	tTasks tasks;
	tOutputs bots;
	for (std::string line; std::getline(_is, line); ) {
		if (std::regex_match(line, matches, give_re)) {
			// bot x gives low to bot y and high to bot z
			tOutputId bot_id = std::stoi(matches[1]);
			Instruction in{
				Instruction::GetType(matches[2]), std::stoi(matches[3]),
				Instruction::GetType(matches[4]), std::stoi(matches[5])
			};
			instr.emplace(bot_id, in);
		}
		else if (std::regex_match(line, matches, receive_re)) {
			int bot_id = std::stoi(matches[2]);
			auto &bot = bots[bot_id];
			bot.push_back(std::stoi(matches[1]));
			std::sort(std::begin(bot), std::end(bot));
			if (bot.size() == 2) {
				tasks.emplace_back(bot_id, bot);
			}
		}
	}

	return std::make_tuple(instr, bots, tasks);
}

static auto
GetOutput(Target& target, tOutputs& bots, tOutputs& outputs) {
	//tOutputs::value_type output;
	switch (target.type) {
	case TargetType::kBot:
		return bots[target.id];
		break;
	default:
		return outputs[target.id];
		break;
	}
}

static auto
part1(tBotInstructions const& instr, tOutputs& bots, tTasks& tasks)
{
	tOutputs outputs;
	while(!tasks.empty()) {
		auto task = tasks.back();
		tasks.pop_back();

		auto& task_chips = task.second;
		if (task_chips.size() != 2) {
			continue;
		}
		auto task_bot = task.first;
		if(task_chips == goal) {
			return task_bot;
		}

		auto instruction = instr.find(task_bot)->second; // get instruction for current tasks bot
		for (size_t i{}; i < instruction.targets.size(); ++i) {
			auto target = instruction.targets[i];
			auto output = GetOutput(target, bots, outputs);
			output.push_back(task_chips[i]);
			std::sort(std::begin(output), std::end(output));
			if (target.type == kBot && task_chips.size() == 2) {
				tasks.push_back({ instruction.targets[i].id, output });
			}
		}
	}

	return 0;
}

static auto
part2(tBotInstructions const& instr, tOutputs& bots, tTasks& tasks)
{
	tOutputs outputs;
	while(!tasks.empty()) {
		auto task = tasks.back();
		tasks.pop_back();

		auto& task_chips = task.second;
		if (task_chips.size() != 2) {
			continue;
		}

		auto task_bot = task.first;
		auto instruction = instr.find(task_bot)->second; // get instruction for current tasks bot
		for (size_t i{}; i < instruction.targets.size(); ++i) {
			auto target = instruction.targets[i];
			auto output = GetOutput(target, bots, outputs);
			output.push_back(task_chips[i]);
			std::sort(std::begin(output), std::end(output));
			if (target.type == kBot && task_chips.size() == 2) {
				tasks.push_back({ instruction.targets[i].id, output });
			}
		}
	}

	return outputs[0][0] * outputs[1][0] * outputs[2][0];
}

template<> std::string
solve<kDay10>(bool _part1, std::istream& _is, std::ostream& _os)
{
	tBotInstructions instr;
	tOutputs bots;
	tTasks tasks;
	std::tie(instr, bots, tasks) = read_instructions(_is);
	return std::to_string(_part1 ? part1(instr, bots, tasks) : part2(instr, bots, tasks));
}

} // namespace aoc2017
