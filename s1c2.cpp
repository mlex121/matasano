#include "s1utils.h"

#include <iostream>

int main()
{
    std::string n1, n2;
    Bytes b1, b2;

    while (std::cin >> n1 && std::cin >> n2) {
        std::cout << hex_encode(xor_bytes(hex_decode(n1), hex_decode(n2))) << '\n';
    }

    return 0;
}
