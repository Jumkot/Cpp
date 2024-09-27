#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

bool dice_num(const std::vector<int>& dice)
{
    return std::all_of(
            dice.begin(), dice.end(), [](int d) { return d > 0 && d < 7; });
}

int num_sum(const std::vector<int>& dice, int num)
{
    return std::count(dice.begin(), dice.end(), num);
}

bool num_of_a_kind(const std::vector<int>& dice, int n)
{
    for (int i = 1; i < 7; i++) {
        if (std::count(dice.begin(), dice.end(), i) >= n) {
            return true;
        }
    }
    return false;
}

bool full_house(const std::vector<int>& dice)
{
    std::vector<int> counts(6, 0);

    std::for_each(dice.begin(), dice.end(), [&counts](int num) {
        counts[num - 1]++;
    });

    return ((std::find(counts.begin(), counts.end(), 2) != counts.end())
            && (std::find(counts.begin(), counts.end(), 3) != counts.end()));
}

bool small_straight(const std::vector<int>& dice)
{
    std::vector<int> sort_dice = dice;
    std::ranges::sort(sort_dice);
    sort_dice.erase(
            std::unique(sort_dice.begin(), sort_dice.end()), sort_dice.end());

    std::vector<int> small_1 = {1, 2, 3, 4};
    std::vector<int> small_2 = {2, 3, 4, 5};
    std::vector<int> small_3 = {3, 4, 5, 6};

    return (std::ranges::includes(sort_dice, small_1))
            || (std::ranges::includes(sort_dice, small_2))
            || (std::ranges::includes(sort_dice, small_3));
}

bool large_straight(const std::vector<int>& dice)
{
    std::vector<int> sort_dice = dice;
    std::ranges::sort(sort_dice);
    sort_dice.erase(
            std::unique(sort_dice.begin(), sort_dice.end()), sort_dice.end());

    std::vector<int> large_1 = {1, 2, 3, 4, 5};
    std::vector<int> large_2 = {2, 3, 4, 5, 6};

    return (std::ranges::includes(sort_dice, large_1))
            || (std::ranges::includes(sort_dice, large_2));
}

int main()
{
    std::vector<int> dice(5);

    for (int& num : dice) {
        std::cin >> num;
    }

    if (!dice_num(dice)) {
        std::cerr << "Error: invalid dice value\n";
        return 1;
    }

    std::cout << "Ones:             " << num_sum(dice, 1) << "\n";
    std::cout << "Twos:             " << num_sum(dice, 2) << "\n";
    std::cout << "Threes:           " << num_sum(dice, 3) << "\n";
    std::cout << "Fours:            " << num_sum(dice, 4) << "\n";
    std::cout << "Fives:            " << num_sum(dice, 5) << "\n";
    std::cout << "Sixes:            " << num_sum(dice, 6) << "\n";

    const int dice_sum = std::accumulate(dice.begin(), dice.end(), 0);

    std::cout << "Three Of A Kind:  " << (num_of_a_kind(dice, 3) ? dice_sum : 0)
              << "\n";
    std::cout << "Four Of A Kind:   " << (num_of_a_kind(dice, 4) ? dice_sum : 0)
              << "\n";
    std::cout << "Full House:       " << (full_house(dice) ? 25 : 0) << "\n";
    std::cout << "Small Straight:   " << (small_straight(dice) ? 30 : 0)
              << "\n";
    std::cout << "Large Straight:   " << (large_straight(dice) ? 40 : 0)
              << "\n";
    std::cout << "Yahtzee:          " << (num_of_a_kind(dice, 5) ? 50 : 0)
              << "\n";
    std::cout << "Chance:           " << dice_sum << "\n";

    return 0;
}