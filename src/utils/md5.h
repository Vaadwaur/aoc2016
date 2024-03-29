#include <array>
#include <iostream>
#include <fstream>

namespace aoc2016::md5 {

// usage: 1) feed it blocks of uchars with update()
//      2) finalize()
//      3) get hexdigest() string
//      or
//      MD5(std::string).hexdigest()
//
// assumes that char is 8 bit and int is 32 bit
class MD5
{
public:
	enum { kBlockSize = 64 }; // VC6 won't eat a const static int here
	using size_type = uint32_t;

	MD5() = default;
	MD5(std::string const& text);
	void Update(uint8_t const* input, size_type length);
	void Update(int8_t const* input, size_type length);
	MD5& Finalize();
	std::string HexDigest() const;
	friend std::ostream& operator<<(std::ostream&, MD5 md5);

private:
	void Transform(uint8_t const* block);
	static void Decode(uint32_t *output, uint8_t const* input);
	static void Encode(uint8_t *output, uint32_t const* input, size_type len);

	bool finalized_{};
	std::array<uint8_t, kBlockSize> buffer_; // bytes that didn't fit in last 64 byte chunk
	uint32_t count_[2]{};   // 64bit counter for number of bits (lo, hi)
	uint32_t state_[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };   // digest so far
	uint8_t digest_[16]; // 128-bit result
};

std::string md5(std::string const& str);

} // aoc2016::md5
