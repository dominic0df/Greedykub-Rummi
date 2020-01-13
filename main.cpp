#include "main.h"
#include "userInputProcessing.h"
#include "shared.h"

int main()
{
	std::cout << WELCOME << std::endl;
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, -1, -1, -1, -1, -1);
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, -1, -1, -1, -1, -1);
	setStartingCondition(tokens, joker1, joker2);
	printMemoryStructure(tokens, joker1, joker2);
	std::vector<std::vector<std::map < Token::Color, int >>> x = searchForGroups(tokens);
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

void testSearchForGroups(std::vector<std::vector<std::vector<int>>>& x, std::vector<std::vector<Token>>& tokens)
{
	for (int i = 0; i < x.size(); i++)
	{
		for (int j = 0; j < x[i].size(); j++)
		{

			for (int color = 0; color < x[i][j].size(); color++)
			{
				std::cout << "index" << i << ", " << color /*<< "has color" << tokens[i][color]*/ << std::endl;
			}
		}
	}
}

std::vector<std::vector<std::map < Token::Color, int >>> searchForGroups(std::vector<std::vector<Token>>& tokens)
{
	std::vector<std::vector<std::map < Token::Color, int >>> foundGroupsAllColumns;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		std::vector<std::map<Token::Color, int>>foundGroups;
		std::map<int, Token::Color> indexWithColor;
		std::set<int> processed;
		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if (tokens[j][i].getUsage() == Token::Usage::Playground) //|| (field[i][j].location == "HandToPlayground"))
			{
				indexWithColor[j] = (Token::Color) tokens[j][i].getColor();
			}
		}
		int numberOfRemainingColors = indexWithColor.size();
		bool notEqual = true;
		std::shared_ptr<std::map<Token::Color, int>> newGroup(new std::map<Token::Color, int>());
		//std::map<Token::Color, int>* newGroup;
		std::shared_ptr<std::map<Token::Color, int>> group(new std::map<Token::Color, int>());
		std::shared_ptr<std::map<Token::Color, int>> nextGroup(new std::map<Token::Color, int>());
		newGroup = group;
		if (numberOfRemainingColors > 2)
		{
			while (notEqual)
			{
				if (foundGroups.size() == 1)
				{
					newGroup = nextGroup;
				}
				int size;
				if (newGroup == nullptr)
				{
					size = 0;
				}
				else {
					size = newGroup->size();
				}
				int sufficientColors = numberOfRemainingColors + size;
				if (sufficientColors > 2)
				{
					for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
					{
						if (newGroup->size() == 0 && nextGroup->size() > 0)
						{
							newGroup = nextGroup;
						}
						bool colorWithIndexProcessed = processed.find(iter->first) != processed.end();
						if (!colorWithIndexProcessed) {
							if (newGroup->size() != 0 && newGroup->size() < 3) {
								bool colorInNewGroup = newGroup->find(iter->second) != newGroup->end();
								if (!colorInNewGroup)
								{
									processed.insert(iter->first);
									newGroup->insert(std::pair<Token::Color, int>(iter->second, iter->first));
									numberOfRemainingColors--;
								}
								if (newGroup->size() > 2)
								{
									foundGroups.push_back(*newGroup);
									if (numberOfRemainingColors > 2)
									{
										newGroup = nextGroup;
									}
								}
							}
							else {
								if (newGroup == nullptr)
								{
									size = 0;
								}
								else {
									size = newGroup->size();
								}
								if (size == 0)
								{
									newGroup->insert(std::pair<Token::Color, int>(iter->second, iter->first));
									processed.insert(iter->first);
									numberOfRemainingColors--;
								}
							}
						}
					}
				}
				else
				{
					notEqual = false;
				}
				newGroup = nullptr;
				//nicht geprüfter teil kleiner 5
				//if (numberOfRemainingColors < 5)
				std::map<Token::Color, int> repeated;
				for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
				{
					repeated[iter->second] = repeated[iter->second]++;
				}
				if (repeated.size() < 3) {
					notEqual = false;
				}
			}
		}
		int indexOfFoundGroup = 0;
		while (numberOfRemainingColors > 0 && indexOfFoundGroup < foundGroups.size())
		{
			for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
			{
				bool colorWithIndexProcessed = processed.find(iter->first) != processed.end();
				bool colorInNewGroup = foundGroups[indexOfFoundGroup].find(iter->second) != foundGroups[indexOfFoundGroup].end();
				if (!colorInNewGroup)
				{
					if (!colorWithIndexProcessed && foundGroups[indexOfFoundGroup].size() < 4)
					{
						foundGroups[indexOfFoundGroup].insert(std::pair<Token::Color, int>(iter->second, iter->first));
						processed.insert(iter->first);
						numberOfRemainingColors--;
					}
				}
			}
			indexOfFoundGroup++;
		}
		foundGroupsAllColumns.push_back(foundGroups);
	}
	return foundGroupsAllColumns;
}

