#include "md5.h"
#include <cstdint>
#include <cstring>
#include <string>

// reference implemantion of RFC 1321

namespace aoc2016::md5 {

// Constants for MD5Transform routine.
static constexpr int const S11 = 7;
static constexpr int const S12 = 12;
static constexpr int const S13 = 17;
static constexpr int const S14 = 22;
static constexpr int const S21 = 5;
static constexpr int const S22 = 9;
static constexpr int const S23 = 14;
static constexpr int const S24 = 20;
static constexpr int const S31 = 4;
static constexpr int const S32 = 11;
static constexpr int const S33 = 16;
static constexpr int const S34 = 23;
static constexpr int const S41 = 6;
static constexpr int const S42 = 10;
static constexpr int const S43 = 15;
static constexpr int const S44 = 21;

// F, G, H and I are basic MD5 functions.
__forceinline uint32_t
MD5::F(uint32_t x, uint32_t y, uint32_t z)
{
    return x & y | ~x & z;
}

__forceinline uint32_t
MD5::G(uint32_t x, uint32_t y, uint32_t z)
{
    return x & z | y & ~z;
}

__forceinline uint32_t
MD5::H(uint32_t x, uint32_t y, uint32_t z)
{
    return x ^ y ^ z;
}

__forceinline uint32_t
MD5::I(uint32_t x, uint32_t y, uint32_t z)
{
    return y ^ (x | ~z);
}

// rotate_left rotates x left n bits.
__forceinline uint32_t
MD5::rotate_left(uint32_t x, int n)
{
    // return (x << n) | (x >> (32 - n));
    return _rotl(x, n);
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
__forceinline void
MD5::FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
}

__forceinline void
MD5::GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

__forceinline void
MD5::HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

__forceinline void
MD5::II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
    a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}

// compute MD5 for string and finalize it right away
MD5::MD5(std::string const& text)
{
    Update(reinterpret_cast<uint8_t const*>(text.data()), static_cast<size_type>(text.length()));
    Finalize();
}

// Decodes input uint8_t* into output uint32_t*. Assumes len is a multiple of 4.
void
MD5::Decode(uint32_t* output, uint8_t const* input)
{
    for (size_type i{}, j{}; j < kBlockSize; ++i, j += 4)
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
                    (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
}

// encodes input (uint4) into output (unsigned char). Assumes len is
// a multiple of 4.
void
MD5::Encode(uint8_t* output, uint32_t const* input, size_type len)
{
    for (size_type i{}, j{}; j < len; ++i, j += 4) {
        output[j] = input[i] & 0xff;
        output[j + 1] = (input[i] >> 8) & 0xff;
        output[j + 2] = (input[i] >> 16) & 0xff;
        output[j + 3] = (input[i] >> 24) & 0xff;
    }
}

// apply MD5 algo on a block
void
MD5::Transform(uint8_t const* block)
{
    uint32_t a{state_[0]};
    uint32_t b{state_[1]};
    uint32_t c{state_[2]};
    uint32_t d{state_[3]};
    uint32_t x[16];
    Decode(x, block);

    // Round 1 */
    /* Let [abcd k s i] denote the operation
    a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). */
    FF(a, b, c, d, x[0], S11, 0xd76aa478);   // 1
    FF(d, a, b, c, x[1], S12, 0xe8c7b756);   // 2
    FF(c, d, a, b, x[2], S13, 0x242070db);   // 3
    FF(b, c, d, a, x[3], S14, 0xc1bdceee);   // 4
    FF(a, b, c, d, x[4], S11, 0xf57c0faf);   // 5
    FF(d, a, b, c, x[5], S12, 0x4787c62a);   // 6
    FF(c, d, a, b, x[6], S13, 0xa8304613);   // 7
    FF(b, c, d, a, x[7], S14, 0xfd469501);   // 8
    FF(a, b, c, d, x[8], S11, 0x698098d8);   // 9
    FF(d, a, b, c, x[9], S12, 0x8b44f7af);   // 10
    FF(c, d, a, b, x[10], S13, 0xffff5bb1);  // 11
    FF(b, c, d, a, x[11], S14, 0x895cd7be);  // 12
    FF(a, b, c, d, x[12], S11, 0x6b901122);  // 13
    FF(d, a, b, c, x[13], S12, 0xfd987193);  // 14
    FF(c, d, a, b, x[14], S13, 0xa679438e);  // 15
    FF(b, c, d, a, x[15], S14, 0x49b40821);  // 16

    // Round 2
    /* Let [abcd k s i] denote the operation
    a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). */
    GG(a, b, c, d, x[1], S21, 0xf61e2562);   // 17
    GG(d, a, b, c, x[6], S22, 0xc040b340);   // 18
    GG(c, d, a, b, x[11], S23, 0x265e5a51);  // 19
    GG(b, c, d, a, x[0], S24, 0xe9b6c7aa);   // 20
    GG(a, b, c, d, x[5], S21, 0xd62f105d);   // 21
    GG(d, a, b, c, x[10], S22, 0x2441453);   // 22
    GG(c, d, a, b, x[15], S23, 0xd8a1e681);  // 23
    GG(b, c, d, a, x[4], S24, 0xe7d3fbc8);   // 24
    GG(a, b, c, d, x[9], S21, 0x21e1cde6);   // 25
    GG(d, a, b, c, x[14], S22, 0xc33707d6);  // 26
    GG(c, d, a, b, x[3], S23, 0xf4d50d87);   // 27
    GG(b, c, d, a, x[8], S24, 0x455a14ed);   // 28
    GG(a, b, c, d, x[13], S21, 0xa9e3e905);  // 29
    GG(d, a, b, c, x[2], S22, 0xfcefa3f8);   // 30
    GG(c, d, a, b, x[7], S23, 0x676f02d9);   // 31
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);  // 32

    // Round 3
    /* Let[abcd k s t] denote the operation
    a = b + ((a + H(b, c, d) + X[k] + T[i]) << < s). */
    HH(a, b, c, d, x[5], S31, 0xfffa3942);   // 33
    HH(d, a, b, c, x[8], S32, 0x8771f681);   // 34
    HH(c, d, a, b, x[11], S33, 0x6d9d6122);  // 35
    HH(b, c, d, a, x[14], S34, 0xfde5380c);  // 36
    HH(a, b, c, d, x[1], S31, 0xa4beea44);   // 37
    HH(d, a, b, c, x[4], S32, 0x4bdecfa9);   // 38
    HH(c, d, a, b, x[7], S33, 0xf6bb4b60);   // 39
    HH(b, c, d, a, x[10], S34, 0xbebfbc70);  // 40
    HH(a, b, c, d, x[13], S31, 0x289b7ec6);  // 41
    HH(d, a, b, c, x[0], S32, 0xeaa127fa);   // 42
    HH(c, d, a, b, x[3], S33, 0xd4ef3085);   // 43
    HH(b, c, d, a, x[6], S34, 0x4881d05);    // 44
    HH(a, b, c, d, x[9], S31, 0xd9d4d039);   // 45
    HH(d, a, b, c, x[12], S32, 0xe6db99e5);  // 46
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8);  // 47
    HH(b, c, d, a, x[2], S34, 0xc4ac5665);   // 48

    // Round 4
    /* Let [abcd k s t] denote the operation
    a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s). */
    II(a, b, c, d, x[0], S41, 0xf4292244);   // 49
    II(d, a, b, c, x[7], S42, 0x432aff97);   // 50
    II(c, d, a, b, x[14], S43, 0xab9423a7);  // 51
    II(b, c, d, a, x[5], S44, 0xfc93a039);   // 52
    II(a, b, c, d, x[12], S41, 0x655b59c3);  // 53
    II(d, a, b, c, x[3], S42, 0x8f0ccc92);   // 54
    II(c, d, a, b, x[10], S43, 0xffeff47d);  // 55
    II(b, c, d, a, x[1], S44, 0x85845dd1);   // 56
    II(a, b, c, d, x[8], S41, 0x6fa87e4f);   // 57
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0);  // 58
    II(c, d, a, b, x[6], S43, 0xa3014314);   // 59
    II(b, c, d, a, x[13], S44, 0x4e0811a1);  // 60
    II(a, b, c, d, x[4], S41, 0xf7537e82);   // 61
    II(d, a, b, c, x[11], S42, 0xbd3af235);  // 62
    II(c, d, a, b, x[2], S43, 0x2ad7d2bb);   // 63
    II(b, c, d, a, x[9], S44, 0xeb86d391);   // 64

    state_[0] += a;
    state_[1] += b;
    state_[2] += c;
    state_[3] += d;

    // Zeroize sensitive information.
    memset(x, 0, sizeof x);
}

// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void
MD5::Update(uint8_t const* input, size_type length)
{
    // compute number of bytes mod 64
    size_type index = count_[0] / 8 % kBlockSize;

    // Update number of bits
    if ((count_[0] += (length << 3)) < (length << 3)) {
        ++count_[1];
    }
    count_[1] += (length >> 29);

    // number of bytes we need to fill in buffer
    size_type firstpart = 64 - index;

    size_type i;

    // transform as many times as possible.
    if (length >= firstpart) {
        // fill buffer first, transform
        memcpy(&buffer_[index], input, firstpart);
        Transform(buffer_.data());

        // transform chunks of blocksize (64 bytes)
        for (i = firstpart; i + kBlockSize <= length; i += kBlockSize) Transform(&input[i]);

        index = 0;
    }
    else
        i = 0;

    // buffer remaining input
    memcpy(&buffer_[index], &input[i], length - i);
}

// for convenience provide a verson with signed char
void
MD5::Update(int8_t const* input, size_type length)
{
    Update((uint8_t const*)input, length);
}

// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
MD5&
MD5::Finalize()
{
    static constexpr uint8_t const padding[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (!finalized_) {
        // save number of bits
        uint8_t bits[8];
        Encode(bits, count_, 8);

        // pad out to 56 mod 64.
        size_type index = count_[0] / 8 % 64;
        size_type pad_len = (index < 56) ? (56 - index) : (120 - index);
        Update(padding, pad_len);

        // append length, before padding
        Update(bits, 8);

        // store state in digest
        Encode(digest_, state_, 16);

        // Zeroize sensitive information.
        std::fill_n(buffer_.data(), buffer_.size(), 0);
        memset(count_, 0, sizeof count_);

        finalized_ = true;
    }

    return *this;
}

// return hex representation of digest as string
std::string
MD5::HexDigest() const
{
    std::string result;
    if (!finalized_) return result;

    char buf[33];
    for (int i{}; i < 16; ++i) {
        sprintf(buf + i * 2, "%02x", digest_[i]);
    }
    buf[32] = 0;

    return std::string(buf);
}

std::ostream&
operator<<(std::ostream& out, MD5 md5)
{
    return out << md5.HexDigest();
}

std::string
md5(std::string const& str)
{
    return MD5(str).HexDigest();
}

}  // namespace aoc2016::md5
