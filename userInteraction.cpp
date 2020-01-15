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

	std::string selection;
	std::cin >> selection;
	if (!std::cin.good() || (selection != "0" && selection != "1" && selection != "2"))
	{
		std::cin.clear();
		std::cin.ignore(INT8_MAX, '\n');
		std::cout << UNAVAILABLE_OPTION_CHOOSED << std::endl;
		return showFirstSelectMenu();
	}
	else {
		return std::stoi(selection);
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
	std::string numberOfHumanOpponents_s;

	std::cout
		<< std::endl
		<< INSTRUCTION_NUMBER_OF_HUMAN_OPPONENTS;
	std::cin >> numberOfHumanOpponents_s;

	if (validateInputNumberOfOpponents(numberOfHumanOpponents_s)) {
		numberOfHumanOpponents = std::stoi(numberOfHumanOpponents_s);
	}
	else {
		requestNumberOfHumanOpponents(numberOfHumanOpponents);
	}
}

void requestNumberOfPcOpponents(int& numberOfPcOpponents)
{
	std::string numberOfPcOpponents_s;
	std::cout
		<< std::endl
		<< INSTRUCTION_NUMBER_OF_PC_OPPONENTS;
	std::cin >> numberOfPcOpponents_s;

	if (validateInputNumberOfOpponents(numberOfPcOpponents_s)) {
		numberOfPcOpponents = std::stoi(numberOfPcOpponents_s);
	}
	else {
		requestNumberOfPcOpponents(numberOfPcOpponents);
	}
}

bool validateInputNumberOfOpponents(std::string& numberOfOpponents)
{
	if (!std::cin.good() || (numberOfOpponents != "0" && numberOfOpponents != "1" && numberOfOpponents != "2" && numberOfOpponents != "3"))
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

void showCommandSet() {
	std::cout
		<< std::endl
		<< SEPARATION_LINE
		<< std::endl
		<< "BEFEHLSSATZ" << std::endl
		<< std::endl
		<< std::endl
		<< "SYNTAX: <IndexSpielstein> > <EinfuegenVorSpielsteinMitDiesemIndex>" << std::endl
		<< "Auswahl Spielfeld: " << std::endl
		<< "Bsp.:   A  B  C  D" << std::endl
		<< "    0   4  5  6  3" << std::endl
		<< "    1   9  9  9   " << std::endl
		<< "Index Spielfeld: <Zeile><Spalte> Bsp.: 0C (Wert: 6)" << std::endl
		<< std::endl
		<< "Auswahl Spielbrett: " << std::endl
		<< "Bsp.:   A  B  C  D" << std::endl
		<< "        7  9  5  3" << std::endl
		<< "Index Spielfeld: <Spate> Bsp.: C (Wert: 5)" << std::endl
		<< std::endl
		<< std::endl
		<< "VERWENDUNGSZWECK:" << std::endl
		<< "Es gibt eine zentrale Befehlssyntax, mit welcher sich ein Spielstein: " << std::endl
		<< std::endl
		<< "+ auf dem Spielbrett" << std::endl
		<< "Bsp.: D > B fuehrt zu 7 3 9 5 (Spielbrett)" << std::endl
		<< std::endl
		<< "+ zwischen Spielbrett und Spielfeld" << std::endl
		<< "Bsp.: B > 1D fuehrt zu 7 5 3 (Spielbrett)" << std::endl
		<< "9 9 9 9 (Spielfeld Zeile mit Index 1)" << std::endl
		<< std::endl
		<< "+ zwischen Spielfeld und Spielbrett" << std::endl
		<< "Bsp.: 0B > B fuehrt zu 7 5 9 5 3 (Spielbrett)" << std::endl
		<< "4 6 3 (Spielfeld Zeile mit Index 0)" << std::endl
		<< std::endl
		<< "+ auf dem Spielfeld" << std::endl
		<< "Bsp.: 1A > 0C fuehrt zu 4 5 9 6 3 (Spielfeld Zeile mit Index 0)" << std::endl
		<< "9 9 (Spielfeld Zeile mit Index 1)" << std::endl
		<< std::endl
		<< "verschieben laesst" << std::endl
		<< std::endl

		<< SEPARATION_LINE
		<< std::endl;
}