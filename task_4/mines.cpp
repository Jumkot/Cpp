#include "Board.hpp"

int main()
{
    int rows;
    int cols;
    int mines;

    std::cin >> rows >> cols;
    std::cin >> mines;

    std::vector<std::pair<int, int>> mines_coords;

    for (int i = 1; i <= mines; i++) {
        int x, y;
        std::cin >> x >> y;
        mines_coords.push_back({x, y});
    }

    Board board(rows, cols, mines, mines_coords);
    board.startBoard();

    return 0;
}