#include "userInputProcessing.h"
#include "main.h"
#include "userInteraction.h"
#include "shared.h"

void firstUserInteraction() {

	int selection = showFirstSelectMenu();

	switch (selection)
	{
	case 0:
		//std::cout << "0 QUIT";
		break;
	case 1:
		showGameManual();
		//break;
	case 2:
		startGame();
		//std::cout << "2 START GAME";
		break;
	default:
		std::cout << ERROR_OCCURRED << std::endl;
		break;
	}
}

void setPlayerInformation(std::vector<playerAdministration>& player) {
	//TO DO: Schwierigkeitsgrad der Gegner auswählen
	//(TO DO: Namen für PC-Gegner festlegen)

	std::cin.clear();
	std::cin.ignore(INT8_MAX, '\n');
	std::cout << std::endl << "Gebe folgend deinen Namen an!" << std::endl;
	addPlayer(player, Token::Usage::HUMAN_Player_1, requestNameOfPlayer());

	std::cout
		<< std::endl
		<< "Rummikub wird mit 2-4 Gegenspielern gespielt"
		<< std::endl
		<< "-> Im folgenden kannst du die Anzahl menschlicher als auch computerbasierter Gegner waehlen:"
		<< std::endl;

	int numberOfHumanOpponents;
	int numberOfPcOpponents;

	requestNumberOfOpponents(numberOfHumanOpponents, numberOfPcOpponents);

	if (numberOfHumanOpponents > 0) {
		std::cout << std::endl << "Wie heissen die menschlichen Gegenspieler?:";
	}

	std::cin.clear();
	std::cin.ignore(INT8_MAX, '\n');
	for (int humanPlayer = 1; humanPlayer <= numberOfHumanOpponents; humanPlayer++)
	{
		std::cout << std::endl << "Gebe folgend den Namen vom meschlichen Gegenspieler " << humanPlayer << " an!" << std::endl;
		addPlayer(player, (Token::Usage) humanPlayer, requestNameOfPlayer());
	}

	for (int pcPlayer = 1; pcPlayer <= numberOfPcOpponents; pcPlayer++)
	{
		std::string nameOfPcPlayer = "PC Gegner " + std::to_string(pcPlayer);
		addPlayer(player, (Token::Usage) (pcPlayer + 3), nameOfPcPlayer);
	}
}

void addPlayer(std::vector<playerAdministration>& playerMemory, Token::Usage player, std::string nameOfHumanPlayer) {
	playerAdministration nextPlayer;
	nextPlayer.player = player;
	nextPlayer.constumizedName = nameOfHumanPlayer;
	nextPlayer.tokensMovedToPlayground = false;
	nextPlayer.points = 0;

	playerMemory.push_back(nextPlayer);
}

void makeMovePlayer(Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer,
	bool& gameOn, bool& roundOn, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, bool& tokenDrawn, std::string& name) {

	printMemoryStructure(currentPlayground);
	// TO DO: nameOfHumanPlayer
	showTokensOfPlayer(tokensOfPlayer, name);

	std::string selection = showSelectMenuMove();
	std::cout << SEPARATION_LINE
		<< std::endl
		<< std::endl;

	//std::cout << "<" << selection << ">" << std::endl;
	trim(selection);
	//std::cout << "<" << selection << ">" << std::endl;

	if (isNumber(selection)) {
		int selectionNumber = std::stoi(selection);

		switch (selectionNumber)
		{
		case 0:
			roundOn = false;
			gameOn = false;
			break;
		case 1:
			showGameManual();
			break;
		case 2:
			//showCommandSet();
			showCommandSet();
			break;
		case 3:
			if (!drawTokenRandomlyFromStock(tokens, joker1, joker2, player, 1)) {
				gameOn = false;
			}
			roundOn = false;
			tokenDrawn = true;
			break;
		case 4:
			//nextPlayer()
			roundOn = false;
			tokenDrawn = false;
			std::cout << "Spielrunde beendet!";
			break;
		default:
			std::cout << UNAVAILABLE_OPTION_CHOOSED << std::endl;
			makeMovePlayer(player, currentPlayground, tokensOfPlayer, gameOn, roundOn, tokens, joker1, joker2, tokenDrawn, name);
			break;
		}
	}
	else {
		//checkRegex
		processCommandInput(selection, player, currentPlayground, tokensOfPlayer, tokens, joker1, joker2);
		//std::cout << "Check Regex";
	}
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}