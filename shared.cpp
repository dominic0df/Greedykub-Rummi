#include "shared.h"

Token::Token(Token::Color newColor, int newValue, Token::Usage currentLocation, int currentPosition,
	int memoryColumn, int memoryRow, int currentColumnPlayground, int currentRowPlayground)
{
	color = newColor;
	value = newValue;
	usage = currentLocation;
	positionPlayerBoard = currentPosition;
	column = memoryColumn;
	row = memoryRow;
	columnPlayground = currentColumnPlayground;
	rowPlayground = currentRowPlayground;
}

std::string Token::getTerminalColor()
{
	switch (color)
	{
	case CYAN:
		return CYAN_TERMINAL_COL;
	case RED:
		return RED_TERMINAL_COL;
	case YELLOW:
		return YELLOW_TERMINAL_COL;
	case PURPLE:
		return PURPLE_TERMINAL_COL;
	case JOKER_WHITE:
		return JOKER_WHITE_TERMINAL_COL;
	}
	//Fehlerfall
	return RESET_TERMINAL_COL;
}

Token::Color& Token::getColor()
{
	return color;
}

int& Token::getValue()
{
	return value;
}

Token::Usage& Token::getUsage()
{
	return usage;
}

int& Token::getPositionPlayerBoard()
{
	return positionPlayerBoard;
}

int& Token::getColumn() {
	return column;
}

int& Token::getRow() {
	return row;
}

int& Token::getColumnPlayground() {
	return columnPlayground;
}

int& Token::getRowPlayground() {
	return rowPlayground;
}

void Token::setColor(Token::Color newColor)
{
	color = newColor;
}

void Token::setValue(int newValue)
{
	value = newValue;
}

void Token::setUsage(Usage newUsage)
{
	usage = newUsage;
}

void Token::setPositionPlayerBoard(int newPosition)
{
	positionPlayerBoard = newPosition;
}

void Token::setColumn(int memoryColumn) {
	column = memoryColumn;
}

void Token::setRow(int memoryRow) {
	row = memoryRow;
}

void Token::setColumnPlayground(int newColumnPlayground) {
	columnPlayground = newColumnPlayground;
}

void Token::setRowPlayground(int currentRowPlayground) {
	rowPlayground = currentRowPlayground;
}


// trim from start (in place)
void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

char indexToAscii(int index) {
	index = index + LETTER_A_ASCII_NUMBER;
	if (index >= 91) {
		index = index + 6;	//skip special Characters
	}
	return index;
}

int asciiToIndex(char asciiValue) {
	int index = (int)asciiValue;
	if (index >= 97) {
		index = index - 6;
	}
	index = index - LETTER_A_ASCII_NUMBER;
	return index;
}