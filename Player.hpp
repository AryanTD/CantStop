// ================================================================
// Name: Can't Stop Board Game        Jan, 2025
// Author:  Ashish Khadka and Aryan Tandon      File: Player.hpp
// ================================================================
#pragma once
#include "tools.hpp"
#include "enums.hpp"
// -----------------------------------------------------------------
class Player{
private:
    string name;
    ECcolor color;
    int score;
    int scoreboard[3];
    static bool takenColors[5]; // Track if colors are used (Index: 0=White, 1=Orange, 2=Blue, 3=Yellow, 4=Green
    static vector<string> takenNames; // Track used player names
    static string toLowerCase(const string& str); // Helper function to convert string to lowercase
    
public:
    Player(const string& playerName, ECcolor playerColor);
	~Player() = default;
    
//    Accessor functions
	ECcolor getColor() const { return color; } // Get the tile color of the player.
	int getScore() const { return score; } // Get the score of the player.
    
//  stores the number of captured columns
    bool wonColumn(int colNum);
    
//  functions to handle name and color chosen by players
    static bool isColorTaken (ECcolor playerColor);
    static bool isNameTaken (const string& playerName);
    static void resetTakenData();
    
//  Print function
    ostream& print(ostream& os) const;
};

//  Overload the output operator
inline ostream& operator<<(ostream& os, const Player& player) {
    return player.print(os);
}
