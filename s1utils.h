#ifndef S1UTILS_H
#define S1UTILS_H

#include <cstdint>
#include <deque>
#include <string>

// Bytes are stored from most-significant to least-significant.
typedef uint8_t Byte;
typedef std::deque<Byte> Bytes;

// Digit to value
uint8_t hex_value(char hex);
uint8_t base64_value(char base64);

// Value to digit
char hex_digit(uint8_t value, bool upper_case = false);
char base64_digit(uint8_t value);

// Encoding
std::string base64_encode(Bytes bytes);
std::string hex_encode(Bytes bytes, bool upper_case = false);
std::string as_string(Bytes bytes);

// Decoding
Bytes base64_decode(std::string base64);
Bytes hex_decode(std::string hex);
Bytes as_bytes(const char bytes[]);

// Operators
Bytes xor_bytes(const Bytes &b1, const Bytes &b2);
Bytes xor_bytes(const Bytes &bytes, char c);

#endif /* S1UTILS_H */
