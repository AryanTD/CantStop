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
	int towerCount; // number of active towers (max 3)
	int activeTowers[3]; // column numbers that have towers
	Column* backBone[13]; // array of column pointers
	Player* currentPlayer; // pointer to active player
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
inline ostream& operator<<(ostream& os, Board& board) {
	return board.print(os);
}
