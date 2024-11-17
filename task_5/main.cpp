#include "normpath.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ./normpath <path>\n";
        return 1;
    }

    try {
        const std::string normalized_path = normpath(argv[1]);
        std::cout << normalized_path << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}