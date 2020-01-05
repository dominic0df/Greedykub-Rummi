#include <string>
#include <vector>
#include <iostream>
#include <memory>

const int NUMBER_OF_ROWS = 8;
const int NUMBER_OF_COLUMNS = 13;
const int VALUE_OF_JOKER = 30;
const std::string RESET_TERMINAL_COL = "\033[0m";

int main();

class Token //Spielstein
{

public:

	const std::string RED_TERMINAL_COL = "\033[31m";      /* Red */
	const std::string GREEN_TERMINAL_COL = "\033[32m";      /* Green */
	const std::string YELLOW_TERMINAL_COL = "\033[33m";      /* Yellow */
	const std::string BLUE_TERMINAL_COL = "\033[36m";      /* Blau -> Cyan */
	const std::string JOKER_WHITE_TERMINAL_COL = "\033[37m";      /* White */

	enum Color { BLUE, RED, GREEN, YELLOW, JOKER_WHITE };
	enum Usage { Player1, Player2, Player3, Player4, Playground, Stock };

	std::string getColor() {
		switch (color) {
		case BLUE:
			return BLUE_TERMINAL_COL;
		case RED:
			return RED_TERMINAL_COL;
		case GREEN:
			return GREEN_TERMINAL_COL;
		case YELLOW:
			return YELLOW_TERMINAL_COL;
		case JOKER_WHITE:
			return JOKER_WHITE_TERMINAL_COL;
		}
		//Fehlerfall
		return RESET_TERMINAL_COL;
	}

	int& getValue() {
		return value;
	}

	Token::Usage& getLocation() {
		return location;
	}

	std::string& getPosition() {
		return position;
	}

	Token(Token::Color newColor, int newValue, Token::Usage currentUsage, std::string currentPosition);


private:

	Token::Color color;
	int value;
	Token::Usage location;
	std::string position;

};

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void printMemoryStructure(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);