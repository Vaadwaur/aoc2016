#include <fstream>
#include <string_view>
#include <days.h>
#include "md5.h"

namespace aoc2017 {

static std::string
part1(std::istream& _is, std::ostream& _os)
{
	std::string input;
	std::getline(_is, input);
	size_t counter{};
	std::string code, digest;
	for (int i{}; i < 8; ++i) {
		do {
			std::string hash_input = input + std::to_string(counter++);
			digest = md5::MD5(hash_input).HexDigest();
		} while (std::string_view(digest.data(), 5) != "00000");
		code += digest[5];
		_os << digest[5] << std::flush;
	}
	
	return code;
}

static std::string
part2(std::istream& _is, std::ostream& _os)
{
	std::string input, digest, hash_input;
	std::string code(8, '_');
	std::getline(_is, input);
	size_t counter{};
	for (uint8_t found{}; found != 0xff;) {
		hash_input = input + std::to_string(counter++);
		digest = md5::MD5(hash_input).HexDigest();
		if (std::string_view(digest.data(), 5) != "00000") {
			continue;
		}
		uint8_t pos = digest[5] - 0x30;
		if (pos >= 8) {
			continue;
		}
		if (((0x1 << pos) & found) == 0x00) {
			// password position not yet filled
			found |= 0x1 << pos;
			code[pos] = digest[6];
			_os << code << "\b\b\b\b\b\b\b\b" << std::flush;
		}
	}

	return code;
}

template<> std::string
solve<kDay05>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return _part1 ? part1(_is, _os) : part2(_is, _os);
}

} // namespace aoc2017
