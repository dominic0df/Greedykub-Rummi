#include "userInteraction.h"
#include "userInputProcessing.h"

int showFirstSelectMenu()
{
	std::cout
		<< std::endl
		<< AVAILABLE_OPTIONS << std::endl
		<< QUIT_GAME << std::endl
		<< SHOW_MANUAL << std::endl
		<< START_GAME << std::endl
		<< std::endl;

	int selection;
	std::cin >> selection;
	if (!std::cin.good() || (selection != 0 && selection != 1 && selection != 2))
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << UNAVAILABLE_OPTION_CHOOSED << std::endl;
		return showFirstSelectMenu();
	}
	else {
		return selection;
	}
}

std::string requestNameOfPlayer() {
	std::cout
		<< std::endl
		<< INSTRUCTION_ENTER_NAME;

	// NICE TO HAVE: Nachnamen erlauben

	std::string nameOfHumanPlayer;
	std::cin >> nameOfHumanPlayer;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	return nameOfHumanPlayer;
}

int requestNumberOfOpponents() {
	std::cout
		<< std::endl
		<< INSTRUCTION_NUMBER_OF_OPPONENTS;

	int numberOfOpponents;
	std::cin >> numberOfOpponents;

	if (!std::cin.good() || (numberOfOpponents != 1 && numberOfOpponents != 2 && numberOfOpponents != 3))
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << UNAVAILABLE_OPTION_CHOOSED << std::endl;
		return requestNumberOfOpponents();
	}
	else {
		return numberOfOpponents;
	}
}