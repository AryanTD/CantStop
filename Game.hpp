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
	Dice* dice;
	Player* player;
	Board board;
public:
	Game();
	~Game() { delete dice; delete player;}
	static string getName();
	static ECcolor getColor();
	void getPlayers();
	void oneTurn(Player* pp);
	void moveTower();
	pair<int, int> selectPairs();
	void play();
	ostream& print (ostream& os);
};
//  Overload the output operator
inline ostream& operator<<(ostream& os, Game& game) {
	return game.print(os);
}
