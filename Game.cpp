#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;
Game::Game(){
    string seed;
    int i;
    quit = 0;
    cout << "Enter seed" << endl;
    getline(cin, seed);
    if (seed.empty()) {
        cout << "Missing user input - quiting game." << endl;
        quit = 1;
    }
    istringstream(seed) >> i;
    dice = new Dice(i);
    player1 = new Board("White");
    player2 = new Board("Black");
}
bool Game::helper(Board* b){
    //a method that will tell us if all the remaining checkers are in the "home" of the player. if so returns true else false
    for(int i=25; i>6; i--){
        if(b->board[i] != 0){
            return false;
        }
    }
    return true;
}
bool Game::helper2(Board* b, int throw1, int throw2){
    //a method that will be helpfull only when the case is that we got a bigger value un one of
    // the throws but the reamaing checkers are smaller than this throw
    //in that case the nethod will return true and will do the move
    int max;
    if(throw1 >= throw2){
        max = throw1;
    }
    else{
        max = throw2;
    }
    for (int i = max; i <7 ; i++) {
        if(b->board[i] != 0){
            return false;
        }
    }
    return true;
}
bool Game::is_legal(Board *b, Board *other, int from, int to, int throw1, int throw2) {
    if(((from < 1) || (from > 25)) || ((to < 0) || (to > 24)) || ((abs(from-to) <= 0) || (abs(from-to) > 6))){
        cout << "Illegal move: From/to out of bounds (from=" << from << ", to=" << to << ")." << endl;
        return false;
    } else {
        if ((b->board[25] != 0) && (from != 25)) {
            cout << "Illegal move: Player still has captured piece(s)." << endl;
            return false;
        } else {
            if (b->board[from] == 0) {
                cout << "Illegal move: No pieces at from location " << from << "." << endl;
                return false;
            } else {
                if (other->board[25 - to] > 1) {
                    cout << "Illegal move: Cannot capture more that one piece at location " << to << "." << endl;
                    return false;
                } else {
                    if ((to == 0) && !helper(b)) {
                        cout << "Illegal move: Cannot bear off while not all pieces at home." << endl;
                        return false;
                    } else {
                        if (((abs(to - from) != throw1) && (abs(to - from) != throw2)) && !helper2(b, throw1, throw2)) {
                            cout << "Illegal move: No value of " << abs(to - from) << " in dice roll " << endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
bool Game::is_possible(Board *b, Board *other, int throw1, int throw2) {
    int counter = 0;
    if(b->board[25] != 0){
        if((other->board[throw1] > 1) && (other->board[throw2] > 1)){
            return false;
        }
    }
    return true;
}
bool Game::play(Board *b, Board *other, int throw1, int throw2) {
    int flag = 0;
    bool legal;
    string move;
    int from, to;
    while (flag == 0) {
        cout << "Enter " << b->color << " move: " << endl;
        getline(cin, move);
        if (move.empty()) {
            cout << "Missing user input - quiting game." << endl;
            return false;
        }
        istringstream(move) >> from >> to;
        //checking if the entered move is legal
        legal = is_legal(b, other, from, to, throw1, throw2);
        if (legal == true) {
            break;
        }
        if (legal == false) {
            continue;
        }
    }
    if(other->board[25-to] == 1){
        other->board[25]++;
        other->board[25-to] = 0;
    }
    b->board[from]--;
    b->board[to]++;
    return true;
}
int Game::turn(Board *b, Board *other) {
    int throw1, throw2;
    bool success;
    b->printBoard(other);
    throw1 = dice->generate();
    throw2 = dice->generate();
    cout << b->color << " rolls " << throw1 << "-" << throw2 << "." << endl;
    //checking if the player has any possible moves
    if (!is_possible(b, other, throw1, throw2)) {
        cout << "No possible move for " << b->color << endl;
    } else {
        if (throw1 == throw2) {
            for (int i = 0; i < 4; i++) {
                success = play(b, other, throw1, throw2);
                if(!success) {
                    return -1; //failed reading input ending game
                }
                else{
                    if (b->board[0] == 15) { // checking after every turn if the player has finished won or not
                        return 1;
                    }
                }
            }
        } else {
            for (int i = 0; i < 2; i++) {
                success = play(b, other, throw1, throw2);
                if(!success) {
                    return -1;
                }
                else{
                    if (b->board[0] == 15) {  // checking after every turn if the player has finished won or not
                        return 1;
                    }
                }
            }
        }

    }
    return 0;
}
void Game::start() {
    int throw1, throw2, flag = 0, from, to, get, counter;
    Board *first, *second;
    if(quit == 0){
        //each player throw the dice
        //finding out how will start first
        while (flag == 0) {
            throw1 = dice->generate();
            throw2 = dice->generate();
            cout << "White player casts " << throw1 << ", " << "black player casts " << throw2 << endl;
            if (throw1 > throw2) {
                first = player1;
                second = player2;
                break;
            }
            if (throw2 > throw1) {
                first = player2;
                second = player1;
                break;
            }
        }
        cout << first->color << " plays first." << endl;
        while (flag == 0) {
            if((turn(first, second) == -1) || (turn(second, first) == -1)){
                break;
            }
            else {
                if (turn(first, second) == 1) {
                    cout << first->color << " player wins!" << endl;
                    break;
                }
                if (turn(second, first) == 1) {
                    cout << second->color << " player wins!" << endl;
                    break;
                }
            }
        }
    }
}