#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>

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

	enum Color { BLUE = 0, RED, GREEN, YELLOW, JOKER_WHITE };
	enum Usage { Player1 = 0, Player2, Player3, Player4, Playground, Stock };


private:

	Color color;
	int value;
	Token::Usage usage;
	std::string position;

public:

	std::string getTerminalColor();

	Token::Color& getColor();

	int& getValue();

	Token::Usage& getUsage();

	std::string& getPosition();

	void setColor(Token::Color newColor);

	void setValue(int newValue);

	void setUsage(Token::Usage newUsage);

	void setPosition(std::string newPosition);

	Token(Token::Color newColor, int newValue, Token::Usage currentUsage, std::string currentPosition);

};

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void printMemoryStructure(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void searchForGroups(std::vector<std::vector<Token>>& tokens);