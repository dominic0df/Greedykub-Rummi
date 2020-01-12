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
		checkRegex();
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

void makeMovePlayer(Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, bool& gameOn,
	std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {
	std::string selection = showSelectMenuMove();

	if (isNumber(selection)) {
		int selectionNumber = std::stoi(selection);

		switch (selectionNumber)
		{
		case 0:
			std::cout << "0 Quit Game";
			gameOn = false;
			break;
		case 1:
			//showGameManual();
			std::cout << "1 Manual";
			break;
		case 2:
			//showCommandSet();
			std::cout << "2 CommandSet";
			break;
		case 3:
			drawTokenRandomlyFromStock(tokens, joker1, joker2, player, 1);
			std::cout << "3 Draw Token";
			break;
		case 4:
			//nextPlayer()
			std::cout << "4 Quit Move";
			break;
		case 5:
			//resetPlayground()
			std::cout << "5 Reset Playground";
			break;
		default:
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << UNAVAILABLE_OPTION_CHOOSED << std::endl;
			makeMovePlayer(player, currentPlayground, gameOn, tokens, joker1, joker2);
			break;
		}
	}
	else {
		//checkRegex
		std::cout << "Check Regex";
	}
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}