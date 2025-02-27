// ===============================================================
// Can't Stop Board Game          File: unitTest.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "tools.hpp"
#include "Board.hpp"
#include "Game.hpp"
//-----------------------------------------------------------------
void testGame(ostream& os) {
	os << "Starting Board class unit test...\n";
	Game game;  // Game creates the player internally
	Board board;
	
	// Use the player from the Game instance directly
	Player* player1 = game.getPlayer();  // getPlayer() returns a reference to the player
	
	// Test 1: Board initialization and verify the lengths of all 11 Column objects
	os << "\nTest 1: Board initialization" << endl;
	os << board << endl;
	os << "//--------------" << endl;
	
	// Test 2: Start Turn
	os << "\nTest 2: Start Turn" << endl;
	os << game << endl;
	board.startTurn(player1);
	os << board << endl;
	os << "//--------------" << endl;
	
	// Test 3. Move Towers
	os << "\nTest 3: Move Towers.\nMoving in Column 4...\n"; //	Try moving in Column 4
	if (board.move(4)) {
		os << "Tower placed in Column 4!\n";
	} else {
		os << "Could not place tower in Column 4.\n";
	}
	os << "\nMoving in Column 8...\n"; // Try moving in Column 8
	if (board.move(8)) {
		os << "Tower placed in Column 8!\n";
	} else {
		os << "Could not place tower in Column 8.\n";
	}
	os << "\nMoving in column 10...\n"; // Try moving in column 10
	if (board.move(10)) {
		os << "Tower placed in column 10!\n";
	} else {
		os << "Could not place tower in column 10.\n";
	}
	os << board;
	os << "\nTest 3.2: Move the tower that is already in Column 8" << endl;
	for (int k = 0; k < 9; k++){
		board.move(8);
	}
	os << board;
	
	os << "\nTest 3.3: Try moving the tower in a pending and captured column" << endl;
	if (board.move(8)) {
		os << "Tower placed in Column 8!\n";
	} else {
		os << "Could not move tower in Column 8.\n";
	}
	os << board;
	
	os << "\nTest 3.4: Try to move in a new column when all 3 towers are already placed." << endl;
	if (board.move(5)) {
		os << "Tower placed in Column 5!\n";
	} else {
		os << "Could not move tower in Column 5.\n";
	}
	os << "//--------------" << endl;
	// Test 4: Stop turn
	os << "\nTest 4: Stopping turn...\n";
	board.stop();
	os << board;
	os << "//--------------" << endl;
	
	// Test 5: Bust scenario;
	// Test 5.1: Call `bust()` when the player has active towers.
	os << "\nTest 5: Call `bust()` when the player has active towers." << endl;
	os << "Move player in column 10" << endl;
	os << board;
	// move player in column 4
	board.move(4);
	board.move(4);
	board.move(4);
	os << board;
	os << "Player goes bust! So, the progress is lost." << endl;
	board.bust(); // all progress should be lost
	os << board; // no change
	os << "Unit test completed." << endl;
}
