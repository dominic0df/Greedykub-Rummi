#include "main.h"

int main() {
	Token::Color color = Token::Color::BLUE;
	Token::Location location = Token::Location::Storage;
	Token* myToken = new Token(color, 1, location, "2");
	//Token testToken(color, 1, location, "2");
	
	//std::cout << "Test";
	//int value = myToken->getValue;
	std::cout << "Farbe: " << myToken->color << std::endl;
	std::cout << "Wert: " << myToken->value << std::endl;
	std::cout << "Ort: " << myToken->location << std::endl;
	std::cout << "Position: " << myToken->position << std::endl;
	/*
	std::cout << "Test: " << "Farbe: " << myToken->getColor << std::endl;
	std::cout << "Test: " << "Wert: " << myToken->getValue << std::endl;
	std::cout << "Test: " << "Ort: " << myToken->getLocation << std::endl;
	std::cout << "Test: " << "Position: " << myToken->getPosition << std::endl;
	*/

}

Token::Token(Token::Color newColor, int newValue, Token::Location currentLocation, std::string currentPosition)
{
	color = newColor;
	value = newValue;
	location = currentLocation;
	position = currentPosition;
}