#include "Board.h"
#include <iostream>
#include <iomanip>

using namespace std;
Board::Board(const string c) {init(c);}
void Board::init(const string c) {
    for(int i=0; i<26;i++){
        if(i == 6){
            board[i] = 5;
        }
        else{
            if(i == 8){
                board[i] = 3;
            }
            else{
                if(i == 13){
                    board[i] = 5;
                }
                else{
                    if(i == 24){
                        board[i] = 2;

                    }
                    else{
                        board[i] = 0;
                    }
                }
            }
        }
    }
    color = c;
}
void Board::printBoard(Board* other) {
    //printing first row
    if(color == "Black"){
        for(int i=12; i>0; i--){
            cout << setw(3) << i;
            if(i == 7){
                cout << setw(3) << " ";
            }
        }
    }
    else{ //white
        for(int i=13; i<25; i++){
            cout << setw(3) << i;
            if(i == 18){
                cout << setw(3) << " ";
            }
        }
    }
    cout << endl;
    //north border
    for(int col=0; col<41; col++) {
        if ((col == 0) || (col == 19) || (col == 21) || (col == 40)) {  //printing the borders of board with +
            cout << "+";
        } else {
            cout << "-";//completing the borders with -
        }
    }
    cout << endl;
    int iteration = 0; //indicator of how many rows have been printed
    int max = 5; //defult minimum of rows in the board can be bigger but not lower
    //figuring the rows size of the upper part of the board
    int cw = 13, cb = 12;
    for(int i=0; i<12; i++, cw++, cb--){
        if(color == "White"){
            if(board[cw] > max){
                max = board[cw];
            }
            else{
                if(other->board[cb] > max){
                    max = other->board[cb];
                }
            }
        }
        else{//black
            if(board[cb] > max){
                max = board[cb];
            }
            else{
                if(other->board[cw] > max){
                    max = other->board[cw];
                }
            }
        }
    }
    //printing the upper part of the board
    while( iteration < max){
        cw = 13;
        cb = 12;
        for(int col=0; col<41; col++) {
            if ((col == 0) || (col == 19) || (col == 21) || (col == 40)) {  //printing the borders of board with +
                cout << "+";
            }
            else{
                if(col == 20){
                    if(color == "White"){
                        if((board[25] != 0) && !((board[25] - iteration) <= 0)) {
                            cout << "W";
                        }
                        else{
                            cout << " ";
                        }
                    }
                    else{//black
                        if((other->board[25] != 0) && !((other->board[25] - iteration) <= 0)) {
                            cout << "W";
                        }
                        else{
                            cout << " ";

                        }
                    }
                }
                else {
                    if ((col % 3 == 0) || (col % 3 == 1)) {
                        cout << " ";
                    } else {
                        if (color == "White") {
                            if ((board[cw] == 0) && (other->board[cb] == 0)) {
                                cout << "|";
                            } else {
                                if (board[cw] != 0) {
                                    if ((board[cw] - iteration) <= 0) {
                                        cout << "|";
                                    } else {
                                        cout << "W";
                                    }
                                } else {
                                    if ((other->board[cb] - iteration) <= 0) {
                                        cout << "|";
                                    } else {
                                        cout << "B";
                                    }
                                }
                            }
                        } else {
                            if ((board[cb] == 0) && (other->board[cw] == 0)) {
                                cout << "|";
                            } else {
                                if (board[cb] != 0) {
                                    if ((board[cb] - iteration) <= 0) {
                                        cout << "|";
                                    } else {
                                        cout << "B";
                                    }
                                } else {
                                    if ((other->board[cw] - iteration) <= 0) {
                                        cout << "|";
                                    } else {
                                        cout << "W";
                                    }
                                }
                            }
                        }
                        cw++;
                        cb--;
                    }
                }
            }
        }
        iteration++;
        cout << endl;
    }
    iteration = 0; //indicator of how many rows have been printed
    //printing the middle row of the board
    for(int col=0; col<41; col++) {
        if ((col == 0) || (col == 19) || (col == 21) || (col == 40)) {  //printing the borders of board with +
            cout << "+";
        }
        else {
            if (col == 20) {
                cout << " ";
            } else {
                cout << " ";
            }
        }
    }
    cout << endl;
    //figuring the rows size of the lower part of the board
    cw = 12, cb = 13, max = 5;
    for(int i=0; i<12; i++, cw--, cb++){
        if(color == "White"){
            if(board[cw] > max){
                max = board[cw];
            }
            else{
                if(other->board[cb] > max){
                    max = other->board[cb];
                }
            }
        }
        else{//black
            if(board[cb] > max){
                max = board[cb];
            }
            else{
                if(other->board[cw] > max){
                    max = other->board[cw];
                }
            }
        }
    }
    //printing the lower part of the board
    while( iteration < max){
        cw = 12;
        cb = 13;
        for(int col=0; col<41; col++) {
            if ((col == 0) || (col == 19) || (col == 21) || (col == 40)) {  //printing the borders of board with +
                cout << "+";
            }
            else{
                if(col == 20){
                    if(color == "White"){
                        if((other->board[25] != 0) && !(max - other->board[25] - iteration)){
                            cout << "B";
                        }
                        else{
                            cout << " ";
                        }
                    }
                    else{//black
                        if((board[25] != 0) && !(max - board[25] - iteration)) {
                            cout << "B";
                        }
                        else{
                            cout << " ";

                        }
                    }
                }
                else {
                    if ((col % 3 == 0) || (col % 3 == 1)) {
                        cout << " ";
                    }
                    else{
                        if(color == "White"){
                            if((board[cw] == 0) && (other->board[cb] == 0)){
                                cout << "|";
                            }
                            else{
                                if(board[cw] != 0){
                                    if((max - board[cw] - iteration) > 0){
                                        cout << "|";
                                    }
                                    else{
                                        cout << "W";
                                    }
                                }
                                else{
                                    if((max - other->board[cb] - iteration) > 0){
                                        cout << "|";
                                    }
                                    else{
                                        cout << "B";
                                    }
                                }
                            }
                        }
                        else {
                            if ((board[cb] == 0) && (other->board[cw] == 0)) {
                                cout << "|";
                            }
                            else {
                                if (board[cb] != 0) {
                                    if ((max - board[cb] - iteration) > 0) {
                                        cout << "|";
                                    } else {
                                        cout << "B";
                                    }
                                } else {
                                    if ((max - other->board[cw] - iteration) > 0) {
                                        cout << "|";
                                    } else {
                                        cout << "W";
                                    }
                                }
                            }
                        }
                        cw--;
                        cb++;
                    }
                }
            }
        }
        iteration++;
        cout << endl;
    }
    //south border
    for(int col=0; col<41; col++) {
       if ((col == 0) || (col == 19) || (col == 21) || (col == 40)) {  //printing the borders of board with +
           cout << "+";
       } else {
           cout << "-";//completing the borders with -
       }
    }
    cout << endl;
    //printing last row
    if(color == "White"){
        for(int i=12; i>0; i--){
            cout << setw(3) << i;
            if(i == 7){
                cout << setw(3) << " ";
            }
        }
    }
    else{ //black
        for(int i=13; i<25; i++){
            cout << setw(3) << i;
            if(i == 18){
                cout << setw(3) << " ";
            }
        }
    }
    cout << endl;


}

