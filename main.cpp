#include "main.h"
#include "userInputProcessing.h"

int main()
{
	std::cout << WELCOME << std::endl;
	firstUserInteraction();
}

void startGame() {
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	setStartingCondition(tokens, joker1, joker2);
	//printMemoryStructure(tokens, joker1, joker2);
	std::vector<scoreEntry> score;
	std::string nameOfHumanPlayer;

	setPlayerInformation(score, nameOfHumanPlayer);

	int indexOfPlayerToStartGame = determineIndexPlayerToStart(score);
	std::cout << std::endl << MESSAGE_PLAYER_TO_START << score[indexOfPlayerToStartGame].player;

	drawTokenRandomlyFromStock(tokens, joker1, joker2, Token::Usage::HUMAN_Player, AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING);

	/*
	std::cout << std::endl;
	for (scoreEntry& entry : score)
	{
		std::cout << entry.player << ": " << entry.point << std::endl;
	}
	*/
}

void drawTokenRandomlyFromStock(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage player, int amountOfTokens) {
	srand((unsigned int)time(NULL));

	int positionOfToken;
	int rowOfToken;
	int columnOfToken;

	for (int token = 0; token < amountOfTokens; token++)
	{
		positionOfToken = rand() % TOTAL_AMOUNT_OF_TOKEN;

		rowOfToken = (int)positionOfToken / NUMBER_OF_COLUMNS;
		columnOfToken = positionOfToken % NUMBER_OF_COLUMNS;

		while (true) {

			std::cout << std::endl << std::endl << "Pos.:" << positionOfToken;
			if (positionOfToken == 104 && joker1.getUsage() == Token::Usage::Stock) {
				joker1.setUsage(player);
				printToken(joker1);
				break;
			}
			else if (positionOfToken == 105 && joker2.getUsage() == Token::Usage::Stock) {
				joker2.setUsage(player);
				printToken(joker2);
				break;
			}
			else if (tokens[rowOfToken][columnOfToken].getUsage() == Token::Usage::Stock) {
				tokens[rowOfToken][columnOfToken].setUsage(player);
				printToken(tokens[rowOfToken][columnOfToken]);
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

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{

	for (int color = 0; color < 4; color++)
	{
		std::vector<Token> toAdd;
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			Token token((Token::Color) color, column + 1, Token::Usage::Stock, "");
			toAdd.push_back(token);
		}
		tokens.push_back(toAdd);
		tokens.push_back(toAdd);
	}
}

void printMemoryStructure(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	for (int row = 0; row < NUMBER_OF_ROWS; row++)
	{
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			Token value = tokens[row][column];
			std::cout << value.getTerminalColor() << value.getValue() << RESET_TERMINAL_COL << " ";
		}
		std::cout << std::endl;
	}

	std::cout << joker1.getTerminalColor() << "J" << RESET_TERMINAL_COL << " ";
	std::cout << joker2.getTerminalColor() << "J" << RESET_TERMINAL_COL << " ";
	std::cout << std::endl;
}

void printToken(Token token) {
	std::cout
		<< std::endl
		<< "Farbe: " << token.getColor()
		<< ", Wert: " << token.getValue()
		<< ", Verw.: " << token.getUsage()
		<< ", Pos.: " << token.getPosition()
		<< std::endl;
}

/*std::vector<Token>*/void searchForGroups(std::vector<std::vector<Token>>& tokens)
{
	Token::Color color;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		std::map<int, Token::Color> indexWithColor;
		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if (tokens[i][j].getUsage() == Token::Usage::Playground) //|| (field[i][j].location == "HandToPlayground"))
			{
				indexWithColor[j] = (Token::Color) tokens[i][j].getColor(); //increase number of fields with same color
			}
		}

		std::map<Token::Color, int> repeated;
		for (std::map<int, Token::Color>::iterator it = indexWithColor.begin(); it != indexWithColor.end(); ++it)
		{
			repeated[it->second] = repeated[it->second]++;
		}

		if (repeated.size() > 2)
		{
			std::vector<int> newGroup;
			for (std::map<Token::Color, int>::iterator it = repeated.begin(); it != repeated.end(); ++it)
			{
				if (it->second > 1)
				{
					//find out repeated keys to add
					for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++it) {
						if (repeated[iter->second] == it->first) //gleiche Farbe
						{
							newGroup.push_back(iter->first);
							repeated[iter->second]--;
							break;
						}
					}
				}
			}
		}
	}
}

Token::Token(Token::Color newColor, int newValue, Token::Usage currentLocation, std::string currentPosition)
{
	color = newColor;
	value = newValue;
	usage = currentLocation;
	position = currentPosition;
}

std::string Token::getTerminalColor()
{
	switch (color) {
	case BLUE:
		return BLUE_TERMINAL_COL;
	case RED:
		return RED_TERMINAL_COL;
	case GREEN:
		return GREEN_TERMINAL_COL;
	case YELLOW:
		return YELLOW_TERMINAL_COL;
	case JOKER_WHITE:
		return JOKER_WHITE_TERMINAL_COL;
	}
	//Fehlerfall
	return RESET_TERMINAL_COL;
}

Token::Color& Token::getColor()
{
	return color;
}

int& Token::getValue()
{
	return value;
}

Token::Usage& Token::getUsage()
{
	return usage;
}

std::string& Token::getPosition()
{
	return position;
}

void Token::setColor(Token::Color newColor)
{
	color = newColor;
}

void Token::setValue(int newValue)
{
	value = newValue;
}

void Token::setUsage(Usage newUsage)
{
	usage = newUsage;
}

void Token::setPosition(std::string newPosition)
{
	position = newPosition;
}
