#ifndef HW2_GAME_H
#define HW2_GAME_H
#include <string>
#include "Dice.h"
#include "Board.h"

using namespace std;
class Game {
public:
    Game();
    void start();
    bool helper(Board* b);
    bool helper2(Board* b, int throw1, int throw2);
    bool is_legal(Board* b, Board *other, int from, int to, int throw1, int throw2);
    bool is_possible(Board* b, Board *other, int throw1, int throw2);
    bool play(Board *b, Board *other, int throw1, int throw2);
    int turn(Board *b, Board *other);
private:
    string first;
    int quit;
    Dice *dice;
    Board *player1;
    Board *player2;
};


#endif //HW2_GAME_H
