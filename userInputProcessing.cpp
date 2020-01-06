#include "userInputProcessing.h"
#include "main.h"
#include "userInteraction.h"

void firstUserInteraction(std::map<std::string, int>& score) {

	int selection = showFirstSelectMenu();

	switch (selection)
	{
	case 0:
		//std::cout << "0 QUIT";
		break;
	case 1:
		//showGameManual();
		//std::cout << "1 MANUAL";
		break;
	case 2:
		startGame(score);
		//std::cout << "2 START GAME";
		break;
	default:
		std::cout << ERROR_OCCURRED << std::endl;
		break;
	}
}

void setPlayerInformation(std::map<std::string, int>& score) {
	//TO DO: Schwierigkeitsgrad der Gegner auswählen
	//(TO DO: Namen für PC-Gegner festlegen)

	std::string nameOfHumanPlayer = requestNameOfPlayer();

	int numberOfOpponents = requestNumberOfOpponents();

	score.insert(std::make_pair(nameOfHumanPlayer, 0));

	for (int player = 0; player < numberOfOpponents; player++)
	{
		std::string nextPlayer = "Player " + std::to_string(player + 1);
		score.insert(std::make_pair(nextPlayer, 0));
	}

	//std::cout << nameOfHumanPlayer << std::endl;
}