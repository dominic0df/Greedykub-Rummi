#include <string>
#include <vector>
#include <iostream>

int main();

class Token //Spielstein
{

public:

	enum Color { BLUE, RED, GREEN, YELLOW, JOKER };
	enum Location { Player1, Player2, Player3, Player4, Playground, Storage };


	Token::Color& getColor() {
		return color;
	}

	int& getValue() {
		return value;
	}

	Token::Location& getLocation() {
		return location;
	}

	std::string& getPosition() {
		return position;
	}

	Token(Token::Color newColor, int newValue, Token::Location currentLocation, std::string currentPosition);


public:

	Token::Color color;
	int value;
	Token::Location location;
	std::string position;

};