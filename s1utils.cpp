#include "s1utils.h"

#include <cassert>

uint8_t hex_value(char hex)
{
    assert(('0' <= hex && hex <= '9')
           || ('a' <= hex && hex <= 'f')
           || ('A' <= hex && hex <= 'F'));

    if ('0' <= hex && hex <= '9') {
        return hex - '0';
    } else if ('a' <= hex && hex <= 'f') {
        return hex - 'a' + 10;
    } else if ('A' <= hex && hex <= 'F') {
        return hex - 'A' + 10;
    }

    // Shouldn't get to here.
    return std::numeric_limits<uint8_t>::max();
}

uint8_t base64_value(char base64)
{
    assert(('A' <= base64 && base64 <= 'Z')
           || ('a' <= base64 && base64 <= 'z')
           || ('0' <= base64 && base64 <= '9')
           || (base64 == '+')
           || (base64 == '/'));

    if ('A' <= base64 && base64 <= 'Z') {
        return base64 - 'A';
    } else if ('a' <= base64 && base64 <= 'z') {
        return base64 - 'a' + 26;
    } else if ('0' <= base64 && base64 <= '9') {
        return base64 - '0' + 52;
    } else if (base64 == '+') {
        return 62;
    } else if (base64 == '/') {
        return 63;
    }

    // Shouldn't get to here.
    return std::numeric_limits<uint8_t>::max();
}

char hex_digit(uint8_t value, bool upper_case)
{
    assert(value < 16);

    if (value < 10) {
        return '0' + value;
    } else if (upper_case) {
        return 'A' + (value - 10);
    } else {
        return 'a' + (value - 10);
    }

    // Shouldn't get to here.
    return std::numeric_limits<char>::max();
}

char base64_digit(uint8_t value)
{
    assert(value < 64);

    if (value < 26) {
        return 'A' + value;
    } else if (value < 52) {
        return 'a' + (value - 26);
    } else if (value < 62) {
        return '0' + (value - 52);
    } else if (value == 62) {
        return '+';
    } else if (value == 63) {
        return '/';
    }

    // Shouldn't get to here.
    return std::numeric_limits<char>::max();
}

std::string hex_encode(Bytes bytes, bool upper_case)
{
    std::string result;

    for (Bytes::const_iterator b = bytes.begin(); b != bytes.end(); ++b) {
        result.insert(0, 1, hex_digit(*b % 16, upper_case));
        result.insert(0, 1, hex_digit(*b / 16, upper_case));
    }

    return result;
}

std::string base64_encode(Bytes bytes)
{
    std::string result;
    uint16_t current = 0;
    uint8_t offset = 0;

    for (Bytes::size_type i = 0; i < bytes.size(); ++i) {
        Bytes::size_type idx = bytes.size() - i - 1;
        current += bytes[idx] << offset;
        offset += 8;

        if (offset >= 6 || i == 0) {
            while (offset >= 6) {
                result.insert(0, 1, base64_digit(current % 64));
                current /= 64;
                offset -= 6;
            }
        }
    }

    return result;
}

std::string as_string(Bytes bytes)
{
    std::string result;

    for (auto i = bytes.begin(); i != bytes.end(); ++i) {
        result.push_back(*i);
    }

    return result;
}

Bytes hex_decode(std::string hex)
{
    Byte byte = 0;
    Bytes result;

    for (std::string::size_type i = 0; i < hex.size(); ++i) {
        std::string::size_type idx = hex.size() - i - 1;
        byte += hex_value(hex[idx]) << ((i % 2) * 4);

        if (i % 2 == 1 || idx == 0) {
            result.push_front(byte);
            byte = 0;
        }
    }

    return result;
}

Bytes base64_decode(std::string base64)
{
    Bytes result;
    uint16_t current = 0;
    uint8_t offset = 0;

    for (std::string::size_type i = 0; i < base64.size(); ++i) {
        std::string::size_type idx = base64.size() - i - 1;
        current += base64_value(base64[idx]) << offset;
        offset += 6;

        if (current >= 256 || idx == 0) {
            result.push_front(current % 256);
            current /= 256;
            offset -= 8;
        }
    }

    return result;
}

Bytes as_bytes(const char bytes[])
{
    Bytes result;
    const char *current = bytes;

    while (*current != '\0') {
        result.push_back(*current);
        current++;
    }

    return result;
}

Bytes xor_bytes(const Bytes &b1, const Bytes &b2)
{
    Bytes result;

    for (Bytes::size_type i = 0; i < std::max(b1.size(), b2.size()); ++i) {
        uint8_t byte1 = (i < b1.size()) ? b1[i] : 0;
        uint8_t byte2 = (i < b2.size()) ? b2[i] : 0;

        result.push_back(byte1 ^ byte2);
    }

    return result;
}

Bytes xor_bytes(const Bytes &bytes, char c)
{
    Bytes result;

    for (auto i = bytes.begin(); i != bytes.end(); ++i) {
        result.push_back(*i ^ c);
    }

    return result;
}

