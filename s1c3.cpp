#include "s1utils.h"

#include <iostream>

int score(Byte b)
{
    if ((b < 'A' || b > 'Z') && (b < 'a' || b > 'z')) {
        return 0;
    }

    switch (b) {
        case 'E': case 'T': case 'A': case 'O': case 'I': case 'N':
        case 'S': case 'H': case 'R': case 'D': case 'L': case 'U':
        case 'e': case 't': case 'a': case 'o': case 'i': case 'n':
        case 's': case 'h': case 'r': case 'd': case 'l': case 'u':
            return 3;
        default:
            return 2;
    }
}

int score(const Bytes &b)
{
    int result = 0;
    for (auto i = b.begin(); i != b.end(); ++i) {
        result += score(*i);
    }
    return result;
}

int main()
{
    std::string encoded;

    while (std::cin >> encoded) {
        Bytes bytes = hex_decode(encoded);
        Bytes best;
        int best_score = -1;

        for (char i = 0; i <= std::numeric_limits<char>::max(); ++i) {
            Bytes after_xor = xor_bytes(bytes, i);
            int s = score(after_xor);

            std::cout << as_string(after_xor) << '\n';

            if (s > best_score) {
                best = after_xor;
                best_score = s;
            }

            if (i == std::numeric_limits<char>::max()) {
                break;
            }
        }

        std::cout << "Result: " << as_string(best) << '\n';
    }

    return 0;
}
