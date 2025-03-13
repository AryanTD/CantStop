// ===============================================================
// Can't Stop Board Game          File: Player.cpp
// Author:  Ashish Khadka and Aryan Tandon
// ===============================================================
#include "Player.hpp"
//-----------------------------------------------------------------
bool Player::takenColors[5] = {true, false, false, false, false}; // used colors
vector<string> Player::takenNames = {};  // used player names

Player::Player(const string& name, ECcolor color)
               : name(name), color(color), score(0) {
    string lowerName = toLowerCase(name);
    
    // Check if name is taken before storing
    if (isNameTaken(lowerName)) {
        fatal("This player name is already taken! Choose another.");
    }

    // Check if color is taken
    int colorIndex = (int)(color);
    if (colorIndex < 1 || colorIndex >= 5 || takenColors[colorIndex]) {
        fatal("Color already taken or invalid! Choose a different color.");
    }

    // Assign values only after validation
    takenNames.push_back(lowerName);
    takenColors[colorIndex] = true;
}

//-----------------------------------------------------------------
// Check if player has won the column.
bool Player::wonColumn(int colNum){
    if (score<3){
        scoreboard[score] = colNum; // store the score in the next available column
        score += 1;
        return (score == 3);
    }
    return false;
}

//-----------------------------------------------------------------
// Check if a color is already taken
bool Player::isColorTaken(ECcolor color) {
    int colorIndex = (int)(color);
    return (colorIndex >= 1 && colorIndex < 5) ? takenColors[colorIndex] : true;
}

//-----------------------------------------------------------------
// Check if a name is already taken
bool Player::isNameTaken(const string& name) {
    string lowerName = toLowerCase(name);
    return find(takenNames.begin(), takenNames.end(), lowerName) != takenNames.end();
}

//-----------------------------------------------------------------
// Reset the taken colors (for a new game)
void Player::resetTakenData() {
    for (int i = 1; i < 5; i++) {
        takenColors[i] = false;
    }
    takenNames.clear();
}

//-----------------------------------------------------------------
// Helper function to convert string to lowercase
string Player::toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

//-----------------------------------------------------------------
// Print the player name, tile color and score.
ostream& Player::print(ostream& os) const {
	os <<"Player Name: " << name
	<<"\nColor: " <<" \t" <<colorNames[(int)(color)]
	<<"\nScore: " <<score <<endl;
	return os;
}
