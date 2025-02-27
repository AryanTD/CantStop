// ================================================================
// Name: Can't Stop Board Game        Feb, 2025
// Author:  Ashish Khadka and Aryan Tandon      File: Game.hpp
// ================================================================
#pragma once
#include "tools.hpp"
#include "Dice.hpp"
#include "Player.hpp"
#include "Column.hpp"
#include "Board.hpp"
// -----------------------------------------------------------------
class Game {
private:
	Dice* dice; // Pointer to dice
	Player player;
	Board board;

public:
	Game();
	~Game() { delete dice; }
	Player getNewPlayer();
	Player* getPlayer(){ return &player; }
	static string getName();
	static ECcolor getColor();
	void rollAndPrint(ostream& os);
	ostream& print (ostream& os);
};
//  Overload the output operator
inline ostream& operator<<(ostream& os, Game& game) {
	return game.print(os);
}
