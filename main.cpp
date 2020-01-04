#include "main.h"

int main()
{
	std::unique_ptr<std::unique_ptr<std::unique_ptr<Token>>> tokenManagement;
	//Token* tokenManagement[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
	initialFillTokenManagementArray(tokenManagement);
	printMemoryStructure(tokenManagement);
}

void printMemoryStructure(Token *tokenManagement[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS])
{
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

void initialFillTokenManagementArray(Token *tokenManagement[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS])
{

	for (int color = 0; color<4; color++)
	{
		for (size_t j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			Token *token = new Token((Token::Color) color, j + 1, Token::Location::Storage, "");
			tokenManagement[0 + color][j] = token;
			tokenManagement[4 + color][j] = token;
		}
	}

	Token *token = new Token(Token::Color::JOKER, 30, Token::Location::Storage, "");
	tokenManagement[8][0] = token;
	tokenManagement[8][1] = token;
}

std::string getColorToPrint(int place_in_enum)
{
	if (place_in_enum == 0)
	{
		return BLUE_TERMINAL_COL;
	}
	else if (place_in_enum == 1)
	{
		return RED_TERMINAL_COL;
	}
	else if (place_in_enum == 2)
	{
		return GREEN_TERMINAL_COL;
	}
	else if (place_in_enum == 3)
	{
		return YELLOW_TERMINAL_COL;
	}
	else
	{
		return WHITE_TERMINAL_COL;
	}
}