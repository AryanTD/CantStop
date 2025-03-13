// ===============================================================
// Can't Stop Board Game          File: Column.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "Column.hpp"
//-----------------------------------------------------------------
const int Column::colLen[13] = {0,0,3,5,7,9,11,13,11,9,7,5,3};

Column::Column (int colNum) : colNum(colNum), state(ECstate::Available){
    if (colNum < 2 || colNum > 12){
        fatal("Column number must be between 2 and 12");
    }
}

//-----------------------------------------------------------------
// Prints the column state and contents
ostream& Column::print(ostream& os) const {
    os << colNum << " " << stateNames[(int)(state)];
    for (int i = 1; i <= colLen[colNum]; i++) {
        os << "  ";
        for (int j = 0; j < 5; j++) {
            if (squares[j] == i) {
				os << markerColor[j];
            }
            else os << "-";
        }
        os << "  ";
    }
    os << endl;
	return os;
}

//-----------------------------------------------------------------
// Start a tower for a player
bool Column::startTower(Player* player) {
    if (state == ECstate::Captured) return false;
    ECcolor color = player->getColor();
	
    int index = (int)(color);
    squares[0] = (squares[index] == 0) ? 1 : squares[index] + 1;
	
	if (squares[index] > 0){
		squares[0]++;
	}else{
		squares[index] = 0;
	}
    
    if (squares[index] >= colLen[colNum]) {
        state = ECstate::Pending;
    }
    return true;
}

//-----------------------------------------------------------------
// Moves tower forward
bool Column::move() {
	if (state == ECstate::Captured) return false;
	
	if (squares[0] > 0 && squares[0] < colLen[colNum]) {
		squares[0] += 1;  // Move only the tower
	}
	if (squares[0] == colLen[colNum]) {
		state = ECstate::Pending;
	}
	return true;
}

//-----------------------------------------------------------------
// Stop and replace tower with tile
void Column::stop(Player* player) {
    int index = (int)(player->getColor());
    if (squares[0] == 0) return;  // No tower to replace
    squares[index] = squares[0]; // Convert tower into tile of player's color
    squares[0] = 0;  // Remove the tower
    
    if (squares[index] > 0) {
        if (state == ECstate::Pending) {
            state = ECstate::Captured;
            player->wonColumn(colNum);
        }
    }
}

//-----------------------------------------------------------------
// Reset squares on bust
void Column::bust() {
	// Remove the player's tower for this turn
	squares[0] = 0;
	// If the column is not captured
	if (state == ECstate::Pending) {
		state = ECstate::Available;
	}
}
