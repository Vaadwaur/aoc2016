#include <days.h>

namespace aoc2016 {

static std::string
checksum(std::string const& input)
{
    std::string chksum;
    if (input.empty()) {
        return chksum;
    }
    size_t const len = input.length() - 1;
    chksum.reserve(len / 2 + 3);
    for (size_t i{}; i < len; i += 2) {
        chksum += (input[i] == input[i + 1]) ? '1' : '0';
    }

    return chksum;
}

static std::string
get_data(std::string storage, size_t const storage_size)
{
    storage.reserve((storage_size << 1) + 1);
    while (storage.length() < storage_size) {
        storage += '0';
        for (auto it = storage.rbegin() + 1; it != storage.rend(); ++it) {
            storage += ((*it) == '0') ? '1' : '0';
        }
    }

    // trim to requested storage size
    storage.resize(storage_size);
    // calculate checksum
    do {
        storage = checksum(storage);
        // continue as long as checksum is of even length
    } while ((storage.length() & 0x1) == 0);

    return storage;
}

template <>
std::string
solve<kDay16>(bool _part1, std::istream& _is, std::ostream& _os)
{
    std::string storage;
    _is >> storage;
    return _part1 ? get_data(storage, 272) : get_data(storage, 35651584);
}

}  // namespace aoc2016
