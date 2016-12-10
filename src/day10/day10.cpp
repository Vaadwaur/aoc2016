#include <cassert>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <days.h>

namespace aoc2017 {

using tBotValue = int;
using tBotValues = std::vector<tBotValue>;
using tOutput = int;
using tOutputs = std::map<tOutput,tBotValues>;

static const std::regex give_re{R"(^bot (\d+) gives low to (bot|output) (\d+) and high to (output|bot) (\d+)$)"};
static const std::regex receive_re{R"(^value (\d+) goes to bot (\d+)$)"};

tOutputs::mapped_type goal{ 17,61 };

static auto
part1(std::istream& _is)
{
	tOutputs bots;
	tOutputs outputs;
	std::vector<std::string> instructions;

	std::string line;
	std::smatch matches;
	while (std::getline(_is, line)) {
		instructions.push_back(line);
	}
	std::set<size_t> is_done;
	while(is_done.size() < instructions.size()) {
		size_t instr_nr{};
		for (auto& instruction : instructions) {
			++instr_nr;
			if (std::cend(is_done) != is_done.find(instr_nr)) {
				continue;
			}

			if (std::regex_match(instruction, matches, give_re)) {
				// bot x gives low to bot y and high to bot z
				auto bot = std::stoi(matches[1]);
				auto giver = bots.find(bot);
				// bot doesn't yet have two values and hence cannot execute his instruction
				if (giver == std::cend(bots) || giver->second.size() != 2) {
					continue;
				}

				// give away low value
				auto value = giver->second[0];
				auto target = std::stoi(matches[3]);
				if (matches[2] == "output") {
					auto target_output = outputs.insert({ target, {} }).first;
					target_output->second.push_back(value);
				}
				else {
					auto target_bot = bots.insert({ target, {} }).first;
					target_bot->second.push_back(value);
					std::sort(target_bot->second.begin(), target_bot->second.end());
					if (target_bot->second == goal) {
						return target;
					}
				}

				// give away high value
				value = giver->second[1];
				target = std::stoi(matches[5]);
				if (matches[4] == "output") {
					auto target_output = outputs.insert({ target, {} }).first;
					target_output->second.push_back(value);
				}
				else {
					auto target_bot = bots.insert({ target, {} }).first;
					target_bot->second.push_back(value);
					std::sort(target_bot->second.begin(), target_bot->second.end());
					if (target_bot->second == goal) {
						return target;
					}
				}
				is_done.insert(instr_nr);
			}
			else if (std::regex_match(instruction, matches, receive_re)) {
				// value x goes to bot y
				auto inserted = is_done.insert(instr_nr);
				assert(inserted.second == true);
				auto value = std::stoi(matches[1]);
				auto bot = std::stoi(matches[2]);
				auto target = bots.insert({ bot, {} }).first;
				target->second.push_back(value);
				std::sort(target->second.begin(), target->second.end());
				if (target->second == goal) {
					return bot;
				}
			}
		}
	}

	return 0;
}

static auto
part2(std::istream& _is)
{
	tOutputs bots;
	tOutputs outputs;
	std::vector<std::string> instructions;

	std::string line;
	std::smatch matches;
	while (std::getline(_is, line)) {
		instructions.push_back(line);
	}
	std::set<size_t> is_done;
	while(is_done.size() < instructions.size()) {
		size_t instr_nr{};
		for (auto& instruction : instructions) {
			++instr_nr;
			if (std::cend(is_done) != is_done.find(instr_nr)) {
				continue;
			}

			if (std::regex_match(instruction, matches, give_re)) {
				// bot x gives low to bot y and high to bot z
				auto bot = std::stoi(matches[1]);
				auto giver = bots.find(bot);
				// bot doesn't yet have two values and hence cannot execute his instruction
				if (giver == std::cend(bots) || giver->second.size() != 2) {
					continue;
				}

				// give away low value
				auto value = giver->second[0];
				auto target = std::stoi(matches[3]);
				if (matches[2] == "output") {
					auto target_output = outputs.insert({ target, {} }).first;
					target_output->second.push_back(value);
				}
				else {
					auto target_bot = bots.insert({ target, {} }).first;
					target_bot->second.push_back(value);
					std::sort(target_bot->second.begin(), target_bot->second.end());
				}

				// give away high value
				value = giver->second[1];
				target = std::stoi(matches[5]);
				if (matches[4] == "output") {
					auto target_output = outputs.insert({ target, {} }).first;
					target_output->second.push_back(value);
				}
				else {
					auto target_bot = bots.insert({ target, {} }).first;
					target_bot->second.push_back(value);
					std::sort(target_bot->second.begin(), target_bot->second.end());
				}

				is_done.insert(instr_nr);
			}
			else if (std::regex_match(instruction, matches, receive_re)) {
				// value x goes to bot y
				is_done.insert(instr_nr);
				auto value = std::stoi(matches[1]);
				auto bot = std::stoi(matches[2]);
				auto target = bots.insert({ bot, {} }).first;
				target->second.push_back(value);
				std::sort(target->second.begin(), target->second.end());
				if (target->second == goal) {
					return bot;
				}
			}
		}
	}

	auto out0 = outputs[0][0];
	auto out1 = outputs[1][0];
	auto out2 = outputs[2][0];
	return out0 * out1 * out2;
}

template<> std::string
solve<kDay10>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1(_is) : part2(_is));
}

} // namespace aoc2017
