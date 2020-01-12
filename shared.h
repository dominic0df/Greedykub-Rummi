#pragma once
#include <string>
#include <regex>
#ifndef SHARED_H
#define SHARED_H



const int LETTER_A_ASCII_NUMBER = 65;
const int NUMBER_OF_COLUMNS = 13;
const int NUMBER_OF_ROWS = 8;
const std::string RESET_TERMINAL_COL = "\033[0m";

class Token;
class Token //Spielstein
{

public:

	const std::string RED_TERMINAL_COL = "\033[31m";      /* Red */
	const std::string YELLOW_TERMINAL_COL = "\033[33m";      /* Yellow */
	//const std::string YELLOW_TERMINAL_COL = "\033[33m";      /* Yellow */
	const std::string PURPLE_TERMINAL_COL = "\033[35m";      /* Purple (Magenta) */
	const std::string CYAN_TERMINAL_COL = "\033[36m";      /* Cyan */
	const std::string JOKER_WHITE_TERMINAL_COL = "\033[37m";      /* White */
	const std::string WHITE_BACKGROUND_COL = "\033[47m";

	enum Color { CYAN = 0, RED, YELLOW, PURPLE, JOKER_WHITE };
	enum Usage { HUMAN_Player = 0, PC_Player_1, PC_Player_2, PC_Player_3, Playground, Stock };

private:

	Color color;
	int value;
	Token::Usage usage;
	std::string position;
	int column;
	int row;

public:

	std::string getTerminalColor();

	Token::Color& getColor();

	int& getValue();

	Token::Usage& getUsage();

	std::string& getPosition();

	int& getColumn();

	int& getRow();

	void setColor(Token::Color newColor);

	void setValue(int newValue);

	void setUsage(Token::Usage newUsage);

	void setPosition(std::string newPosition);

	void setColumn(int column);

	void setRow(int row);

	Token(Token::Color newColor, int newValue, Token::Usage currentLocation, std::string currentPosition, int memoryColumn, int memoryRow);

};

struct scoreEntry {
	Token::Usage player;
	int point;
};

void ltrim(std::string& s);

void rtrim(std::string& s);

void trim(std::string& s);

#endif
