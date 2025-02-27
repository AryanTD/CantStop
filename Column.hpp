// ================================================================
// Name: Can't Stop Board Game        Feb, 2025
// Author:  Ashish Khadka and Aryan Tandon      File: Column.hpp
// ================================================================
#pragma once
#include "tools.hpp"
#include "Player.hpp"
#include "enums.hpp"
// -----------------------------------------------------------------
class Column{
private:
    static const int columnLengths[13];
    const int columnNumber;
    ECstate state;
    int squares[5] = {0};
    
public:
    Column(int colNum);
    ~Column() = default;
	ECstate getState() const { return state; } // Returns the current state of the column
    bool startTower(Player* player); // player places tower in a new column
	bool move(); // moves the player
    void stop(Player* player); // player stops his turn
    void bust(); // player's progress with the tower is lost
	ostream& print(ostream& os) const;
};
//  Overload the output operator
inline ostream& operator<<(ostream& os, const Column& col) {
	return col.print(os);
}
