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
		<< std::endl
		<< INSTRUCTION_ENTER_OPTION;

	int selection;
	std::cin >> selection;
	if (!std::cin.good() || (selection != 0 && selection != 1 && selection != 2))
	{
		std::cin.clear();
		std::cin.ignore(INT8_MAX, '\n');
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
		<< ENTER_NAME;

	char nameOfHumanPlayer_c[50];
	std::cin.getline(nameOfHumanPlayer_c, sizeof(nameOfHumanPlayer_c));
	std::string nameOfHumanPlayer(nameOfHumanPlayer_c);

	return nameOfHumanPlayer;
}


void requestNumberOfOpponents(int& numberOfHumanOpponents, int& numberOfPcOpponents) {

	requestNumberOfHumanOpponents(numberOfHumanOpponents);
	requestNumberOfPcOpponents(numberOfPcOpponents);

	int totalNumberOfOpponents = numberOfHumanOpponents + numberOfPcOpponents;
	if (totalNumberOfOpponents < 1) {
		std::cout << std::endl << NOT_ENOUGH_OPPONENTS_CHOOSED << std::endl << std::endl;
		requestNumberOfOpponents(numberOfHumanOpponents, numberOfPcOpponents);
	}
	else if (totalNumberOfOpponents > 3) {
		std::cout << std::endl << TOO_MANY_OPPONENTS_CHOOSED << std::endl << std::endl;
		requestNumberOfOpponents(numberOfHumanOpponents, numberOfPcOpponents);
	}
}

void requestNumberOfHumanOpponents(int& numberOfHumanOpponents)
{
	std::cout
		<< std::endl
		<< INSTRUCTION_NUMBER_OF_HUMAN_OPPONENTS;
	std::cin >> numberOfHumanOpponents;

	if (validateInputNumberOfOpponents(numberOfHumanOpponents) == false) {
		requestNumberOfHumanOpponents(numberOfHumanOpponents);
	}
}

void requestNumberOfPcOpponents(int& numberOfPcOpponents)
{
	std::cout
		<< std::endl
		<< INSTRUCTION_NUMBER_OF_PC_OPPONENTS;
	std::cin >> numberOfPcOpponents;

	if (validateInputNumberOfOpponents(numberOfPcOpponents) == false) {
		requestNumberOfPcOpponents(numberOfPcOpponents);
	}
}

bool validateInputNumberOfOpponents(int& numberOfOpponents)
{
	if (!std::cin.good() || (numberOfOpponents != 0 && numberOfOpponents != 1 && numberOfOpponents != 2 && numberOfOpponents != 3))
	{
		std::cin.clear();
		std::cin.ignore(INT8_MAX, '\n');
		std::cout << UNAVAILABLE_NUMBER_CHOOSED << std::endl;
		return false;
	}
	else {
		return true;
	}
}

std::string showSelectMenuMove() {

	std::cout
		<< std::endl
		<< AVAILABLE_OPTIONS << std::endl
		<< QUIT_GAME << std::endl
		<< SHOW_MANUAL << std::endl
		<< SHOW_COMMANDS << std::endl
		<< std::endl
		<< DRAW_TOKEN << std::endl
		<< CONTINUE << std::endl
		<< REPAIR_PLAYGROUND << std::endl
		<< MOVE_TOKEN << std::endl
		<< std::endl
		<< INSTRUCTION_ENTER_OPTION;

	char selection_c[50];
	std::cin.getline(selection_c, sizeof(selection_c));
	std::string selection(selection_c);
	return selection;
}