std::vector<std::vector<std::vector<Token>>> searchForRows(std::vector<std::vector<Token>>& tokens)
{
	std::vector<std::vector<std::vector<Token>>> foundRowsAllColors;
	bool processed[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = { false };
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		std::vector<std::vector<Token>>foundRows;
		std::shared_ptr<std::vector<Token>> row(new std::vector<Token>());
		std::shared_ptr<std::vector<Token>> firstRow(new std::vector<Token>());
		row = firstRow;
		int shift;
		if (i % 2 == 0) {
			shift = 1;
		}
		else
		{
			shift = -1;
		}
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			int size;
			if (row == nullptr)
			{
				size = 0;
			}
			else {
				size = row->size();
			}
			if (tokens[i][j].getUsage() == Token::Usage::Playground && !processed[i][j]) {
				if (size == 0) {
					row->push_back(tokens[i][j]);
					processed[i][j] = true;
				}
				else {
					if (((*row)[row->size() - 1].getValue() == j) && (row->size() < 3))
					{
						row->push_back(tokens[i][j]);
						processed[i][j] = true;
					}
					else
					{
						if (row->size() > 2) {
							foundRows.push_back(*row);
						}
						else
						{
							if (row->size() == 2)
							{
								processed[i][j - 2] = false;
								processed[i][j - 3] = false;
							}
							else
							{
								if (row->size() == 1)
								{
									processed[i][j - 2] = false;
								}
							}
						}
						std::shared_ptr<std::vector<Token>> nextRow(new std::vector<Token>());
						row = nextRow;
						row->push_back(tokens[i][j]);
						processed[i][j] = true;
					}
				}
			}
			else {
				if (tokens[i + shift][j].getUsage() == Token::Usage::Playground && !processed[i + shift][j]) {
					if (size == 0) {
						row->push_back(tokens[i + shift][j]);
						processed[i + shift][j] = true;
					}
					else {
						if (((*row)[row->size() - 1].getValue() == j) && (row->size() < 3))
						{
							row->push_back(tokens[i + shift][j]);
							processed[i + shift][j] = true;
						}
						else
						{
							if (row->size() > 2) {
								foundRows.push_back(*row);
							}
							std::shared_ptr<std::vector<Token>> nextRow(new std::vector<Token>());
							row = nextRow;
							row->push_back(tokens[i][j]);
							processed[i + shift][j] = true;
						}
					}
				}
				//processed auch true wenns nicht playground als else
			}

		}
		if (row->size() == 1)
		{
			processed[i][NUMBER_OF_COLUMNS - 1] = false;
		}
		else
		{
			if (row->size() == 2)
			{
				processed[i][NUMBER_OF_COLUMNS - 1] = false;
				processed[i][NUMBER_OF_COLUMNS - 2] = false;
			}
			else
			{
				if (row->size() > 2) {
					foundRows.push_back(*row);
				}
			}
		}

		int indexOfFoundRow = 0;
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			bool c = !processed[i][column];
			if (c)
			{
				if (tokens[i][column].getUsage() == Token::Usage::Playground)
				{
					for (int numberOfRemainingRows = 0; numberOfRemainingRows < foundRows.size(); numberOfRemainingRows++)
					{
						int sizeOfVector = foundRows[numberOfRemainingRows].size();
						//Token tokenToFillIn = foundRows[i][column];
						int valueToFind = tokens[i][column].getValue() - 1;
						int currentValue = foundRows[numberOfRemainingRows][(sizeOfVector - 1)].getValue();
						if (currentValue == valueToFind) {
							foundRows[numberOfRemainingRows].push_back(tokens[i][column]);
							processed[i][column] = true;
						}
					}
				}
			}
		}
		foundRowsAllColors.push_back(foundRows);
	}
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		int shift;
		if (i % 2 == 0) {
			shift = 1;
		}
		else
		{
			shift = -1;
		}
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++) {
			if (tokens[i][column].getUsage() == Token::Usage::Playground && !processed[i + shift][column]) {
				for (int numberOfRemainingRowsShift = 0; numberOfRemainingRowsShift < foundRowsAllColors[i + shift].size(); numberOfRemainingRowsShift++)
				{
					int sizeOfVector = foundRowsAllColors[i + shift][numberOfRemainingRowsShift].size();
					int currentValueShift = foundRowsAllColors[i + shift][numberOfRemainingRowsShift][(sizeOfVector - 1)].getValue();
					//Token tokenToFillIn = foundRows[i][column];
					int valueToFind = tokens[i][column].getValue() - 1;
					int currentValue = foundRowsAllColors[i + shift][numberOfRemainingRowsShift][(sizeOfVector - 1)].getValue();
					if (currentValue == valueToFind) {
						foundRowsAllColors[i + shift][numberOfRemainingRowsShift].push_back(tokens[i][column]);
						processed[i + shift][column] = true;
					}
				}
			}
		}
	}
	return foundRowsAllColors;
}

