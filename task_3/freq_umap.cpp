#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    const std::string file_path = argv[1];

    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Error of open file\n";
        return 1;
    }

    std::unordered_map<std::string, int> freq_umap;
    std::vector<std::string> buffer;
    std::string word;

    while (file >> word) {
        buffer.push_back(word);
    }

    auto start_build = std::chrono::steady_clock::now();

    std::for_each(
            buffer.begin(),
            buffer.end(),
            [&freq_umap](const std::string& word) { ++freq_umap[word]; });

    auto finish_build = std::chrono::steady_clock::now();
    auto duration_build = std::chrono::duration_cast<std::chrono::microseconds>(
            finish_build - start_build);

    std::vector<std::pair<std::string, int>> sort_words(
            freq_umap.begin(), freq_umap.end());

    auto start_sort = std::chrono::steady_clock::now();

    std::sort(
            sort_words.begin(),
            sort_words.end(),
            [](const auto& a, const auto& b) {
                if (a.second == b.second) {
                    return a.first < b.first;
                }
                return a.second > b.second;
            });

    auto finish_sort = std::chrono::steady_clock::now();
    auto duration_sort = std::chrono::duration_cast<std::chrono::microseconds>(
            finish_sort - start_sort);

    for (size_t i = 0; i < 10 && i < sort_words.size(); ++i) {
        std::cout << sort_words[i].second << " " << sort_words[i].first << "\n";
    }

    std::cout << "build: " << duration_build.count() << "\n";
    std::cout << "sort: " << duration_sort.count() << "\n";

    return 0;
}
