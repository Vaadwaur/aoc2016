#include <utils/md5.h>
#include <days.h>
#include <iomanip>
#include <regex>
#include <vector>

namespace aoc2016 {

static std::regex triplet{R"((.)\1\1)", std::regex_constants::optimize};
static std::regex quintet{R"((.)\1\1\1\1)", std::regex_constants::optimize};

namespace {
	static std::string salt;
}

struct tHashType
{
	uint64_t index;
	char match;
	std::string hash;
	bool used;
};

static auto
part1(std::istream& _is, std::ostream& _os)
{
	uint64_t num_confirmed_keys{};
	std::vector<std::pair<uint64_t, std::string>> confirmed_keys;
	constexpr uint64_t const kStorageSize{ 1001 };
	std::array<tHashType, kStorageSize> triplet_hashes{};
	std::array<tHashType, kStorageSize> quintet_hashes{};
	std::smatch matches;
	_os << salt << '\n';
	uint64_t index, stop_index = std::numeric_limits<uint64_t>::max();
	for (index = 0; num_confirmed_keys < 64 || index < stop_index; ++index) {
		auto const input = salt + std::to_string(index);
		auto const cur_hash = md5::MD5(input).HexDigest();
		if (std::regex_search(cur_hash, matches, triplet)) {
			size_t array_pos = index % kStorageSize;
			char match = matches[1].str()[0];
			triplet_hashes[array_pos] = tHashType{index, match, cur_hash, false};

			if (std::regex_search(cur_hash, matches, quintet)) {
				match = matches[1].str()[0];
				quintet_hashes[array_pos] = tHashType{index, match, cur_hash, false};

				for (int counter{1}; counter < kStorageSize; ++counter) {
					uint64_t i = (index + counter) % kStorageSize;
					if (triplet_hashes[i].used == false
						&& (triplet_hashes[i].index >= (index - 1000))
						&& triplet_hashes[i].match == match) {

						if (quintet_hashes[i].used == false
							&& quintet_hashes[i].index < triplet_hashes[i].index
							&& (quintet_hashes[i].index >= (index - 1000))
							&& quintet_hashes[i].match == match) {

							_os << std::setw(4) << num_confirmed_keys << ':' << std::setw(10) << index << " : " << std::setw(10) << index - quintet_hashes[i].index << " : " << cur_hash << " : " << std::setw(10) << quintet_hashes[i].index << " : " << quintet_hashes[i].hash << '\n';
							confirmed_keys.emplace_back(quintet_hashes[i].index, quintet_hashes[i].hash);
							++num_confirmed_keys;
							if (num_confirmed_keys == 64) {
								stop_index = index + 1000;
							}
							triplet_hashes[i].used = true;
							quintet_hashes[i].used = true;
							continue;
						}
						_os << std::setw(4) << num_confirmed_keys << ':' << std::setw(10) << index << " : " << std::setw(4) << index - triplet_hashes[i].index << " : " << cur_hash << " : " << std::setw(10) << triplet_hashes[i].index << " : " << triplet_hashes[i].hash << '\n';
						confirmed_keys.emplace_back(triplet_hashes[i].index, triplet_hashes[i].hash);
						++num_confirmed_keys;
						if (num_confirmed_keys == 64) {
							stop_index = index + 1000;
						}
						triplet_hashes[i].used = true;
						quintet_hashes[i].used = true;
					}
					else if (quintet_hashes[i].used == false
						&& (quintet_hashes[i].index >= (index - 1000))
						&& quintet_hashes[i].match == match) {

						_os << std::setw(4) << num_confirmed_keys << ':' << std::setw(10) << index << " : " << std::setw(4) << index - quintet_hashes[i].index << " : " << cur_hash << " : " << std::setw(10) << quintet_hashes[i].index << " : " << quintet_hashes[i].hash << '\n';
						confirmed_keys.emplace_back(quintet_hashes[i].index, quintet_hashes[i].hash);
						++num_confirmed_keys;
						if (num_confirmed_keys == 64) {
							stop_index = index + 1000;
						}
						triplet_hashes[i].used = true;
						quintet_hashes[i].used = true;
					}
				}
			}
		}
	}
	_os << '\n';
	std::sort(std::begin(confirmed_keys), std::end(confirmed_keys));
	int counter{};
	for (auto const& key : confirmed_keys) {
		_os << std::setw(2) << ++counter << ':' << std::setw(10) << key.first << ':' << key.second << '\n';
	}
	_os << '\n';

	return confirmed_keys[63].first;
}

static auto
part2(std::istream& _is, std::ostream& _os)
{
	uint64_t num_confirmed_keys{};
	std::vector<std::pair<uint64_t, std::string>> confirmed_keys;
	constexpr uint64_t const kStorageSize{ 1001 };
	std::array<tHashType, kStorageSize> triplet_hashes{};
	std::array<tHashType, kStorageSize> quintet_hashes{};
	std::smatch matches;
	_os << salt << '\n';
	uint64_t index, stop_index = std::numeric_limits<uint64_t>::max();
	for (index = 0; num_confirmed_keys < 64 || index < stop_index; ++index) {
		auto const input = salt + std::to_string(index);
		auto cur_hash = md5::MD5(input).HexDigest();
		for (int repeat{}; repeat < 2016; ++repeat) {
			cur_hash = md5::MD5(cur_hash).HexDigest();
		}
		if (std::regex_search(cur_hash, matches, triplet)) {
			size_t array_pos = index % kStorageSize;
			char match = matches[1].str()[0];
			triplet_hashes[array_pos] = tHashType{index, match, cur_hash, false};

			if (std::regex_search(cur_hash, matches, quintet)) {
				match = matches[1].str()[0];
				quintet_hashes[array_pos] = tHashType{index, match, cur_hash, false};

				for (int counter{1}; counter < kStorageSize; ++counter) {
					uint64_t i = (index + counter) % kStorageSize;
					if (triplet_hashes[i].used == false
						&& (triplet_hashes[i].index >= (index - 1000))
						&& triplet_hashes[i].match == match) {

						if (quintet_hashes[i].used == false
							&& quintet_hashes[i].index < triplet_hashes[i].index
							&& (quintet_hashes[i].index >= (index - 1000))
							&& quintet_hashes[i].match == match) {

							_os << std::setw(4) << num_confirmed_keys << ':' << std::setw(10) << index << " : " << std::setw(10) << index - quintet_hashes[i].index << " : " << cur_hash << " : " << std::setw(10) << quintet_hashes[i].index << " : " << quintet_hashes[i].hash << '\n';
							confirmed_keys.emplace_back(quintet_hashes[i].index, quintet_hashes[i].hash);
							++num_confirmed_keys;
							if (num_confirmed_keys == 64) {
								stop_index = index + 1000;
							}
							triplet_hashes[i].used = true;
							quintet_hashes[i].used = true;
							continue;
						}
						_os << std::setw(4) << num_confirmed_keys << ':' << std::setw(10) << index << " : " << std::setw(4) << index - triplet_hashes[i].index << " : " << cur_hash << " : " << std::setw(10) << triplet_hashes[i].index << " : " << triplet_hashes[i].hash << '\n';
						confirmed_keys.emplace_back(triplet_hashes[i].index, triplet_hashes[i].hash);
						++num_confirmed_keys;
						if (num_confirmed_keys == 64) {
							stop_index = index + 1000;
						}
						triplet_hashes[i].used = true;
						quintet_hashes[i].used = true;
					}
					else if (quintet_hashes[i].used == false
						&& (quintet_hashes[i].index >= (index - 1000))
						&& quintet_hashes[i].match == match) {

						_os << std::setw(4) << num_confirmed_keys << ':' << std::setw(10) << index << " : " << std::setw(4) << index - quintet_hashes[i].index << " : " << cur_hash << " : " << std::setw(10) << quintet_hashes[i].index << " : " << quintet_hashes[i].hash << '\n';
						confirmed_keys.emplace_back(quintet_hashes[i].index, quintet_hashes[i].hash);
						++num_confirmed_keys;
						if (num_confirmed_keys == 64) {
							stop_index = index + 1000;
						}
						triplet_hashes[i].used = true;
						quintet_hashes[i].used = true;
					}
				}
			}
		}
	}
	_os << '\n';
	std::sort(std::begin(confirmed_keys), std::end(confirmed_keys));
	int counter{};
	for (auto const& key : confirmed_keys) {
		_os << std::setw(2) << ++counter << ':' << std::setw(10) << key.first << ':' << key.second << '\n';
	}
	_os << '\n';

	return confirmed_keys[63].first;
}

template<> std::string
solve<kDay14>(bool _part1, std::istream& _is, std::ostream& _os)
{
	_is >> salt;

	return std::to_string(_part1 ? part1(_is, _os) : part2(_is, _os));
}

} // namespace aoc2016
