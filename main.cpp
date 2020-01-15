#include "main.h"
#include "userInputProcessing.h"
#include "computerOpponent.h"

int main()
{
	/*std::cout << WELCOME << std::endl;
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, -1, -1, -1, -1, -1);
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, -1, -1, -1, -1, -1);
	setStartingCondition(tokens, joker1, joker2);
	printMemoryStructure(tokens, joker1, joker2);
	bool inputGeneratesCorrectOutput = searchForGroupsAndRows(tokens, result);*/
	firstUserInteraction();
}

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	int row = 0;
	for (int color = 0; color < 4; color++)
	{
		std::vector<Token> toAdd1;
		std::vector<Token> toAdd2;
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			Token::Color col = (Token::Color) color;
			//std::cout << c << std::endl;
			Token token1(col, column + 1, Token::Usage::Stock, -1, column, row, -1, -1);
			toAdd1.push_back(token1);
			Token token2(col, column + 1, Token::Usage::Stock, -1, column, row + 1, -1, -1);
			toAdd2.push_back(token2);
		}
		tokens.push_back(toAdd1);
		tokens.push_back(toAdd2);
		row = row + 2;
	}

}

void startGame() {
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, 1, Token::Usage::Stock, -1, -1, -1, -1, -1);
	Token joker2(Token::Color::JOKER_WHITE, 2, Token::Usage::Stock, -1, -1, -1, -1, -1);
	setStartingCondition(tokens, joker1, joker2);

	std::vector<playerAdministration> playerMemory;

	setPlayerInformation(playerMemory);

	int indexOfPlayerToStartGame = determineIndexPlayerToStart(playerMemory);
	std::cout << std::endl << MESSAGE_PLAYER_TO_START << playerMemory[indexOfPlayerToStartGame].constumizedName;

	dealTokens(playerMemory, tokens, joker1, joker2);

	std::vector<std::vector<Token>> currentPlaygroundBeforeManipulations;
	std::vector<std::vector<Token>> currentPlayground;
	std::vector<Token> tokensOfPlayer;
	bool gameOn = true;
	bool roundOn = true;
	bool tokenDrawn = false;
	bool pcOpponentSuccessfull = true;
	std::cin.clear();
	std::cin.ignore(INT8_MAX, '\n');
	// for loop for multiple games
	while (gameOn) {
		// getPlaygroundToDisplay -> load suitable tokens in current Playground memory structure

		for (int player = indexOfPlayerToStartGame; player <= playerMemory.size(); player++) {
			if (player == playerMemory.size()) {
				player = 0;
			}

			//currentPlaygroundBeforeManipulations = currentPlayground;
			std::copy(currentPlayground.begin(), currentPlayground.end(), back_inserter(currentPlaygroundBeforeManipulations));
			tokenDrawn = false;

			if (playerMemory.at(player).player >= Token::Usage::PC_Player_1) {
				/*std::cout
					<< std::endl
					<< SEPARATION_LINE
					<< std::endl
					<< playerMemory.at(player).constumizedName << " hat gespielt!"
					<< std::endl
					<< SEPARATION_LINE;
					*/

				currentPlayground.clear();

				std::vector<Token::Usage> usageConditions;
				usageConditions.push_back(playerMemory.at(player).player);
				if (playerMemory.at(player).tokensMovedToPlayground) {
					usageConditions.push_back(Token::Usage::Playground);
				}
				pcOpponentSuccessfull = makeAMoveComputerOpponent(tokens, currentPlayground, usageConditions, joker1, joker2);

				if (pcOpponentSuccessfull) {
					// validate "Aufstellung"
					//validateGameLineUp();
					if (currentPlayground.empty()) {
						gameOn = false;
					}
					saveCurrentPlayground(currentPlayground, tokens, joker1, joker2);
				}
				else {
					drawTokenRandomlyFromStock(tokens, joker1, joker2, playerMemory.at(player).player, 1);
					currentPlayground.clear();
					std::copy(currentPlaygroundBeforeManipulations.begin(), currentPlaygroundBeforeManipulations.end(), back_inserter(currentPlayground));
				}

				std::cout
					<< std::endl
					<< SEPARATION_LINE
					<< std::endl
					<< "PC-GEGNER:"
					<< std::endl;
				printMemoryStructure(currentPlayground);

				tokensOfPlayer = getTokensOfPlayer(tokens, joker1, joker2, playerMemory.at(player).player);
				showTokensOfPlayer(tokensOfPlayer, playerMemory.at(player).constumizedName);

				makeMovePlayer(playerMemory.at(player).player, currentPlayground, tokensOfPlayer, gameOn, roundOn, tokens, joker1, joker2, tokenDrawn);
				std::cout
					<< std::endl
					<< SEPARATION_LINE;
			}
			else {
				roundOn = true;
				tokensOfPlayer = getTokensOfPlayer(tokens, joker1, joker2, playerMemory.at(player).player);

				while (roundOn) {
					// while round on -> 30, then variable first move board -> playground
					printMemoryStructure(currentPlayground);
					// TO DO: nameOfHumanPlayer
					showTokensOfPlayer(tokensOfPlayer, playerMemory.at(player).constumizedName);

					makeMovePlayer(playerMemory.at(player).player, currentPlayground, tokensOfPlayer, gameOn, roundOn, tokens, joker1, joker2, tokenDrawn);
				}

				if (gameOn && tokenDrawn) {
					std::cout << "Karte wurde gezogen + moegliche erfolgte Spielzuege der letzten Runde verworfen!";
					currentPlayground.clear();
					std::copy(currentPlaygroundBeforeManipulations.begin(), currentPlaygroundBeforeManipulations.end(), back_inserter(currentPlayground));
				}
				else if (gameOn && !tokenDrawn) {
					//validate "Aufstellung"
					//validateGameLineUp();
					saveGameLineUp(tokens, joker1, joker2, currentPlayground, tokensOfPlayer, playerMemory.at(player).player);
				}
				else {
					break;
				}
			}
			tokensOfPlayer.clear();
			currentPlaygroundBeforeManipulations.clear();
		}
	}


	int score;
	int highestScore = -INT8_MAX;
	int winner;
	// subtract all values on board of each player
	for (int player = 0; player < playerMemory.size(); player++) {
		score = 0;
		tokensOfPlayer = getTokensOfPlayer(tokens, joker1, joker2, playerMemory.at(player).player);
		for (int column = 0; column < tokensOfPlayer.size(); column++) {
			score = score - tokensOfPlayer.at(column).getValue();
		}
		if (highestScore < score) {
			highestScore = score;
			winner = player;
		}
		playerMemory.at(player).points = score;
	}

	playerMemory.at(winner).points = (-1) * (playerMemory.at(winner).points);
	std::cout << "Spieler " << playerMemory.at(winner).constumizedName << "hat das Spiel mit " << playerMemory.at(winner).points << " Punkten gewonnen!" << std::endl;
	std::cout << "Die weiteren Ergebnisse: " << std::endl;
	for (int player = 0; player < playerMemory.size(); player++) {
		if (player != winner) {
			std::cout << playerMemory.at(player).constumizedName << ": " << playerMemory.at(player).points;
		}
	}

	/*
	std::cout << std::endl;
	for (scoreEntry& entry : score)
	{
		std::cout << entry.player << ": " << entry.point << std::endl;
	}
	*/

}

