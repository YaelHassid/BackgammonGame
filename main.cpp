#include <iostream>
#include "Dice.h"
#include "Board.h"
#include "Game.h"

using namespace std;
int main() {
    Game *newgame = new Game();
    newgame->start();
}
