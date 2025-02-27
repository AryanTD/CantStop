// ===============================================================
// Can't Stop Board Game          File: Board.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "Board.hpp"
//-----------------------------------------------------------------
// Constructor: Initializes all columns
Board::Board():towerCount(0), currentPlayer(nullptr){
//	Initialize backBone array with column objects (except 0 and 1)
	backBone[0] = nullptr;
	backBone[1] = nullptr;
	for (int m = 2; m <= 12; m++){
		backBone[m] = new Column(m);
	}
	
	// Initialize active towers as unused
	for (int k = 0; k < 3; k++){
		activeTowers[k] = 0; // 0 - no active towers in that column
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
// Starts a turn by resetting the tower counter and setting the player
void Board::startTurn(Player* player) {
	currentPlayer = player;
	towerCount = 0;

	// Reset tower tracking
	for (int m = 0; m < 3; m++) {
		activeTowers[m] = 0;
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
	
	for (int m = 0; m < towerCount; m++) {
		if (activeTowers[m] == columnNum) {
			return col->move();  // Move if tower exists
		}
	}
	
	// If player has unused towers, place one
	if (towerCount < 3) {
		if (col->startTower(currentPlayer)) {
			activeTowers[towerCount++] = columnNum;
			return true;
		}
	}
	
	return false;
}

//-----------------------------------------------------------------
// Stops the turn and replaces towers with tiles
void Board::stop() {
	for (int k = 0; k < towerCount; k++) {
		int colNum = activeTowers[k];
		backBone[colNum]->stop(currentPlayer);
	}

	// Reset tower tracking
	towerCount = 0;
}

//-----------------------------------------------------------------
// Resets columns where the player had towers (on a bust)
void Board::bust() {
	for (int n = 0; n < towerCount; n++) {
		int colNum = activeTowers[n];
		backBone[colNum]->bust();
	}
	towerCount = 0;
}

//-----------------------------------------------------------------
// Print the Board
ostream& Board::print(ostream& os) {
	os << "Current Board State \n";
	os << "Active towers: " << towerCount << endl;
	for (int i = 2; i <= 12; i++) {
		os << *backBone[i] << "\n";
	}
	return os;
}
