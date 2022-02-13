#include "scrambler.h"

#include <algorithm>

namespace aoc2016 {

void
Scrambler::MovePos(size_t pos1, size_t pos2)
{
    if (reverse_) {
        char ch = str_[pos2];
        str_.erase(str_.begin() + pos2);
        str_.insert(str_.begin() + pos1, ch);
    }
    else {
        char ch = str_[pos1];
        str_.erase(str_.begin() + pos1);
        str_.insert(str_.begin() + pos2, ch);
    }
}

void
Scrambler::ReversePos(size_t pos1, size_t pos2)
{
    auto beg = str_.begin();
    std::reverse(beg + pos1, beg + pos2 + 1);
}

void
Scrambler::RotateDir(Direction dir, size_t steps) noexcept(true)
{
    if (reverse_) {
        dir = (dir == Direction::LEFT) ? Direction::RIGHT : Direction::LEFT;
    }
    steps %= str_.length();
    if (dir == Direction::LEFT) {
        std::rotate(str_.begin(), str_.begin() + steps, str_.end());
    }
    else {
        std::rotate(str_.rbegin(), str_.rbegin() + steps, str_.rend());
    }
}

void
Scrambler::RotateChPos(char letter)
{
    size_t steps = str_.find(letter);

    if (reverse_) {
        // rotate left
        // pos      rev
        //	0->1     1->0
        //	1->3     3->1
        //	2->5     5->2
        //	3->7     7->3
        //	4->10->2 2->4
        //	5->12->4 4->5
        //	6->14->6 6->6
        //	7->16->0 0->7

        //	0->7 = -1
        //	1->0 = -1
        //	2->4 = +2
        //	3->1 = -2
        //	4->5 = +1
        //	5->2 = -3
        //	6->6 = 0
        //	7->3 = -4
        steps = steps / 2 + (((steps % 2 == 1) || steps == 0) ? 1 : 5);
        steps %= str_.length();
        std::rotate(str_.begin(), str_.begin() + steps, str_.end());
    }
    else {
        // rotate right
        if (++steps > 4) {
            ++steps;
        }
        steps %= str_.length();
        std::rotate(str_.rbegin(), str_.rbegin() + steps, str_.rend());
    }
}

void
Scrambler::SwapPos(size_t pos1, size_t pos2)
{
    std::swap(str_[pos1], str_[pos2]);
}

void
Scrambler::SwapCh(char letter1, char letter2)
{
    size_t pos1 = str_.find(letter1);
    size_t pos2 = str_.find(letter2);
    std::swap(str_[pos1], str_[pos2]);
}

std::string Scrambler::operator*() const { return str_; }
}
