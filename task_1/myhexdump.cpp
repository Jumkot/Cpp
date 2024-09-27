#include <fstream>
#include <iomanip>
#include <iostream>

void myhexdump(auto& stream)
{
    unsigned char str[16];
    int address = 0;

    while (stream.read(reinterpret_cast<char*>(str), sizeof(str))
           || stream.gcount() > 0) {
        const int read_bytes = stream.gcount();

        std::cout << std::setw(8) << std::setfill('0') << std::hex << address
                  << "  ";

        for (int i = 0; i < 16; ++i) {
            if (i < read_bytes) {
                std::cout << std::setw(2) << std::setfill('0') << std::hex
                          << static_cast<int>(str[i]) << " ";
            } else {
                std::cout << "   ";
            }

            if (i == 7)
                std::cout << "  ";
        }

        std::cout << "|";

        for (int i = 0; i < read_bytes; ++i) {
            if (std::isprint(str[i])) {
                std::cout << str[i];
            } else {
                std::cout << '.';
            }
        }

        std::cout << "|\n";

        address += read_bytes;
    }
}

int main([[maybe_unused]] int argc, char* argv[])
{
    const char* file_path;
    if (argc) {
        file_path = argv[1];
    }
    std::ifstream file(file_path);
    auto& stream = file.is_open() ? file : std::cin;
    myhexdump(stream);

    file.close();
    return 0;
}
