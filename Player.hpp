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
    static bool takenColors[5]; // Track used colors
    static vector<string> takenNames; // Track used player names
    static string toLowerCase(const string& str); // Converts string to lowercase
    
public:
    Player(const string& playerName, ECcolor playerColor);
	~Player() = default;
    
//    Accessor functions
	ECcolor getColor() const { return color; } // Get player's tile color
	int getScore() const { return score; } // Get player's score
    
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
inline ostream& operator<<(ostream& os, const Player& p) {
    return p.print(os);
}
