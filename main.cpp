//=======================================================================
// Project: Can't Stop Board Game        File: main.cpp
// Author:  Ashish Khadka and Aryan Tandon  Copyright: 2025
// ======================================================================
#include "tools.hpp"
#include "Game.hpp"
// ----------------------------------------------------------------------

int main(int argc, const char * argv[]) {
	banner();
	srand(int(time(nullptr))); // Seed the random number generator once
	Game game;
	game.play();
	bye();
}
