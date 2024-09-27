#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>

void myhead(auto& stream, char mode, int number)
{
    if (mode == '\0') {
        mode = 'n';
        number = 10;
    }

    int count = 0;
    char ch;

    if (mode == 'n') {
        while (count < number && stream.get(ch)) {
            std::cout.put(ch);
            if (ch == '\n') {
                count++;
            }
        }
    } else {
        while (count < number && stream.get(ch)) {
            std::cout.put(ch);
            count++;
        }
    }
}

int main(int argc, char* argv[])
{
    const char* file_path;
    if (argc) {
        file_path = argv[1];
    }
    std::ifstream file(file_path);
    auto& stream = file.is_open() ? file : std::cin;

    char mode = '\0';
    int number = 0;

    int option;
    while ((option = getopt(argc, argv, "n:c:")) != -1) {
        switch (option) {
        case 'n':
            mode = 'n';
            number = std::atoi(optarg);
            if (number <= 0) {
                std::cerr << "Error: number of lines must be non-negative.\n";
                return 1;
            }
            break;
        case 'c':
            mode = 'c';
            number = std::atoi(optarg);
            if (number <= 0) {
                std::cerr << "Error: number of bytes must be non-negative.\n";
                return 1;
            }
            break;
        default:
            std::cerr << "Error: undefined option.\n";
            return 1;
        }
    }

    myhead(stream, mode, number);

    file.close();

    return 0;
}
