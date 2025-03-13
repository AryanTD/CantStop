// ===============================================================
// Can't Stop Board Game          File: Board.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "Board.hpp"
//-----------------------------------------------------------------
// Constructor: Initializes all columns
Board::Board():towers(0), currPlayer(nullptr){
	// Initialize backBone with column objects
	backBone[0] = nullptr;
	backBone[1] = nullptr;
	for (int m = 2; m <= 12; m++){
		backBone[m] = new Column(m);
	}
	
	// Initialize active towers as unused
	for (int k = 0; k < 3; k++){
		towerCols[k] = 0; // 0 - no active towers in column
	}
}

//-----------------------------------------------------------------
// Destructor: Deletes dynamically allocated columns
Board::~Board() {
	for (int n = 0; n <= 12; n++) {
		delete backBone[n];
	}
}

//-----------------------------------------------------------------
// Reset tower counter and set player for new turn
void Board::startTurn(Player* player) {
	currPlayer = player;
	towers = 0;

	// Reset tower tracking
	for (int m = 0; m < 3; m++) {
		towerCols[m] = 0;
	}
}

//-----------------------------------------------------------------
// Moves a tower in the given column
bool Board::move(int columnNum) {
	// if column is invalid
	if (columnNum < 2 || columnNum > 12){
		return false;
	}
	Column * col = backBone[columnNum];
	
	// If column is pending or captured, cannot move
	if (col->getState() == ECstate::Pending || col->getState() == ECstate::Captured) {
		return false;
	}
	// Check if player already has a tower in this column
	
	for (int m = 0; m < towers; m++) {
		if (towerCols[m] == columnNum) {
			return col->move();  // Move if tower exists
		}
	}
	
	// If player has unused towers, place one
	if (towers < 3) {
		if (col->startTower(currPlayer)) {
			towerCols[towers++] = columnNum;
			return true;
		}
	}
	
	return false;
}

//-----------------------------------------------------------------
// Stops the turn and replaces towers with tiles
void Board::stop() {
	for (int k = 0; k < towers; k++) {
		int colNum = towerCols[k];
		backBone[colNum]->stop(currPlayer);
	}

	// Reset tower tracking
	towers = 0;
}

//-----------------------------------------------------------------
// Resets columns where the player had towers (on a bust)
void Board::bust() {
	for (int n = 0; n < towers; n++) {
		int colNum = towerCols[n];
		backBone[colNum]->bust();
	}
	towers = 0;
}

//-----------------------------------------------------------------
// Print the Board
ostream& Board::print(ostream& os) {
	os << "Current Board State \n";
	os << "Active towers: " << towers << "\n\n";
	for (int i = 2; i <= 12; i++) {
		os << setw(2) << *backBone[i] << "\n";
	}
	return os;
}
