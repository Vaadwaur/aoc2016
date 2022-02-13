#include <days.h>
#include <queue>
#include <utils/md5.h>

namespace aoc2016 {

using namespace std::string_literals;

namespace {

constexpr unsigned char const X_SIZE = 4;
constexpr unsigned char const Y_SIZE = 4;
std::string input;
constexpr std::array<char, 4> const PATH_LOOKUP{'U', 'D', 'L', 'R'};

}  // anonymous namespace

using tDoorState = char;

static tDoorState
door_state(std::string const& path)
{
    md5::MD5 md5;
    md5.Update(reinterpret_cast<int8_t const*>(input.data()),
               static_cast<uint32_t>(input.length()));
    md5.Update(reinterpret_cast<int8_t const*>(path.data()), static_cast<uint32_t>(path.length()));
    md5.Finalize();
    auto hash = md5.HexDigest();

    tDoorState state;
    state = hash[0] > 'a';
    state = state | (hash[1] > 'a') << 1;
    state = state | (hash[2] > 'a') << 2;
    state = state | (hash[3] > 'a') << 3;

    return state;
}

struct Pos
{
    char x;
    char y;

    constexpr bool
    operator==(Pos const rhs) const noexcept
    {
        return x == rhs.x && y == rhs.y;
    }
};

struct Trail
{
    Pos start;
    std::string path;
};

auto lookup_up = [](Pos pos) -> Pos { return {pos.x, static_cast<char>(pos.y - 1)}; };
auto lookup_down = [](Pos pos) -> Pos { return {pos.x, static_cast<char>(pos.y + 1)}; };
auto lookup_left = [](Pos pos) -> Pos { return {static_cast<char>(pos.x - 1), pos.y}; };
auto lookup_right = [](Pos pos) -> Pos { return {static_cast<char>(pos.x + 1), pos.y}; };
std::array<Pos (*)(Pos), 4> next_pos_lookup{lookup_up, lookup_down, lookup_left, lookup_right};

template <unsigned char X_SIZE, unsigned char Y_SIZE>
bool
is_pos_valid(Pos pos)
{
    if (0 <= pos.x && pos.x < X_SIZE) {
        if (0 <= pos.y && pos.y < Y_SIZE) {
            return true;
        }
    }

    return false;
}

static auto
part1()
{
    constexpr Pos const end_pos{X_SIZE - 1, Y_SIZE - 1};
    Pos next_pos;
    Trail trail;
    tDoorState state;

    std::queue<Trail> queue;
    queue.push({});
    while (!queue.empty()) {
        trail = std::move(queue.front());
        queue.pop();
        state = door_state(trail.path);
        for (int i{1}, c{}; i < 0x10; i <<= 1, ++c) {
            if (state & i) {
                next_pos = next_pos_lookup[c](trail.start);
                if (!is_pos_valid<X_SIZE, Y_SIZE>(next_pos)) {
                    continue;
                }
                if (next_pos == end_pos) {
                    return trail.path + PATH_LOOKUP[c];
                }
                queue.push({next_pos, trail.path + PATH_LOOKUP[c]});
            }
        }
    }

    return "no solution found"s;
}

static auto
part2()
{
    constexpr Pos const end_pos{X_SIZE - 1, Y_SIZE - 1};
    Pos next_pos;
    Trail trail;
    tDoorState state;
    uint64_t longest_path{};

    std::queue<Trail> queue;
    queue.push({});
    while (!queue.empty()) {
        trail = std::move(queue.front());
        queue.pop();
        state = door_state(trail.path);
        for (int i{1}, c{}; i < 0x10; i <<= 1, ++c) {
            if (state & i) {
                next_pos = next_pos_lookup[c](trail.start);
                if (!is_pos_valid<X_SIZE, Y_SIZE>(next_pos)) {
                    continue;
                }
                if (next_pos == end_pos) {
                    longest_path = trail.path.length() + 1;
                    continue;
                }
                queue.push({next_pos, trail.path + PATH_LOOKUP[c]});
            }
        }
    }

    return longest_path;
}

template <>
std::string
solve<kDay17>(bool _part1, std::istream& _is, [[maybe_unused]] std::ostream& _os)
{
    _is >> input;
    return _part1 ? part1() : std::to_string(part2());
}

}  // namespace aoc2016