void startGame() {
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, -1, -1, -1, -1, -1);
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, -1, -1, -1, -1, -1);
	setStartingCondition(tokens, joker1, joker2);

	//printMemoryStructure(tokens, joker1, joker2);
	//std::cout << x.size() << std::endl;
	//std::cout << x[0].size() << std::endl;
	//std::cout << x[0][0].size() << std::endl;
	/*for (int i = 0; i < x.size(); i++)
	{
		for (int j = 0; j < x[i].size(); j++)
		{
			for (int color = 0; color < x[i][j].size(); color++)
			{
				std::cout << "index" << i << ", " << color /*<< "has color" << tokens[i][color] << std::endl;
			}
		}
	}*/
	//testSearchForGroups(x,tokens);

	std::vector<scoreEntry> score;
	std::string nameOfHumanPlayer;

	setPlayerInformation(score, nameOfHumanPlayer);

	int indexOfPlayerToStartGame = determineIndexPlayerToStart(score);
	std::cout << std::endl << MESSAGE_PLAYER_TO_START << score[indexOfPlayerToStartGame].player << std::endl;

	dealTokens(score, tokens, joker1, joker2);

	/*for (int player = 1; player < score.size(); player++)
	{
		showTokensOfPlayer(tokens, joker1, joker2, (Token::Usage) player);
	}*/

	bool gameOn = true;
	std::cin.clear();
	std::cin.ignore(INT8_MAX, '\n');
	std::vector<std::vector<Token>> currentPlayground = getPlaygroundToDisplay();
	std::vector<Token> tokensOfPlayer = getTokensOfPlayer(tokens, joker1, joker2, Token::HUMAN_Player);
	while (gameOn) {
		printMemoryStructure(currentPlayground, joker1, joker2);
		showTokensOfPlayer(tokensOfPlayer, nameOfHumanPlayer);

		//Achtung: Keine Referenz übergeben! -> Kopie -> currentPlayground
		//std::vector<std::vector<Token>> currentPlayground;
		makeMovePlayer(Token::Usage::HUMAN_Player, currentPlayground, tokensOfPlayer, gameOn, tokens, joker1, joker2);
	}

	/*
	std::cout << std::endl;
	for (scoreEntry& entry : score)
	{
		std::cout << entry.player << ": " << entry.point << std::endl;
	}
	*/
}

