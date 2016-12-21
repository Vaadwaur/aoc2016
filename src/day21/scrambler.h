#include <string>

namespace aoc2016 {

class Scrambler final
{
	std::string str_;
	bool const reverse_;

public:
	enum Direction { LEFT, RIGHT };

	Scrambler() = delete;
	explicit Scrambler(std::string str, bool reverse = false) : str_{str}, reverse_{reverse} {}
	~Scrambler() = default;

	void MovePos(size_t pos1, size_t pos2);
	void ReversePos(size_t pos1, size_t pos2);
	void RotateDir(Direction dir, size_t steps) noexcept(true);
	void RotateChPos(char letter);
	void SwapPos(size_t pos1, size_t pos2);
	void SwapCh(char letter1, char letter2);

	std::string operator*() const;
};

} // namespace aoc2016
