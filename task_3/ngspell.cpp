#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> make_3(const std::string& word)
{
    std::vector<std::string> threes;
    if (word.size() < 3) {
        return threes;
    }

    for (size_t i = 0; i <= word.size() - 3; ++i) {
        threes.push_back(word.substr(i, 3));
    }

    return threes;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    const std::string file_path = argv[1];

    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Error opening dictionary file!\n";
        return 1;
    }

    std::unordered_map<std::string, std::vector<std::string>> threes;
    std::string word;

    while (file >> word) {
        auto trigrams = make_3(word);
        for (const auto& trigram : trigrams) {
            threes[trigram].push_back(word);
        }
    }

    std::string search;

    while (std::getline(std::cin, search) && search != ":q") {
        auto search_trigrams = make_3(search);

        std::unordered_map<std::string, int> similar;

        for (const auto& trigram : search_trigrams) {
            if (threes.find(trigram) != threes.end()) {
                for (const auto& step : threes[trigram]) {
                    similar[step]++;
                }
            }
        }

        int max_count = 0;
        for (const auto& step : similar) {
            if (step.second > max_count) {
                max_count = step.second;
            }
        }

        std::set<std::string> results;
        for (const auto& step : similar) {
            if (step.second == max_count) {
                results.insert(step.first);
            }
        }

        std::cout << results.size() << "\n";
        for (const auto& result : results) {
            std::cout << result << "\n";
        }
    }

    return 0;
}
