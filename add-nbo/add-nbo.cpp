#include <iostream>
#include <fstream>
#include <cstdint>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    std::ifstream file1(argv[1], std::ios::binary);
    std::ifstream file2(argv[2], std::ios::binary);

    uint32_t n1, n2;
    file1.read(reinterpret_cast<char*>(&n1), sizeof(n1));
    file2.read(reinterpret_cast<char*>(&n2), sizeof(n2));

    uint32_t num1 = ntohl(n1);
    uint32_t num2 = ntohl(n2);

    n1 = num1;
    n2 = num2;

    std::cout << std::dec << n1 << "(0x" << std::hex << n1 << ") + "
              << std::dec << n2 << "(0x" << std::hex << n2 << ") = "
              << std::dec << n1 + n2 << "(0x" << std::hex << n1 + n2 << ")" << std::endl;

    return 0;
}

