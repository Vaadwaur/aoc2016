#include <days.h>
#include <utils/md5.h>

#include <memory>
#include <regex>
#include <vector>

namespace aoc2016 {

namespace {

std::regex const triplet{R"((.)\1\1)", std::regex_constants::optimize};
std::regex const quintet{R"((.)\1\1\1\1)", std::regex_constants::optimize};
std::string salt;

}  // anonymous namespace

struct tHashType
{
    uint64_t index;
    char match;
    std::string hash;
    bool used;
};

static auto
pad_key_index(uint16_t const kNumStretches = 0)
{
    uint64_t num_confirmed_keys{};
    std::vector<std::pair<uint64_t, std::string>> confirmed_keys;
    constexpr uint64_t const kStorageSize{1000};
    auto triplet_hashes = std::make_unique<tHashType[]>(kStorageSize);
    auto quintet_hashes = std::make_unique<tHashType[]>(kStorageSize);
    std::smatch matches;
    std::string cur_hash;
    uint64_t index, stop_index = std::numeric_limits<uint64_t>::max();
    for (index = 0; num_confirmed_keys < 64 || index < stop_index; ++index) {
        cur_hash = salt + std::to_string(index);
        for (uint16_t repeat{}; repeat < kNumStretches + 1; ++repeat) {
            cur_hash = md5::MD5(cur_hash).HexDigest();
        }
        if (std::regex_search(cur_hash, matches, triplet)) {
            size_t array_pos = index % kStorageSize;
            char match = matches[1].first[0];

            if (std::regex_search(cur_hash, matches, quintet)) {
                match = matches[1].first[0];

                for (uint64_t counter{0}; counter < kStorageSize; ++counter) {
                    uint64_t i = (index + counter) % kStorageSize;
                    if (triplet_hashes[i].used == false &&
                        (triplet_hashes[i].index >= (index - 1000)) &&
                        triplet_hashes[i].match == match) {

                        if (quintet_hashes[i].used == false &&
                            quintet_hashes[i].index < triplet_hashes[i].index &&
                            (quintet_hashes[i].index >= (index - 1000)) &&
                            quintet_hashes[i].match == match) {

                            confirmed_keys.emplace_back(quintet_hashes[i].index,
                                                        quintet_hashes[i].hash);
                            ++num_confirmed_keys;
                            if (num_confirmed_keys == 64) {
                                stop_index = index + 1000;
                            }
                            triplet_hashes[i].used = true;
                            quintet_hashes[i].used = true;
                            continue;
                        }
                        confirmed_keys.emplace_back(triplet_hashes[i].index,
                                                    triplet_hashes[i].hash);
                        ++num_confirmed_keys;
                        if (num_confirmed_keys == 64) {
                            stop_index = index + 1000;
                        }
                        triplet_hashes[i].used = true;
                        quintet_hashes[i].used = true;
                    }
                    else if (quintet_hashes[i].used == false &&
                             (quintet_hashes[i].index >= (index - 1000)) &&
                             quintet_hashes[i].match == match) {

                        confirmed_keys.emplace_back(quintet_hashes[i].index,
                                                    quintet_hashes[i].hash);
                        ++num_confirmed_keys;
                        if (num_confirmed_keys == 64) {
                            stop_index = index + 1000;
                        }
                        triplet_hashes[i].used = true;
                        quintet_hashes[i].used = true;
                    }
                }
                quintet_hashes[array_pos] = tHashType{index, match, cur_hash, false};
            }
            triplet_hashes[array_pos] = tHashType{index, match, cur_hash, false};
        }
    }
    std::sort(std::begin(confirmed_keys), std::end(confirmed_keys));

    return confirmed_keys[63].first;
}

template <>
std::string
solve<kDay14>(bool _part1, std::istream& _is, [[maybe_unused]] std::ostream& _os)
{
    _is >> salt;

    return std::to_string(_part1 ? pad_key_index() : pad_key_index(2016));
}

}  // namespace aoc2016
