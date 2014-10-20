#include "s1utils.h"

#include <iostream>

int main()
{
    std::string hex;
    Bytes bytes;

    while (std::cin >> hex) {
        bytes = hex_decode(hex);
        std::cout << base64_encode(bytes) << '\n';
    }

    return 0;
}
