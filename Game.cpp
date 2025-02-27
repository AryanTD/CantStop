// ===============================================================
// Can't Stop Board Game          File: Game.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "Game.hpp"
//-----------------------------------------------------------------
// Constructor initializes dice, players, and columns
Game::Game()
	: dice(new Dice(4)),  // Initializes 4 dice
	  player(getNewPlayer()){}

//-----------------------------------------------------------------
// Gets a new player's name and color
Player Game::getNewPlayer() {
	string name;
	ECcolor color;
	name = getName();
	color = getColor();
	return Player(name, color);
}

//-----------------------------------------------------------------
// Function to get a valid player name (no spaces)
string Game::getName() {
	string name;
	while (true) {
		cout << "Enter player name (no spaces): ";
		cin.clear(); cin.sync(); // ignore any leftover newline from previous input
		getline(cin, name);  // Read the user name

		// Remove spaces from the name
		name.erase(remove(name.begin(), name.end(), ' '), name.end());
		
		// Check if the name is empty after removing spaces
		if (name.empty()) {
			cout << "Invalid name! The name cannot be empty or contain only spaces.\n";
			continue;
		}
		
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
	while (true) {
		cout << "Select a color (B = Blue, G = Green, Y = Yellow, O = Orange): ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
		
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
// Function to roll and print a dice
void Game::rollAndPrint (ostream& os) {
	const int* rollResults = dice->roll(); // Roll the dice
	for (int i = 0; i < 4; ++i) {
		os << rollResults[i] << " ";
	}
	os << endl;
}

//-----------------------------------------------------------------
// Print the Game elements
ostream& Game::print(ostream& os) {
	rollAndPrint(os);
	os << player << endl;
	return os;
}
