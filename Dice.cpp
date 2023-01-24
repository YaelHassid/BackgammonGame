#include "Dice.h"

Dice::Dice(unsigned int seed) {x = seed;}
int Dice::generate() {
    const unsigned int a = 22695477;
    const unsigned int c = 1;
    x = a*x + c;
    return (int)((((x & 0x7fffffff) >> 16)%6)+1);
}