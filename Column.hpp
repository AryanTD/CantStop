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
    static const int colLen[13];
    const int colNum;
    ECstate state;
    int squares[5] = {0};
	
public:
    Column(int colNum);
    ~Column() = default;
	ECstate getState() const { return state; } // Returns column state
    bool startTower(Player* player); // place tower in new column
	bool move();
    void stop(Player* player);
    void bust(); // player's tower progress is lost
	ostream& print(ostream& os) const;
};
//  Overload the output operator
inline ostream& operator<<(ostream& os, const Column& c) {
	return c.print(os);
}