void dealTokens(std::vector<scoreEntry>& score, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {

	for (int player = 0; player < score.size(); player++)
	{
		//std::cout << std::endl << std::endl << "Player: " << player;
		drawTokenRandomlyFromStock(tokens, joker1, joker2, (Token::Usage) player, AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING);
	}
}

void drawTokenRandomlyFromStock(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2,
	Token::Usage player, int amountOfTokens) {
	//auto zufall=srand((unsigned int)time(NULL));
	//srand(1);
	// TODO: eventuell srand benutzen

	int positionOfToken;
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

		positionOfToken = rand() % TOTAL_AMOUNT_OF_TOKEN;

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
		}
	}
}

int determineIndexPlayerToStart(std::vector<scoreEntry>& score) {
	int numberOfPlayer = score.size();
	srand((unsigned int)time(NULL));
	int indexOfPlayerToStartGame = rand() % numberOfPlayer;

	return indexOfPlayerToStartGame;
}

std::vector<Token> getTokensOfPlayer(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage player) {

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

void printMemoryStructure(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	std::cout
		<< std::endl
		<< std::endl
		<< "--------------------------------------------------------------------------------------------"
		<< std::endl
		<< "Spielfeld:"
		<< std::endl;

	/*
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

	for (int row = 0; row < tokens.size(); row++)
	{
		std::cout << row << " ";
		if ((row / 10) == 0) {
			std::cout << " ";
		}
		for (int column = 0; column < tokens[row].size(); column++)
		{
			Token token = tokens[row][column];
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
	std::cout << tokens.size();

	std::cout << std::endl;
}

/*void printPlayground(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	for (int row = 0; row < NUMBER_OF_ROWS; row++)
	{
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			if(tokens[row][column])
			Token value = tokens[row][column];
			std::cout << value.getTerminalColor() << value.getValue() << RESET_TERMINAL_COL << " ";
		}
		std::cout << std::endl;
	}

	std::cout << joker1.getTerminalColor() << "J" << RESET_TERMINAL_COL << " ";
	std::cout << joker2.getTerminalColor() << "J" << RESET_TERMINAL_COL << " ";
	std::cout << std::endl;
}*/

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
	std::regex commandMoveMultipleTokens("([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*-[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z])[ ]*>[ ]*([a-zA-Z]|[[:digit:]]+[a-zA-Z]|\\+)");

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
		std::cout << "WRONG!";
	}

}

void splitCommandMoveSingleToken(std::string& command, int& fromRow, int& fromColumn, int& toRow, int& toColumn) {
	std::string delimiter = ">";
	std::string from = command.substr(0, command.find(delimiter));
	std::string to = command.substr(command.find(delimiter) + 1, command.size() - 1);

	trim(from);
	trim(to);
	std::cout << "<" << from << ">" << std::endl;
	std::cout << "<" << to << ">" << std::endl;

	getRowAndColumnOfCommandEntry(from, fromRow, fromColumn);
	getRowAndColumnOfCommandEntry(to, toRow, toColumn);
}

void getRowAndColumnOfCommandEntry(std::string& commandEntry, int& row, int& column) {
	// Bsp.: A (player)
	if (commandEntry.size() == 1) {
		row = -1; //-> User want to move Token from/to player
		column = ((int)commandEntry.at(0)) - LETTER_A_ASCII_NUMBER;
	}

	// Bsp.: 1B (playground)
	if (commandEntry.size() == 2) {
		row = std::stoi(commandEntry.substr(0, 1)) - 1;
		column = ((int)commandEntry.at(1)) - LETTER_A_ASCII_NUMBER;
	}

	// Bsp.: 10B (playground)
	if (commandEntry.size() == 3) {
		row = std::stoi(commandEntry.substr(0, 2)) - 1;
		column = ((int)commandEntry.at(2)) - LETTER_A_ASCII_NUMBER;
	}
}

