#ifndef HW2_BOARD_H
#define HW2_BOARD_H
#include <string>

using namespace std;
class Board {
public:
    Board(const string c);//constructor
    void init(const string c); //initialize a new game board
    void printBoard(Board* other); //printing the board at the current stage he's in
    int board[26];
    string color;
};


#endif //HW2_BOARD_H
