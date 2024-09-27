#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>

char get_soundex_digit(char ch)
{
    std::string sound = "01230120022554012623010202";
    const int alpha = std::tolower(ch) - 'a';

    return sound[alpha];
}

std::string soundex(const std::string& name)
{
    if (!std::all_of(name.begin(), name.end(), ::isalpha)) {
        return "0000";
    }

    const char first_letter = std::toupper(name[0]);

    std::string digits;
    std::ranges::transform(
            name.begin() + 1,
            name.end(),
            std::back_inserter(digits),
            get_soundex_digit);

    digits.erase(std::remove(digits.begin(), digits.end(), '0'), digits.end());

    std::string result;
    std::ranges::unique_copy(digits, std::back_inserter(result));

    result.insert(result.begin(), first_letter);

    result.resize(4, '0');

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: soundex <name>"
                  << "\n";
        return 1;
    }

    const std::string name = argv[1];
    std::cout << soundex(name) << "\n";

    return 0;
}
