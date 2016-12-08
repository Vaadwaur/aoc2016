#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <days.h>

namespace aoc2017 {

constexpr bool check_triangle(unsigned side1, unsigned side2, unsigned side3)
{
	return (side1 + side2) > side3;
}

auto
part1(std::istream& _is)
{
	unsigned nValid{};
	std::string line;
	std::array<unsigned, 3> sides;
	while (std::getline(_is, line)) {
		std::stringstream ss{ line };
		ss >> sides[0];
		ss >> sides[1];
		ss >> sides[2];
		std::sort(sides.data(), sides.data() + 3);
		bool isPossible{ true };
		do {
			if(!check_triangle(sides[0], sides[1], sides[2])) {
				isPossible = false;
				break;
			}
		} while (std::next_permutation(sides.data(), sides.data() + 3));
		if (isPossible) {
			++nValid;
		}
	}

	return nValid;
}

auto
part2(std::istream& _is)
{
	std::string line;
	std::array<unsigned, 3> tri;
	std::vector<std::array<unsigned, 3>> horiz_triangles;
	while (std::getline(_is, line)) {
		std::stringstream ss{ line };
		ss >> tri[0];
		ss >> tri[1];
		ss >> tri[2];

		horiz_triangles.push_back(tri);
	}
	// transpose to vertical alignment
	size_t nTriangles = horiz_triangles.size();
	std::vector<std::array<unsigned, 3>> triangles(nTriangles);
	if (horiz_triangles.size() % 3) {
		std::cerr << "num rows is not modulus 3";
	}
	for (unsigned row{}; row < 3; ++row) {
		for (unsigned i{}; i < nTriangles; i += 3) {
			tri = { horiz_triangles[i][row], horiz_triangles[i + 1][row], horiz_triangles[i + 2][row] };
			triangles.push_back(tri);
		}
	}

	unsigned nValid{};
	for (auto triangle : triangles) {
		std::sort(triangle.data(), triangle.data() + triangle.size());
		bool isPossible{ true };
		do {
			if(!check_triangle(triangle[0], triangle[1], triangle[2])) {
				isPossible = false;
				break;
			}
		} while (std::next_permutation(triangle.data(), triangle.data() + triangle.size()));
		if (isPossible) {
			++nValid;
		}
	}

	return nValid;
}

template<> std::string
solve<kDay03>(bool _part1, std::istream& _is, std::ostream& _os)
{
	return std::to_string(_part1 ? part1(_is) : part1(_is));
}

} // namespace aoc2017
