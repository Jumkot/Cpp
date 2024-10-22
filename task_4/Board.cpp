#include "Board.hpp"

Board::Board(
        int rows,
        int cols,
        int mines,
        std::vector<std::pair<int, int>>& mines_coords)
    : rows_(rows),
      columns_(cols),
      mines_(mines),
      Field(rows, std::vector<Cell>(cols))
{
    for (const auto& pair : mines_coords) {
        const int x = pair.first;
        const int y = pair.second;

        if (x >= 0 && x < rows_ && y >= 0 && y < columns_) {
            Field[x][y].has_mine_ = true;
        }
    }
    countMines();
}

void Board::countMines()
{
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            if (Field[i][j].has_mine_) {
                continue;
            }

            size_t count = 0;

            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    const int ni = i + x;
                    const int nj = j + y;

                    if (isCell(ni, nj) && Field[ni][nj].has_mine_) {
                        count++;
                    }
                }
            }

            Field[i][j].mines_count_ = count;
        }
    }
}

bool Board::isCell(int row, int col) const
{
    return (row >= 0 && row < rows_ && col >= 0 && col < columns_);
}

int Board::openCell(int row, int col)
{
    if (!isCell(row, col)) {
        return 1;
    }

    if (Field[row][col].is_opened_ || Field[row][col].has_flag_) {
        return 2;
    }

    Field[row][col].is_opened_ = true;

    if (Field[row][col].has_mine_) {
        return 3;
    }

    if (Field[row][col].mines_count_ == 0) {
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                openCell(row + x, col + y);
            }
        }
    }

    return 0;
}

void Board::flagCell(int row, int col)
{
    if (!isCell(row, col)) {
        return;
    }

    if (Field[row][col].is_opened_ || Field[row][col].has_flag_) {
        return;
    }

    Field[row][col].has_flag_ = true;
}

void Board::printBoard(std::ostream& stream) const
{
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            const Cell& now_cell = Field[i][j];

            if (!now_cell.is_opened_) {
                if (now_cell.has_flag_) {
                    stream << "F";
                } else {
                    stream << "#";
                }
            } else {
                if (now_cell.has_mine_) {
                    stream << "*";
                } else if (now_cell.mines_count_ > 0) {
                    stream << now_cell.mines_count_;
                } else {
                    stream << ".";
                }
            }
        }
        stream << "\n";
    }
}

void Board::isWin() const
{
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < columns_; ++j) {
            if (!(Field[i][j].has_mine_) && !(Field[i][j].is_opened_)) {
                return;
            }
        }
    }
    printBoard(std::cout);
    std::cout << "You win!\n";
    std::exit(0);
}

void Board::useCommand(std::string command, int row, int col)
{
    if (command == "open") {
        const int result = openCell(row, col);
        if (result == 1) {
            std::cout << "Invalid cell coordinates.\n";
        } else if (result == 2) {
            std::cout << "Cell already opened or flagged.\n";
        } else if (result == 3) {
            std::cout << "You lose!\n";
            std::exit(0);
        }
    } else if (command == "flag") {
        flagCell(row, col);
    }
}

void Board::startBoard()
{
    std::string command;
    while (true) {
        printBoard(std::cout);
        std::cin >> command;
        if (command == "open" || command == "flag") {
            int row;
            int col;
            std::cin >> row >> col;
            useCommand(command, row, col);
        } else if (command == "exit") {
            std::exit(0);
        } else {
            std::cout << "Invalid command.\n";
        }
        isWin();
    }
}