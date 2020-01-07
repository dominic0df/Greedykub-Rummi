#include "userInputProcessing.h"
#include "main.h"
#include "userInteraction.h"

void firstUserInteraction() {

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
		startGame();
		//std::cout << "2 START GAME";
		break;
	default:
		std::cout << ERROR_OCCURRED << std::endl;
		break;
	}
}

void setPlayerInformation(std::vector<scoreEntry>& score, std::string& nameOfHumanPlayer) {
	//TO DO: Schwierigkeitsgrad der Gegner auswählen
	//(TO DO: Namen für PC-Gegner festlegen)

	nameOfHumanPlayer = requestNameOfPlayer();

	int numberOfOpponents = requestNumberOfOpponents();

	for (int player = 0; player <= numberOfOpponents; player++)
	{
		scoreEntry nextPlayer;
		nextPlayer.player = (Token::Usage) player;
		nextPlayer.point = 0;
		score.push_back(nextPlayer);
	}

	//std::cout << "Length: " << score.size() << std::endl;
}