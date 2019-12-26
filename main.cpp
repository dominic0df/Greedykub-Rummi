#include "main.h"

int main() {
	Token::Color color = Token::Color::BLUE;
	Token::Location location = Token::Location::Storage;
	Token myToken = *(new Token(color, 1, location, "2"));
	
	Token* tokenManagement[9][13];
	initialFillTokenManagementArray(tokenManagement);
	printMemoryStructure(tokenManagement);
}

void printMemoryStructure(Token* tokenManagement[9][13]) {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 13; j++)
		{
			//Token myTokenTest2 = *(tokenManagement[i][j]);
			//Token::Color colorTest = myTokenTest2.getColor();
			std::string color_for_print = getColorToPrint(tokenManagement[i][j]->color);
			std::cout << color_for_print << tokenManagement[i][j]->value << RESET_TERMINAL_COL << " ";
		}
		std::cout << std::endl;
	}
	std::cout << WHITE_TERMINAL_COL << tokenManagement[8][0]->value << RESET_TERMINAL_COL << " ";
	std::cout << WHITE_TERMINAL_COL << tokenManagement[8][1]->value << RESET_TERMINAL_COL << " ";
}

Token::Token(Token::Color newColor, int newValue, Token::Location currentLocation, std::string currentPosition)
{
	color = newColor;
	value = newValue;
	location = currentLocation;
	position = currentPosition;
}

void initialFillTokenManagementArray(Token* tokenManagement[9][13]) {

	for (size_t i = 0; i < 13; i++)
	{
		Token* token = new Token(Token::Color::BLUE, i+1, Token::Location::Storage, "");
		tokenManagement[0][i] = token;
		tokenManagement[4][i] = token;
	}

	for (size_t i = 0; i < 13; i++)
	{
		Token* token = new Token(Token::Color::RED, i + 1, Token::Location::Storage, "");
		tokenManagement[1][i] = token;
		tokenManagement[5][i] = token;
	}

	for (size_t i = 0; i < 13; i++)
	{
		Token* token = new Token(Token::Color::GREEN, i + 1, Token::Location::Storage, "");
		tokenManagement[2][i] = token;
		tokenManagement[6][i] = token;
	}

	for (size_t i = 0; i < 13; i++)
	{
		Token* token = new Token(Token::Color::YELLOW, i + 1, Token::Location::Storage, "");
		tokenManagement[3][i] = token;
		tokenManagement[7][i] = token;
	}

	Token* token = new Token(Token::Color::JOKER, 0, Token::Location::Storage, "");
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
	else if (place_in_enum == 4) {
		return WHITE_TERMINAL_COL;
	}
}