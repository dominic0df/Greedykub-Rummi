#include "shared.h"

Token::Token(Token::Color newColor, int newValue, Token::Usage currentLocation, std::string currentPosition, int memoryColumn, int memoryRow)
{
	color = newColor;
	value = newValue;
	usage = currentLocation;
	position = currentPosition;
	column = memoryColumn;
	row = memoryRow;

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

std::string& Token::getPosition()
{
	return position;
}

int& Token::getColumn() {
	return column;
}

int& Token::getRow() {
	return row;
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

void Token::setPosition(std::string newPosition)
{
	position = newPosition;
}

void Token::setColumn(int memoryColumn) {
	column = memoryColumn;
}

void Token::setRow(int memoryRow) {
	row = memoryRow;
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