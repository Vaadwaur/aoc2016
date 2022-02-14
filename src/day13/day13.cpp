#include <days.h>

#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcount __popcnt
#else
#include <x86intrin.h>
#endif

#include <array>

namespace aoc2016 {

namespace {

enum eRoomType { UNCHECKED = 0xfe, WALL = 0xff };
constexpr uint8_t const ROOMS_X = 52;
constexpr uint8_t const ROOMS_Y = 52;
uint32_t puzzle_input;

}  // anonymous namespace

template <typename T>
static constexpr T
square(T const value) noexcept
{
    return value * value;
}

static bool
is_open_space(uint32_t const pos_x, uint32_t const pos_y) noexcept
{
    uint32_t result = square(pos_x) + 3 * pos_x + 2 * pos_x * pos_y + pos_y + square(pos_y);
    result += puzzle_input;
    uint32_t num_bits_set = __builtin_popcount(result);

    // odd number == wall, even number == open space
    return (num_bits_set & 1) == 0;
}

template <uint8_t X, uint8_t Y>
static constexpr uint32_t
shortest_path_neighbour(std::array<std::array<uint8_t, X>, Y> const& dungeon, int const pos_x,
                        int const pos_y) noexcept
{
    static_assert(X < 254, "X size must be less than 254");
    static_assert(Y < 254, "Y size must be less than 254");

    uint8_t min = WALL;
    if (pos_y > 0) {
        // check row above
        auto test = std::min(dungeon[pos_y - 1][pos_x], min);
        min = std::min(test, min);
    }
    if (pos_x > 0) {
        // check room to the left
        auto test = std::min(dungeon[pos_y][pos_x - 1], min);
        min = std::min(test, min);
    }
    if (pos_x < X - 1) {
        // check room to the right
        auto test = std::min(dungeon[pos_y][pos_x + 1], min);
        min = std::min(test, min);
    }
    if (pos_y < Y - 1) {
        // check room to the below
        auto test = std::min(dungeon[pos_y + 1][pos_x], min);
        min = std::min(test, min);
    }

    return min;
}

template <uint8_t X, uint8_t Y>
static constexpr std::array<std::array<uint8_t, X>, Y>
get_dungeon(uint32_t const start_pos_x, uint32_t const start_pos_y)
{
    static_assert(X < 254, "X size must be less than 254");
    static_assert(Y < 254, "Y size must be less than 254");

    // set layout of dungeon
    std::array<std::array<uint8_t, X>, Y> dungeon{};
    for (uint8_t y{}; y < ROOMS_Y; ++y) {
        for (uint8_t x{}; x < ROOMS_X; ++x) {
            dungeon[y][x] = is_open_space(x, y) ? UNCHECKED : WALL;
        }
    }

    // for each room...
    // calculate least number of steps required from starting position
    uint32_t counter{1};
    dungeon[start_pos_y][start_pos_x] = 0;
    while (counter > 0) {
        counter = 0;
        for (uint8_t y{}; y < ROOMS_Y; ++y) {
            for (uint8_t x{}; x < ROOMS_X; ++x) {
                auto room_value = dungeon[y][x];
                if (room_value < 0xff) {
                    auto new_value = shortest_path_neighbour<X, Y>(dungeon, x, y) + 1;
                    if (new_value < room_value) {
                        // count number of rooms with improved score since last run
                        ++counter;
                        dungeon[y][x] = new_value;
                    }
                }
            }
        }
    }

    return dungeon;
}

static uint8_t
part1([[maybe_unused]] std::ostream& _os)
{
    auto dungeon = get_dungeon<ROOMS_X, ROOMS_Y>(1, 1);
    uint8_t const shortest_path = dungeon[39][31];

#ifdef DAY13_SHOW_DUNGEON
    for (uint8_t y{}; y < ROOMS_Y; ++y) {
        for (uint8_t x{}; x < ROOMS_X; ++x) {
            auto walkable = is_open_space(x, y);
            dungeon[y][x] = walkable ? '.' : '#';
        }
    }

    dungeon[1][1] = '@';    // start position
    dungeon[39][31] = 'X';  // end position
    _os << '\n';
    for (uint8_t y{}; y < ROOMS_Y; ++y) {
        for (uint8_t x{}; x < ROOMS_X; ++x) {
            _os << dungeon[y][x];
        }
        _os << '\n';
    }
#endif

    return shortest_path;
}

static auto
part2()
{
    auto dungeon = get_dungeon<ROOMS_X, ROOMS_Y>(1, 1);
    uint16_t counter{};
    for (uint8_t y{}; y < ROOMS_Y; ++y) {
        for (uint8_t x{}; x < ROOMS_X; ++x) {
            if (dungeon[y][x] <= 50) {
                ++counter;
            }
        }
    }

    return counter;
}

template <>
std::string
solve<kDay13>(bool _part1, std::istream& _is, std::ostream& _os)
{
    _is >> puzzle_input;

    return std::to_string(_part1 ? part1(_os) : part2());
}

}  // namespace aoc2016
