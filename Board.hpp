// ================================================================
// Name: Can't Stop Board Game        Feb, 2025
// Author:  Ashish Khadka and Aryan Tandon      File: Board.hpp
// ================================================================
#pragma once
#include "tools.hpp"
#include "Column.hpp"
// -----------------------------------------------------------------
class Board {
private:
	int towers; // active towers (max 3)
	int towerCols[3]; // column with towers
	Column* backBone[13];
	Player* currPlayer;
public:
	Board();
	~Board();
	void startTurn(Player* player);
	bool move (int column);
	void stop();
	void bust();
	ostream& print (ostream& os);
};
//  Overload the output operator
inline ostream& operator<<(ostream& os, Board& b) {
	return b.print(os);
}
