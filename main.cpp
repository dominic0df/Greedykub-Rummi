#include "main.h"

int main() {
	Token::Color color = Token::Color::BLUE;
	Token::Location location = Token::Location::Storage;
	Token myToken = *(new Token(color, 1, location, "2"));
	
	Token* tokenManagement[9][13];
	initialFillTokenManagementArray(tokenManagement);
	printArray(tokenManagement);
}

void printArray(Token* tokenManagement[9][13]) {
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 13; j++)
		{
			std::cout << tokenManagement[i][j]->value << " ";
		}
		std::cout << std::endl;
	}
	std::cout << tokenManagement[8][0]->value << " ";
	std::cout << tokenManagement[8][1]->value << " ";
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
