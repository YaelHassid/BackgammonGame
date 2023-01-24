#ifndef HW2_DICE_H
#define HW2_DICE_H

class Dice {
public:
    Dice(unsigned int seed);//constructor
    int generate(); //generator of numbers
private:
    unsigned int x;
};
#endif //HW2_DICE_H
