#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Cell
{
public:
    bool is_opened_ = false;
    bool has_flag_  = false;
    bool has_mine_ = false;
    size_t mines_count_ = 0;
};

class Board {
public:
    Board(int rows, int cols, int mines, std::vector<std::pair<int, int>>& mines_coords);
   
    void startBoard();

private:
    const int rows_;
    const int columns_;
    const int mines_;
    std::vector<std::vector<Cell>> Field;
    
    bool isCell(int row, int col) const;
    int openCell(int row, int col);
    void flagCell(int row, int col);
    void printBoard(std::ostream& stream) const; 
    void countMines();
    void isWin() const;
    void useCommand(std::string command, int row, int col);
};

#endif
