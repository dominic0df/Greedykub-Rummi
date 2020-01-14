#pragma once
#include <string>
#include <regex>
#ifndef SHARED_H
#define SHARED_H


const std::string ERROR_OCCURRED = "Ein Fehler im Programm ist aufgetreten!";
const std::string WELCOME = "Herzlich Willkommen bei Rummikub!";
const std::string MESSAGE_PLAYER_TO_START = "Folgender Spieler darf das Spiel beginnen: ";
const std::string BOARD_FILLED = "Dein Brett ist voll -> du kannst keine neuen Spielsteine mehr aufnehmen. Lege Spielsteine auf dem Spielfeld ab!";

const int VALUE_OF_JOKER = 30;
const int TOTAL_AMOUNT_OF_TOKEN = 106;
const int AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING = 14;

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
	int positionPlayerBoard;
	int column;		//memory -> vector "tokens" which includes all Tokens
	int row;		//memory -> vector "tokens" which includes all Tokens
	int columnPlayground;
	int rowPlayground;

public:

	std::string getTerminalColor();

	Token::Color& getColor();

	int& getValue();

	Token::Usage& getUsage();

	int& getPositionPlayerBoard();

	int& getColumn();

	int& getRow();

	int& getColumnPlayground();

	int& getRowPlayground();

	void setColor(Token::Color newColor);

	void setValue(int newValue);

	void setUsage(Token::Usage newUsage);

	void setPositionPlayerBoard(int newPosition);

	void setColumn(int column);

	void setRow(int row);

	void setColumnPlayground(int newColumnPlayground);

	void setRowPlayground(int newRowPlayground);

	Token(Token::Color newColor, int newValue, Token::Usage currentLocation, int currentPosition,
		int memoryColumn, int memoryRow, int currentColumnPlayground, int currentRowPlayground);

};

struct scoreEntry {
	Token::Usage player;
	int point;
};

void ltrim(std::string& s);

void rtrim(std::string& s);

void trim(std::string& s);

char indexToAscii(int index);

int asciiToIndex(char asciiValue);

#endif
