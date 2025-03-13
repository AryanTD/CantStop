// ================================================================
// Name: Can't Stop Board Game        Jan, 2025
// Author:  Ashish Khadka and Aryan Tandon      File: Dice.hpp
// ================================================================
#pragma once
#include "tools.hpp"
// -----------------------------------------------------------------
class Dice {
private:
    int nDice;
    int* diceValues;
    
public:
//    Constructor with default value of 1 dice
    Dice(int n = 1);
    ~Dice(){delete[] diceValues;}
    
//    returns the array of values when we roll the dice
    const int* roll();

//    Print the dice values
    ostream& print(ostream& os) const;
};

//    Overload the output operator
inline ostream& operator<<(ostream& os, Dice& d) {
    return d.print(os);
}
