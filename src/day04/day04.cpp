#include <fstream>
#include <functional>
#include <map>
#include <regex>
#include <string>
#include <string_view>
#include <vector>
#include <days.h>

namespace aoc2017 {

using tSectorId = uint64_t;

static auto
explode_room(std::string const& room)
{
	std::regex delimeters{R"([-\[\]])"};
	std::vector<std::string> tokens(
		std::sregex_token_iterator(room.begin(), room.end(), delimeters, -1),
		std::sregex_token_iterator());
	auto checksum = tokens.back();
	tokens.pop_back();
	auto sector_id = tokens.back();
	tokens.pop_back();
	std::string room_code;
	for (auto& token : tokens) {
		room_code.append(token);
	}
	return std::make_tuple(room_code, std::stoull(sector_id), checksum);
}

static std::string
calculate_room_checksum(std::string const& room_code)
{
	std::map<char, size_t> char_count;
	for (auto ch : room_code) {
		// insert or update
		auto lb = char_count.lower_bound(ch);
		if (lb == std::cend(char_count) || lb->first != ch) {
			char_count.emplace_hint(lb, ch, 0);
		}
		else {
			++lb->second;
		}
	}

	// sort by how common each character is
	std::vector<std::pair<size_t, char>> vec;
	vec.reserve(char_count.size());
	for (auto const& value : char_count) {
		vec.emplace_back(value.second, value.first);
	}
	std::stable_sort(std::begin(vec), std::end(vec), [](auto const& lhs, auto const& rhs) {
		if (lhs.first == rhs.first) {
			return lhs.second < rhs.second;
		}
		return lhs.first > rhs.first;
	});
	// calculate checksum based on room code
	std::string calculated_chksum;
	auto it = std::cbegin(vec);
	for (size_t i{}; i < 5; ++i) {
		calculated_chksum.append(1, it->second);
		++it;
	}

	return calculated_chksum;
}


static bool
is_room_valid(std::string const& room_code, std::string const& checksum)
{
	return checksum == calculate_room_checksum(room_code);
}

static tSectorId
part1(std::istream& _is)
{
	tSectorId sum{}, sector_id;
	std::string line, room_code, checksum;
	while (std::getline(_is, line)) {
		std::tie(room_code, sector_id, checksum) = explode_room(line);
		if (is_room_valid(room_code, checksum)) {
			sum += sector_id;
		}
	}

	return sum;
}

static std::string
decrypt_name(std::string room_code, tSectorId sector_id)
{
	char const rotate_count = sector_id % 26;
	char const reverse = 26 - rotate_count;
	for (auto& ch : room_code) {
		if (ch > ('z' - rotate_count)) {
			ch -= reverse;
		}
		else {
			ch += rotate_count;
		}
	}

	return room_code; // decrypted room name
}

static tSectorId
part2(std::istream& _is)
{
	tSectorId sector_id;
	std::string line, room_code, checksum;
	while (std::getline(_is, line)) {
		std::tie(room_code, sector_id, checksum) = explode_room(line);
		if (!is_room_valid(room_code, checksum)) {
			continue;
		}

		auto room_name = decrypt_name(room_code, sector_id);
		if (room_name == "northpoleobjectstorage") {
			return sector_id;
		}
	}

	return std::numeric_limits<tSectorId>::max();
}

template<> std::string
solve<kDay04>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1(_is) : part2(_is));
}

} // namespace aoc2017