void validateGameLineUp(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, Token::Usage player,
	std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {

	std::vector<Token> tokensOfPlayerOriginal = getTokensOfPlayer(tokens, joker1, joker2, player);

}

void saveGameLineUp(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, std::vector<std::vector<Token>>& currentPlayground,
	std::vector<Token>& tokensOfPlayer, Token::Usage player) {

	saveCurrentPlayground(currentPlayground, tokens, joker1, joker2);

	saveTokensOfPlayer(tokensOfPlayer, tokens, player, joker1, joker2);
}

void saveCurrentPlayground(std::vector<std::vector<Token>>& currentPlayground, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	for (int rowPlayground = 0; rowPlayground < currentPlayground.size(); rowPlayground++)
	{
		for (int columnPlayground = 0; columnPlayground < currentPlayground[rowPlayground].size(); columnPlayground++)
		{
			if (currentPlayground[rowPlayground][columnPlayground].getRow() != -1) {
				int tokenRow = currentPlayground[rowPlayground][columnPlayground].getRow();
				int tokenColumn = currentPlayground[rowPlayground][columnPlayground].getColumn();
				tokens[tokenRow][tokenColumn].setUsage(Token::Usage::Playground);
				tokens[tokenRow][tokenColumn].setRowPlayground(rowPlayground);
				tokens[tokenRow][tokenColumn].setColumnPlayground(columnPlayground);
			}
			else {
				if (currentPlayground[rowPlayground][columnPlayground].getValue() == 1) {
					joker1.setUsage(Token::Usage::Playground);
					joker1.setRowPlayground(rowPlayground);
					joker1.setColumnPlayground(columnPlayground);
				}
				else {
					joker2.setUsage(Token::Usage::Playground);
					joker2.setRowPlayground(rowPlayground);
					joker2.setColumnPlayground(columnPlayground);
				}
			}
		}
	}
}

void saveTokensOfPlayer(std::vector<Token>& tokensOfPlayer, std::vector<std::vector<Token>>& tokens, Token::Usage player, Token& joker1, Token& joker2)
{
	for (int columnTokensOfPlayer = 0; columnTokensOfPlayer < tokensOfPlayer.size(); columnTokensOfPlayer++)
	{
		if (tokensOfPlayer[columnTokensOfPlayer].getRow() != -1) {
			int tokenRow = tokensOfPlayer[columnTokensOfPlayer].getRow();
			int tokenColumn = tokensOfPlayer[columnTokensOfPlayer].getColumn();
			tokens[tokenRow][tokenColumn].setUsage(player);
			tokens[tokenRow][tokenColumn].setPositionPlayerBoard(columnTokensOfPlayer);
		}
		else {
			if (tokensOfPlayer[columnTokensOfPlayer].getValue() == 1) {
				joker1.setUsage(player);
				joker1.setPositionPlayerBoard(columnTokensOfPlayer);
			}
			else {
				joker2.setUsage(player);
				joker2.setPositionPlayerBoard(columnTokensOfPlayer);
			}
		}
	}
}

void dealTokens(std::vector<playerAdministration>& score, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {

	for (int player = 0; player < score.size(); player++)
	{
		//std::cout << std::endl << std::endl << "Player: " << player;
		drawTokenRandomlyFromStock(tokens, joker1, joker2, (Token::Usage) player, AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING);
	}
}

bool drawTokenRandomlyFromStock(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2,
	Token::Usage player, int amountOfTokens) {
	//auto zufall=srand((unsigned int)time(NULL));
	//srand(1);
	// TODO: eventuell srand benutzen

	int positionOfToken;
	int initialPositionOfToken;
	int rowOfToken;
	int columnOfToken;

	int highestTokenPosition = 0;
	// Tokens are drawn at the Beginning, so no player has Tokens on his board -> highestTokenPosition = 0;
	if (amountOfTokens != AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING) {
		for (int row = 0; row < NUMBER_OF_ROWS; row++)
		{
			for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
			{
				if (tokens[row][column].getUsage() == (Token::Usage) player) {
					if (tokens[row][column].getPositionPlayerBoard() > highestTokenPosition) {
						highestTokenPosition = tokens[row][column].getPositionPlayerBoard();
					}
				}
			}
		}

		if (joker1.getUsage() == (Token::Usage) player) {

			if (joker1.getPositionPlayerBoard() > highestTokenPosition) {
				highestTokenPosition = joker1.getPositionPlayerBoard();
			}
		}

		if (joker2.getUsage() == (Token::Usage) player) {

			if (joker2.getPositionPlayerBoard() > highestTokenPosition) {
				highestTokenPosition = joker2.getPositionPlayerBoard();
			}
		}

		highestTokenPosition++;
	}

	for (int token = highestTokenPosition; token < amountOfTokens + highestTokenPosition; token++)
	{
		if (token == 52) {
			std::cout << BOARD_FILLED << std::endl;
			break;
		}

		initialPositionOfToken = rand() % TOTAL_AMOUNT_OF_TOKEN;
		positionOfToken = initialPositionOfToken;

		rowOfToken = (int)positionOfToken / NUMBER_OF_COLUMNS;
		columnOfToken = positionOfToken % NUMBER_OF_COLUMNS;

		while (true) {

			//std::cout << std::endl << "Pos.:" << positionOfToken;
			if (positionOfToken == 104 && joker1.getUsage() == Token::Usage::Stock) {
				joker1.setUsage(player);
				joker1.setPositionPlayerBoard(token);
				//printToken(joker1);
				break;
			}
			else if (positionOfToken == 105 && joker2.getUsage() == Token::Usage::Stock) {
				joker2.setUsage(player);
				joker2.setPositionPlayerBoard(token);
				//printToken(joker2);
				break;
			}
			else if (positionOfToken < 104 && tokens[rowOfToken][columnOfToken].getUsage() == Token::Usage::Stock) {
				tokens[rowOfToken][columnOfToken].setUsage(player);
				tokens[rowOfToken][columnOfToken].setPositionPlayerBoard(token);
				//printToken(tokens[rowOfToken][columnOfToken]);
				break;
			}
			else {
				positionOfToken = positionOfToken + 1;
				if (positionOfToken == 106) {
					positionOfToken = 0;
				}

				rowOfToken = (int)positionOfToken / NUMBER_OF_COLUMNS;
				columnOfToken = positionOfToken % NUMBER_OF_COLUMNS;
			}

			if (positionOfToken == initialPositionOfToken) {
				std::cout << "Ziehen nicht moeglich, da keine Karten mehr auf dem Stapel!";
				return false;
				break;
			}
		}
	}
	return true;
}

int determineIndexPlayerToStart(std::vector<playerAdministration>& score) {
	int numberOfPlayer = score.size();
	srand((unsigned int)time(NULL));
	int indexOfPlayerToStartGame = rand() % numberOfPlayer;

	return indexOfPlayerToStartGame;
}

std::vector<Token>& getTokensOfPlayer(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage player) {

	std::vector<Token> tokensOfPlayer;
	bool tokenFound = true;
	int tokenPosition = 0;
	while (tokenFound) {

		tokenFound = false;

		for (int row = 0; row < NUMBER_OF_ROWS; row++)
		{
			for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
			{
				Token value = tokens[row][column];
				if (value.getUsage() == (Token::Usage) player) {
					if (value.getPositionPlayerBoard() == tokenPosition) {
						tokensOfPlayer.push_back(value);
						tokenFound = true;
					}
				}
			}
		}

		if (joker1.getUsage() == (Token::Usage) player) {
			if (joker1.getPositionPlayerBoard() == tokenPosition) {
				tokensOfPlayer.push_back(joker1);
				tokenFound = true;
			}
		}

		if (joker2.getUsage() == (Token::Usage) player) {
			if (joker2.getPositionPlayerBoard() == tokenPosition) {
				tokensOfPlayer.push_back(joker2);
				tokenFound = true;
			}
		}

		tokenPosition++;
	}

	return tokensOfPlayer;
}

void showTokensOfPlayer(std::vector<Token> tokensOfPlayer, std::string nameOfHumanPlayer) {

	std::cout << std::endl << "Player: " << nameOfHumanPlayer << std::endl;

	for (Token& token : tokensOfPlayer)
	{
		char position = indexToAscii(token.getPositionPlayerBoard());	//ASCII int to char
		std::cout << position << "  ";
	}
	std::cout << std::endl;

	for (Token& token : tokensOfPlayer)
	{
		if (token.getColor() == Token::Color::JOKER_WHITE) {
			std::cout << token.getTerminalColor() << "J" << RESET_TERMINAL_COL << "  ";
		}
		else {
			std::cout << token.getTerminalColor() << token.getValue() << RESET_TERMINAL_COL << " ";
			if ((token.getValue() / 10) == 0) {
				std::cout << " ";
			}
		}
	}

	std::cout << std::endl;
}

void printMemoryStructure(std::vector<std::vector<Token>>& currentPlayground)
{
	std::cout
		<< std::endl
		<< std::endl
		<< std::endl
		<< "Spielfeld:"
		<< std::endl;

	/*
	// show with max Row size
	int maxRowSize = 0;
	for (int row = 0; row < tokens.size(); row++)
	{
		for (int column = 0; column < tokens[row].size(); column++)
		{
			if (maxRowSize < tokens[row].size()) {
				maxRowSize = tokens[row].size();
			}
		}
	}

	// print index
	std::cout << "   ";
	for (int letter = LETTER_A_ASCII_NUMBER; letter < maxRowSize + LETTER_A_ASCII_NUMBER;  letter++)
	{
		char index = letter;
		std::cout << index << "  ";
	}
	std::cout << std::endl;
	*/

	// print index
	std::cout << "   ";
	for (int letter = LETTER_A_ASCII_NUMBER; letter < NUMBER_OF_COLUMNS + LETTER_A_ASCII_NUMBER; letter++)
	{
		char index = letter;
		std::cout << index << "  ";

		if (letter == 90) {
			letter = 96; //skip special Characters
		}
	}
	std::cout << std::endl;

	for (int row = 0; row < currentPlayground.size(); row++)
	{
		std::cout << row << " ";
		if ((row / 10) == 0) {
			std::cout << " ";
		}
		for (int column = 0; column < currentPlayground[row].size(); column++)
		{
			Token token = currentPlayground[row][column];
			if (token.getColor() == Token::Color::JOKER_WHITE) {
				std::cout << token.getTerminalColor() << "J" << RESET_TERMINAL_COL << "  ";
			}
			else {
				std::cout << token.getTerminalColor() << token.getValue() << RESET_TERMINAL_COL << " ";
				if ((token.getValue() / 10) == 0) {
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << currentPlayground.size();

	std::cout << std::endl;
}

void printToken(Token token) {
	std::cout
		<< std::endl
		<< "Farbe: " << token.getColor()
		<< ", Wert: " << token.getValue()
		<< ", Verw.: " << token.getUsage()
		<< ", Pos.: " << token.getPositionPlayerBoard()
		<< ", Spalte: " << token.getColumn()
		<< ", Zeile: " << token.getRow()
		<< std::endl;
}

void regexTester() {
	//std::regex commandMoveTokenPlayerTotoken("([a-zA-Z]|[[:digit:]]+),[ ]*([a-zA-Z]|[[:digit:]]+),[ ]*(R|G|M|C),[ ]*([2-9]|1[0-3]?),[ ]*(J)?");
	//std::regex commandMoveTokenPlayerToTokenCorrect("([a-zA-Z]|[[:digit:]]+),[ ]*([a-zA-Z]|[[:digit:]]+),[ ]*(R|G|M|C),[ ]*([2-9]|1[0-3]?)(,)?[ ]*(J)?");

	std::regex commandMoveSingleToken("([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*>[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z])");
	std::regex commandMoveMultipleTokens("([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*-[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*>[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z]|\\+)");
	std::regex& regex = commandMoveMultipleTokens;

	std::cin.clear();
	std::cin.ignore(INT8_MAX, '\n');
	while (true)
	{
		char testStr[50];
		std::cout << "Enter a String:" << std::endl;
		std::cin.getline(testStr, sizeof(testStr));
		std::string str(testStr);
		//processCommandInput(str);

		/*
		if (std::regex_match(testStr, regex)) {
			std::cout << "YES - Your entered string matches!" << std::endl;
		}
		else {
			std::cout << "NO - Your entered string doesn't match!" << std::endl;
		}
		*/

	}
}

void processCommandInput(std::string& command, Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer,
	std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {
	std::regex commandMoveSingleToken("([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*>[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z])");
	//std::regex commandMoveMultipleTokens("([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*-[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*>[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z]|\\+)");

	int fromRow;
	int fromColumn;
	int toRow;
	int toColumn;

	if (std::regex_match(command, commandMoveSingleToken)) {
		splitCommandMoveSingleToken(command, fromRow, fromColumn, toRow, toColumn);
		moveToken(currentPlayground, tokensOfPlayer, fromRow, fromColumn, toRow, toColumn);
	}
	/*else if (std::regex_match(command, commandMoveMultipleTokens)) {
		std::cout << "WRONG!";
	}*/
	else {
		// TODO: Befehl in Ausgabe ergänzen
		std::cout << "Der eingegebene Befehl entspricht nicht der geforderten Syntax! " << std::endl;
	}

}

void splitCommandMoveSingleToken(std::string& command, int& fromRow, int& fromColumn, int& toRow, int& toColumn) {
	std::string delimiter = ">";
	std::string from = command.substr(0, command.find(delimiter));
	std::string to = command.substr(command.find(delimiter) + 1, command.size() - 1);

	trim(from);
	trim(to);
	//std::cout << "<" << from << ">" << std::endl;
	//std::cout << "<" << to << ">" << std::endl;

	getRowAndColumnOfCommandEntry(from, fromRow, fromColumn);
	getRowAndColumnOfCommandEntry(to, toRow, toColumn);
}

void getRowAndColumnOfCommandEntry(std::string& commandEntry, int& row, int& column) {
	// Bsp.: A (player)
	if (commandEntry.size() == 1) {
		row = -1; //-> User want to move Token from/to player
		//column = ((int)commandEntry.at(0)) - LETTER_A_ASCII_NUMBER;
		column = asciiToIndex(commandEntry.at(0));
	}

	// Bsp.: 1B (playground)
	if (commandEntry.size() == 2) {
		row = std::stoi(commandEntry.substr(0, 1));
		//column = ((int)commandEntry.at(1)) - LETTER_A_ASCII_NUMBER;
		column = asciiToIndex(commandEntry.at(1));
	}

	// Bsp.: 10B (playground)
	if (commandEntry.size() == 3) {
		row = std::stoi(commandEntry.substr(0, 2));
		//column = ((int)commandEntry.at(2)) - LETTER_A_ASCII_NUMBER;
		column = asciiToIndex(commandEntry.at(2));
	}
}

void moveToken(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toRow, int& toColumn) {
	// row = -1 -> User want to move Token from/to player

	//std::cout << "Spielstein wird wie folgt verschoben: " << std::endl;
	//std::cout << "Von (Reihe): <" << fromRow << ">" << std::endl;
	//std::cout << "Von (Spalte): <" << fromColumn << ">" << std::endl;
	//std::cout << "Nach (Reihe): <" << toRow << ">" << std::endl;
	//std::cout << "Nach (Spalte): <" << toColumn << ">" << std::endl;

	bool validationSuccessful = basicValidationOfRowAndColumn(currentPlayground, tokensOfPlayer, fromRow, fromColumn, toRow, toColumn);

	// try to move Token
	if (validationSuccessful && fromRow == -1 && toRow == -1) {
		moveTokenOnBoard(tokensOfPlayer, fromColumn, toColumn);
	}
	else if (validationSuccessful && fromRow != -1 && toRow == -1) {
		moveTokenPlaygroundToBoard(currentPlayground, tokensOfPlayer, fromRow, fromColumn, toColumn);
	}
	else if (validationSuccessful && fromRow == -1 && toRow != -1) {
		moveTokenBoardToPlayground(currentPlayground, tokensOfPlayer, fromColumn, toRow, toColumn);
	}
	else if (validationSuccessful && fromRow != -1 && toRow != -1) {
		moveTokenOnPlayground(currentPlayground, fromRow, fromColumn, toRow, toColumn);
	}
	else {
		// user feedback in method basicValidationOfRowAndColumn
	}
}

bool basicValidationOfRowAndColumn(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toRow, int& toColumn)
{
	bool validationSuccessful = false;

	// check from value (currently on board of the player)
	if (fromRow == -1) {
		if (fromColumn >= tokensOfPlayer.size()) {
			std::cout << "An der angebenen Stelle zur Spielstein-Entnahme liegt kein Spielstein vor!";
		}
		else {
			validationSuccessful = true;
		}
	}
	// check from value (currently on the playground)
	else {
		if (fromRow >= currentPlayground.size()) {
			std::cout << "An der angebenen Stelle zur Spielstein-Entnahme liegt kein Spielstein vor!";
		}
		else if (fromColumn >= currentPlayground[fromRow].size()) {
			std::cout << "An der angebenen Stelle zur Spielstein-Entnahme liegt kein Spielstein vor!";
		}
		else {
			validationSuccessful = true;
		}
	}
	// check to value (condition on playground)
	if (toRow != -1 && toColumn >= NUMBER_OF_COLUMNS) {
		std::cout << "Mehr als 13 Zahlen sind in einer Reihe nicht moeglich!";
		validationSuccessful = false;
	}

	return validationSuccessful;
}

void moveTokenOnBoard(std::vector<Token>& tokensOfPlayer, int& fromColumn, int& toColumn)
{
	if (tokensOfPlayer.size() >= toColumn) {
		// Insert Token on the left side: Ex.: 1 2 3 4 5 -> Command: D > B
		if (fromColumn > toColumn) {
			insertTokenAndMoveElementsRight(tokensOfPlayer, fromColumn, toColumn);
		}
		else if (fromColumn == toColumn) {
			std::cout << "Gebe bitte 2 unterschiedliche Positionen zum Verschieben an!";
		}
		// Insert Token on the right side: Ex.: 1 2 3 4 5 -> Command: B > D
		else {
			insertTokenAndMoveElementsLeft(tokensOfPlayer, fromColumn, toColumn);
		}
	}
	else {
		std::cout << "Es kann nicht nach der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
	}
}

void moveTokenPlaygroundToBoard(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toColumn)
{
	if (tokensOfPlayer.size() >= toColumn) {
		// Add Token as last element Ex.: insert 5
		// Insert Token on the left side: Ex.: 1 2 6 7 5 -> Command: E > ...
		currentPlayground[fromRow][fromColumn].setPositionPlayerBoard(tokensOfPlayer.size());
		tokensOfPlayer.push_back(currentPlayground[fromRow][fromColumn]);
		if (tokensOfPlayer.size() - 1 > toColumn) {
			insertTokenAndMoveElementsRight(tokensOfPlayer, tokensOfPlayer.size() - 1, toColumn);
		}
		// Delete from playground -> move Token to last element -> delete last Element
		if (currentPlayground[fromRow].size() != fromColumn - 1) {
			insertTokenAndMoveElementsLeft(currentPlayground[fromRow], fromColumn, currentPlayground[fromRow].size());
		}
		currentPlayground[fromRow].pop_back();
		// delete empty Row, if row is before last row
		if (currentPlayground[fromRow].empty() && currentPlayground.size() - 1 == fromRow) {
			currentPlayground.pop_back();
		}
	}
	else {
		std::cout << "Es kann nicht nach der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
	}
}

void moveTokenBoardToPlayground(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromColumn, int& toRow, int& toColumn)
{
	bool processingSuccessful = true;

	if (currentPlayground.size() > toRow) {
		if (currentPlayground[toRow].size() == NUMBER_OF_COLUMNS) {
			std::cout << "Einfuegen nicht moeglich, da angegebene Zeile auf dem Spielfeld schon voll ist -> max. 13 Elemente pro Zeile!";
			processingSuccessful = false;
		}
		else {
			if (currentPlayground[toRow].size() >= toColumn) {
				// Add Token as last element Ex.: insert 5
				// Insert Token on the left side: Ex.: 1 2 6 7 5 -> Command: E > ...
				currentPlayground[toRow].push_back(tokensOfPlayer[fromColumn]);
				if (currentPlayground[toRow].size() - 1 > toColumn) {
					insertTokenAndMoveElementsRight(currentPlayground[toRow], currentPlayground[toRow].size() - 1, toColumn);
				}
			}
			else {
				std::cout << "Es kann nicht nach der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
				processingSuccessful = false;
			}
		}
	}
	else if (currentPlayground.size() == toRow) {
		if (toColumn == 0) {
			std::vector<Token> toAdd;
			toAdd.push_back(tokensOfPlayer[fromColumn]);
			currentPlayground.push_back(toAdd);
		}
		else {
			std::cout << "Es kann nicht nach der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
			processingSuccessful = false;
		}
	}
	else {
		std::cout << "Es kann nicht nach der letzten Zeile eingefuegt werden! -> Gebe zum Einfuegen in der letzte Zeile, deren Index an!";
		processingSuccessful = false;
	}

	// Delete from board -> move Token to last element -> delete last Element
	if (processingSuccessful) {
		if (tokensOfPlayer.size() != fromColumn - 1) {
			insertTokenAndMoveElementsLeft(tokensOfPlayer, fromColumn, tokensOfPlayer.size());
		}
		tokensOfPlayer.pop_back();
	}

}

void moveTokenOnPlayground(std::vector<std::vector<Token>>& currentPlayground, int& fromRow, int& fromColumn, int& toRow, int& toColumn)
{
	bool processingSuccessful = true;

	if (currentPlayground.size() > toRow) {
		if (currentPlayground[toRow].size() == NUMBER_OF_COLUMNS) {
			std::cout << "Einfuegen nicht moeglich, da angegebene Zeile auf dem Spielfeld schon voll ist -> max. 13 Elemente pro Zeile!";
			processingSuccessful = false;
		}
		else {
			if (currentPlayground[toRow].size() >= toColumn) {
				// Add Token as last element Ex.: insert 5
				// Insert Token on the left side: Ex.: 1 2 6 7 5 -> Command: E > ...
				currentPlayground[toRow].push_back(currentPlayground[fromRow][fromColumn]);
				if ((currentPlayground[toRow].size() - 1) > toColumn) {
					insertTokenAndMoveElementsRight(currentPlayground[toRow], currentPlayground[toRow].size() - 1, toColumn);
				}
			}
			else {
				std::cout << "Es kann nicht nach der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
				processingSuccessful = false;
			}
		}
	}
	else if (currentPlayground.size() == toRow) {
		if (toColumn == 0) {
			std::vector<Token> toAdd;
			toAdd.push_back(currentPlayground[fromRow][fromColumn]);
			currentPlayground.push_back(toAdd);
		}
		else {
			std::cout << "Es kann nicht nach der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
			processingSuccessful = false;
		}
	}
	else {
		std::cout << "Es kann nicht nach der letzten Zeile eingefuegt werden! -> Gebe zum Einfuegen in der letzte Zeile, deren Index an!";
		processingSuccessful = false;
	}
	// Delete from playground -> move Token to last element -> delete last Element
	if (processingSuccessful) {
		if (currentPlayground[fromRow].size() != fromColumn - 1) {
			insertTokenAndMoveElementsLeft(currentPlayground[fromRow], fromColumn, currentPlayground[fromRow].size());
		}
		currentPlayground[fromRow].pop_back();
		// delete empty Row, if row is before last row
		if (currentPlayground[fromRow].empty() && currentPlayground.size() - 1 == fromRow) {
			currentPlayground.pop_back();
		}
	}
}

void insertTokenAndMoveElementsRight(std::vector<Token>& tokensOfPlayer, int columnOfElementToInsert, int toColumn) {
	for (int column = columnOfElementToInsert; column != toColumn; column--)
	{
		swapValuesOfTwoTokens(tokensOfPlayer.at(column), tokensOfPlayer.at(column - 1));
	}
}

void insertTokenAndMoveElementsLeft(std::vector<Token>& tokensOfPlayer, int columnOfElementToInsert, int toColumn) {
	for (int column = columnOfElementToInsert; column != toColumn - 1; column++)
	{
		swapValuesOfTwoTokens(tokensOfPlayer.at(column), tokensOfPlayer.at(column + 1));
	}
}

void setValuesOfAnotherToken(Token& toBeModified, Token& toBeCopied) {
	toBeModified.setColor(toBeCopied.getColor());
	toBeModified.setValue(toBeCopied.getValue());
	toBeModified.setUsage(toBeCopied.getUsage());
	//toBeModified.setPositionPlayerBoard(toBeCopied.getPositionPlayerBoard());
	toBeModified.setColumn(toBeCopied.getColumn());
	toBeModified.setRow(toBeCopied.getRow());
	toBeModified.setColumnPlayground(toBeCopied.getColumnPlayground());
	toBeModified.setRowPlayground(toBeCopied.getRowPlayground());
}

void swapValuesOfTwoTokens(Token& token1, Token& token2) {

	Token::Color color = token1.getColor();
	int value = token1.getValue();
	Token::Usage usage = token1.getUsage();
	//int positionPlayerBoard = token1.getPositionPlayerBoard();
	int column = token1.getColumn();
	int row = token1.getRow();
	int columnPlayground = token1.getColumnPlayground();
	int rowPlayground = token1.getRowPlayground();

	token1.setColor(token2.getColor());
	token1.setValue(token2.getValue());
	token1.setUsage(token2.getUsage());
	//token1.setPositionPlayerBoard(token2.getPositionPlayerBoard());
	token1.setColumn(token2.getColumn());
	token1.setRow(token2.getRow());
	token1.setColumnPlayground(token2.getColumnPlayground());
	token1.setRowPlayground(token2.getRowPlayground());

	token2.setColor(color);
	token2.setValue(value);
	token2.setUsage(usage);
	//token2.setPositionPlayerBoard(positionPlayerBoard);
	token2.setColumn(column);
	token2.setRow(row);
	token2.setColumnPlayground(columnPlayground);
	token2.setRowPlayground(rowPlayground);
}

std::vector<std::vector<Token>> getPlaygroundToDisplay() {
	std::vector<std::vector<Token>> playgroundBeforeMove;

	std::vector<Token> toAdd1;
	Token token1(Token::Color::CYAN, 3, Token::Usage::Playground, -1, 0, 2, 0, 0);
	Token token2(Token::Color::CYAN, 4, Token::Usage::Playground, -1, 0, 3, 1, 0);
	Token token3(Token::Color::CYAN, 5, Token::Usage::Playground, -1, 0, 4, 2, 0);
	toAdd1.push_back(token1);
	toAdd1.push_back(token2);
	toAdd1.push_back(token3);
	playgroundBeforeMove.push_back(toAdd1);

	std::vector<Token> toAdd2;
	Token token4(Token::Color::CYAN, 12, Token::Usage::Playground, -1, 0, 4, 0, 1);
	Token token5(Token::Color::RED, 12, Token::Usage::Playground, -1, 2, 4, 1, 1);
	Token token6(Token::Color::YELLOW, 12, Token::Usage::Playground, -1, 4, 4, 2, 1);
	Token token7(Token::Color::PURPLE, 12, Token::Usage::Playground, -1, 6, 4, 3, 1);
	toAdd2.push_back(token4);
	toAdd2.push_back(token5);
	toAdd2.push_back(token6);
	toAdd2.push_back(token7);
	playgroundBeforeMove.push_back(toAdd2);

	std::vector<Token> toAdd3;
	Token token8(Token::Color::CYAN, 9, Token::Usage::Playground, -1, 0, 4, 0, 2);
	/*Token token9(Token::Color::RED, 9, Token::Usage::Playground, -1, 2, 4, 1, 2);
	Token token10(Token::Color::YELLOW, 9, Token::Usage::Playground, -1, 4, 4, 2, 2);*/
	toAdd3.push_back(token8);
	//toAdd3.push_back(token9);
	//toAdd3.push_back(token10);
	playgroundBeforeMove.push_back(toAdd3);

	return playgroundBeforeMove;
}