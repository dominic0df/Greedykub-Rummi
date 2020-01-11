#pragma once
#include <string>
#ifndef SHARED_H
#define SHARED_H

class Token //Spielstein
{

public:

	const std::string RED_TERMINAL_COL = "\033[31m";      /* Red */
	const std::string GREEN_TERMINAL_COL = "\033[32m";      /* Green */
	const std::string YELLOW_TERMINAL_COL = "\033[33m";      /* Yellow */
	const std::string BLUE_TERMINAL_COL = "\033[36m";      /* Blau -> Cyan */
	const std::string JOKER_WHITE_TERMINAL_COL = "\033[37m";      /* White */

	enum Color { BLUE = 0, RED, GREEN, YELLOW, JOKER_WHITE };
	enum Usage { HUMAN_Player = 0, PC_Player_1, PC_Player_2, PC_Player_3, Playground, Stock };

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

struct scoreEntry {
	Token::Usage player;
	int point;
};

#endif
