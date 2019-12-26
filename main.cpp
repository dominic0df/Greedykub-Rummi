#include "main.h"

int main() {
	Token* tokenManagement[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
	initialFillTokenManagementArray(tokenManagement);
	printMemoryStructure(tokenManagement);
}

void printMemoryStructure(Token* tokenManagement[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS]) {
	for (size_t i = 0; i < NUMBER_OF_ROWS - 1; i++)
	{
		for (size_t j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			Token value = *(tokenManagement[i][j]);
			std::string color_for_print = getColorToPrint(value.getColor());
			std::cout << color_for_print << value.getValue() << RESET_TERMINAL_COL << " ";
		}
		std::cout << std::endl;
	}
	// -> Wenn Wert 30 -> J
	Token value = *(tokenManagement[8][0]);
	std::cout << WHITE_TERMINAL_COL << "J" << RESET_TERMINAL_COL << " ";
	value = *(tokenManagement[8][1]);
	std::cout << WHITE_TERMINAL_COL << "J" << RESET_TERMINAL_COL << " ";
}

Token::Token(Token::Color newColor, int newValue, Token::Location currentLocation, std::string currentPosition)
{
	color = newColor;
	value = newValue;
	location = currentLocation;
	position = currentPosition;
}

void initialFillTokenManagementArray(Token* tokenManagement[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS]) {

	for (size_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Token* token = new Token(Token::Color::BLUE, i+1, Token::Location::Storage, "");
		tokenManagement[0][i] = token;
		tokenManagement[4][i] = token;
	}

	for (size_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Token* token = new Token(Token::Color::RED, i + 1, Token::Location::Storage, "");
		tokenManagement[1][i] = token;
		tokenManagement[5][i] = token;
	}

	for (size_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Token* token = new Token(Token::Color::GREEN, i + 1, Token::Location::Storage, "");
		tokenManagement[2][i] = token;
		tokenManagement[6][i] = token;
	}

	for (size_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Token* token = new Token(Token::Color::YELLOW, i + 1, Token::Location::Storage, "");
		tokenManagement[3][i] = token;
		tokenManagement[7][i] = token;
	}

	Token* token = new Token(Token::Color::JOKER, 30, Token::Location::Storage, "");
	tokenManagement[8][0] = token;
	tokenManagement[8][1] = token;
}

std::string getColorToPrint(int place_in_enum) {
	if (place_in_enum == 0) {
		return BLUE_TERMINAL_COL;
	}
	else if (place_in_enum == 1) {
		return RED_TERMINAL_COL;
	}
	else if (place_in_enum == 2) {
		return GREEN_TERMINAL_COL;
	}
	else if (place_in_enum == 3) {
		return YELLOW_TERMINAL_COL;
	}
	else{
		return WHITE_TERMINAL_COL;
	}
}