// ===============================================================
// Can't Stop Board Game          File: Game.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "Game.hpp"
//-----------------------------------------------------------------
// Constructor initializes dice, players, and columns
Game::Game()
	: dice(new Dice(4)), board(), player(nullptr){
		getPlayers();
	}

//-----------------------------------------------------------------
// Gets all players
void Game::getPlayers() {
	string name;
	ECcolor color;
	name = getName();
	color = getColor();
	player = new Player(name,color);
}

//-----------------------------------------------------------------
// Function to get a valid player name (no spaces)
string Game::getName() {
	string name;
	for (;;) {
		cout << "\nEnter player name (no spaces): ";
		cin >> name;  // Read the user name

		// Check if the name is already taken
		if (Player::isNameTaken(name)) {
			cout << "The name is already taken! Please choose a different name.\n";
			continue;
		}
		break;
	}
	return name;
}

//-----------------------------------------------------------------
// Function to get a valid ECcolor input
ECcolor Game::getColor(){
	char choice;
	ECcolor color;
	
	// Display available colors
	cout << "Available colors:\n";
	if (!Player::isColorTaken(ECcolor::Blue)) cout << "B: Blue\n";
	if (!Player::isColorTaken(ECcolor::Green)) cout << "G: Green\n";
	if (!Player::isColorTaken(ECcolor::Yellow)) cout << "Y: Yellow\n";
	if (!Player::isColorTaken(ECcolor::Orange)) cout << "O: Orange\n";
	
	for (;;) {
		cout << "Select a color: ";
		cin >> choice;
		
		// Convert to uppercase to handle lowercase input
		choice = toupper(choice);
		
		// Switch statement to return the correct enum
		switch (choice) {
			case 'B': color = ECcolor::Blue; break;
			case 'G': color = ECcolor::Green; break;
			case 'Y': color = ECcolor::Yellow; break;
			case 'O': color = ECcolor::Orange; break;
			default:
				cout << "Invalid choice! Please enter B, G, Y, or O." << endl;
				continue;  // Continue the loop to ask for input again
		}
		if (Player::isColorTaken(color)) {
			cout << "Color already taken! Choose another.\n";
			continue;
		}
		break;
	}
	return color;
}

//-----------------------------------------------------------------
// Handles dice rolling and pair selection
pair<int, int> Game::selectPairs() {
	char first, second;
	const int* diceRolls = dice->roll();
	cout << "\nDice Rolled: ";
	for (int i = 0; i < 4; ++i) cout << char('A' + i) << ":" << diceRolls[i] << " ";
	cout << "\n";
	
	for (;;) {
		cout << "Choose two dice (A, B, C, or D) to form a pair (e.g., AB, BC): ";
		cin >> first >> second;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		first = toupper(first);
		second = toupper(second);
		
		// Check if input is valid
		if ((first >= 'A' && first <= 'D') && (second >= 'A'
			&& second <= 'D') && (first != second)) {
			break;
		}
		
		cout << "\nInvalid input! Enter two different dice (A, B, C, or D): ";
	}

	int pair1 = diceRolls[first - 'A'] + diceRolls[second - 'A'];
	int pair2 = 0;

	for (int i = 0; i < 4; ++i) {
		if (char('A' + i) != first && char('A' + i) != second) {
			if (pair2 == 0) {
				pair2 = diceRolls[i];
			} else {
				pair2 += diceRolls[i];
			}
		}
	}
	cout << "\nSelected Pairs: (" << pair1 << ") and (" << pair2 << ")\n";
	return {pair1, pair2};
}

//-----------------------------------------------------------------
// Handles moving in columns
void Game::moveTower() {
	pair<int, int> pairs = selectPairs();
	int pair1 = pairs.first;
	int pair2 = pairs.second;
	
	// Try moving using both pairs
	bool moveSuccess = board.move(pair1);
	moveSuccess |= board.move(pair2);

	// Display updated board
	cout << board;

	if (!moveSuccess) {
		cout << "Bust! Losing progress.\n";
		board.bust();
		return;
	}
}

//-----------------------------------------------------------------
// Runs one full turn for a player
void Game::oneTurn(Player* pp) {
	board.startTurn(pp);
	player = pp;
	bool turnActive = true;
	
	while (turnActive) {
		cout << "\nChoose an action:\n1. Roll Dice \n2. Stop Turn";
		cout << "\n3. Resign (Not Implemented)\n\nEnter choice (1,2, or 3): ";
		int choice;
		cin >> choice;
		
		// roll dice
		if (choice == 1) {
			moveTower();
		}
		// stop turn
		else if (choice == 2) {
			cout << "Player stops.\n";
			board.stop();
			cout << board;
			// Check captured columns and call Player::wonColumn()
			for (int colNum = 2; colNum <= 12; colNum++) {
				if (board.move(colNum) == false) {
					player->wonColumn(colNum);
				}
			}
			turnActive = false;
		}
		else if (choice == 3) {
			cout << "Resign is not implemented yet.\n";
		}
		else {
			cout << "Invalid choice. Try again.\n";
		}
	}
}

//-----------------------------------------------------------------
// Starts the game loop
void Game::play() {
	cout << "\nStarting game...\n";
	oneTurn(player);
}

//-----------------------------------------------------------------
// Print the Game elements
ostream& Game::print(ostream& os) {
	os << player << endl;
	return os;
}