void moveToken(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toRow, int& toColumn) {
	// S -> Spielfeld		B -> Brett
	// Step 1: Brett -> Brett (A > B) -> B: Tauschen der beiden Zahlen
	// Step 2: Brett -> Spielfeld (A > 1C)  -> S: 1C liegt Karte?	-> JA B: Karten nach rechts verschieben, Karte von B nach S verschieben, B: Karten nach links verschieben
	//																-> NEIN B: Karte von B nach S verschieben, B: Karten nach links verschieben 
	// Step 3: Spielfeld -> Brett (1C > A) -> B:  C liegt Karte?	-> JA S: Karten nach rechts verschieben, Karte von S nach B verschieben, B: Karten nach links verschieben
	//																-> NEIN B: Karte von S nach B verschieben, S: Karten nach links verschieben 
	// Step 4: Spielfeld -> Spielfeld (1C > 1D) ->	1D liegt Karte) -> JA B: Karten nach rechts verschieben, Karte von S nach S verschieben, S: Karten nach links verschieben 
	//																-> NEIN B: Karte von S nach S verschieben, B: Karten nach links verschieben 
	// row = -1 -> User want to move Token from/to player

	std::cout << "Spielstein wird wie folgt verschoben: " << std::endl;
	std::cout << "Von (Reihe): <" << fromRow << ">" << std::endl;
	std::cout << "Von (Spalte): <" << fromColumn << ">" << std::endl;
	std::cout << "Nach (Reihe): <" << toRow << ">" << std::endl;
	std::cout << "Nach (Spalte): <" << toColumn << ">" << std::endl;

	bool fromValuesValid = false;
	// check from value (currently on board of the player)
	if (fromRow == -1) {
		if (fromColumn >= tokensOfPlayer.size()) {
			std::cout << "An der angebenen Stelle zur Spielstein-Entnahme liegt kein Spielstein vor! -> Wert zu groß!";
		}
		else {
			fromValuesValid = true;
		}
	}
	else {
		// Playground
	}
	//Board 2 Board
	if (fromValuesValid) {
		if (toRow == -1) {
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
				//deleteTokenAndMoveElementsLeft(tokensOfPlayer, fromColumn);
			}
			// Insert Token at last position (empty) of board: Ex.: 1 2 3 4 -> Command: B > E
			/*else if (tokensOfPlayer.size() == toColumn) {
				tokensOfPlayer[fromColumn].setColumn(tokensOfPlayer.size());
				tokensOfPlayer.push_back(tokensOfPlayer[fromColumn]);
				deleteTokenAndMoveElementsLeft(tokensOfPlayer, fromColumn);
			}*/
			else {
				std::cout << "Es kann nur an der letzten Stelle angefuegt werden! -> Gebe zum Einfuegen an der letzte Stelle, deren Index an!";
			}
		}
	}
}

/*void deleteTokenAndMoveElementsLeft(std::vector<Token>& tokensOfPlayer, int& columnOfElementToDelete) {
	for (int column = columnOfElementToDelete; column < tokensOfPlayer.size() - 2; column++)
	{
		setValuesOfAnotherToken(tokensOfPlayer.at(column), tokensOfPlayer.at(column + 1));
	}
}*/

void insertTokenAndMoveElementsRight(std::vector<Token>& tokensOfPlayer, int& columnOfElementToInsert, int& toColumn) {
	for (int column = columnOfElementToInsert; column != toColumn; column--)
	{
		swapValuesOfTwoTokens(tokensOfPlayer.at(column), tokensOfPlayer.at(column - 1));
	}
}

void insertTokenAndMoveElementsLeft(std::vector<Token>& tokensOfPlayer, int& columnOfElementToInsert, int& toColumn) {
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

	return playgroundBeforeMove;
}