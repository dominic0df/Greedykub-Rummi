#include "userInputProcessing.h"
#include "main.h"
#include "userInteraction.h"

void firstUserInteraction(std::vector<scoreEntry>& score) {

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

void setPlayerInformation(std::vector<scoreEntry>& score) {
	//TO DO: Schwierigkeitsgrad der Gegner auswählen
	//(TO DO: Namen für PC-Gegner festlegen)

	std::string nameOfHumanPlayer = requestNameOfPlayer();

	int numberOfOpponents = requestNumberOfOpponents();

	scoreEntry humanPlayer;
	humanPlayer.playerName = nameOfHumanPlayer;
	humanPlayer.point = 0;
	score.push_back(humanPlayer);

	for (int player = 0; player < numberOfOpponents; player++)
	{
		std::string playerName = "Player " + std::to_string(player + 1);
		scoreEntry nextPlayer;
		nextPlayer.playerName = playerName;
		nextPlayer.point = 0;
		score.push_back(nextPlayer);
	}

	//std::cout << nameOfHumanPlayer << std::endl;
}