#include <string>
#include <vector>
#include <iostream>

const std::string RESET_TERMINAL_COL = "\033[0m";
const std::string RED_TERMINAL_COL = "\033[31m";      /* Red */
const std::string GREEN_TERMINAL_COL = "\033[32m";      /* Green */
const std::string YELLOW_TERMINAL_COL = "\033[33m";      /* Yellow */
const std::string BLUE_TERMINAL_COL = "\033[36m";      /* Blau -> Cyan */
const std::string WHITE_TERMINAL_COL = "\033[37m";      /* White */

int main();

class Token //Spielstein
{

public:

	enum Color { BLUE, RED, GREEN, YELLOW, JOKER };
	enum Location { Player1, Player2, Player3, Player4, Playground, Storage };


	Token::Color& getColor() {
		return color;
	}

	int& getValue() {
		return value;
	}

	Token::Location& getLocation() {
		return location;
	}

	std::string& getPosition() {
		return position;
	}

	Token(Token::Color newColor, int newValue, Token::Location currentLocation, std::string currentPosition);


public:

	Token::Color color;
	int value;
	Token::Location location;
	std::string position;

};

void initialFillTokenManagementArray(Token* tokenManagement[9][13]);

void printMemoryStructure(Token* tokenManagement[9][13]);

std::string getColorToPrint(int place_in_enum);