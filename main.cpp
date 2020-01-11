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

			//std::cout << std::endl << "Pos.:" << positionOfToken;
			if (positionOfToken == 104 && joker1.getUsage() == Token::Usage::Stock) {
				joker1.setUsage(player);
				joker1.setPosition(std::to_string(token));
				//printToken(joker1);
				break;
			}
			else if (positionOfToken == 105 && joker2.getUsage() == Token::Usage::Stock) {
				joker2.setUsage(player);
				joker2.setPosition(std::to_string(token));
				//printToken(joker2);
				break;
			}
			else if (positionOfToken < 104 && tokens[rowOfToken][columnOfToken].getUsage() == Token::Usage::Stock) {
				tokens[rowOfToken][columnOfToken].setUsage(player);
				tokens[rowOfToken][columnOfToken].setPosition(std::to_string(token));
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

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	for (int color = 0; color < 4; color++)
	{
		std::vector<Token> toAdd;
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			Token::Color c = (Token::Color) color;
			//std::cout << c << std::endl;
			Token token(c, column + 1, Token::Usage::Stock, "");
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

int main()
{
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	setStartingCondition(tokens, joker1, joker2);
	printMemoryStructure(tokens, joker1, joker2);
	std::vector<std::vector<std::map < Token::Color, int >>> x = searchForGroups(tokens);
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
}

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2)
{
	for (int color = 0; color < 4; color++)
	{
		std::vector<Token> toAdd;
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
		{
			Token::Color c = (Token::Color) color;
			//std::cout << c << std::endl;
			Token token(c, column + 1, Token::Usage::Playground, "");
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

/*std::vector<Token> void searchForGroups(std::vector<std::vector<Token>> &tokens)
{
	Token::Color color;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		std::map<int, Token::Color> indexWithColor;
		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if (tokens[i][j].getUsage() == Token::Usage::Playground) //|| (field[i][j].location == "HandToPlayground"))
			{
				indexWithColor[j] = (Token::Color)tokens[i][j].getColor(); //increase number of fields with same color
			}
		}

		//speichere alle sich wiederholenden Farben der Spalte ab
		std::map<Token::Color, int> repeated;
		for (std::map<int, Token::Color>::iterator it = indexWithColor.begin(); it != indexWithColor.end(); ++it)
		{
			repeated[it->second] = repeated[it->second]++;
		}
		std::vector<std::vector<int>> foundedGroups;
		while (repeated.size() > 2)
		{
			std::vector<int> newGroup;
			while (newGroup.size() < 4)
			{
				//füge doppelte zu Gruppe hinzu
				for (std::map<Token::Color, int>::iterator it = repeated.begin(); it != repeated.end(); ++it)
				{
					//if (it->second > 1)
					if (it->second > 0)
					{
						//find out repeated keys to add
						for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++it)
						{
							if (repeated[iter->second] == it->first) //gleiche Farbe
							{
								newGroup.push_back(iter->first);
								repeated[iter->second]--;
								if (it->second==0)
								{
									repeated.erease(iter);
								}
								break; //farbe muss nicht weiter gesucht werden, schon vorhanden
							}
						}
					}
				}
			}
			foundedGroups.add(newGroup);
		}
		//versuche restliche elemente zu bestehenden gruppen hinzuzufügen
		int indexOfGroups=0;
		bool successfull=true;
		while (repeated.size()>0 && successfull)
		{
			for (int i = 0; i < repeated.size(); i++)
			{

			}
			for (std::vector<std::vector<int>>::iterator i = foundedGroups.begin(); iter != foundedGroups.end(); ++it)
			{

			}
		}

		}


	}
}*/

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
				if (foundGroups.size()==1)
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
						if (newGroup->size()==0 && nextGroup->size()>0)
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
								if (size==0)
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
				newGroup=nullptr;
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

Token::Token(Token::Color newColor, int newValue, Token::Usage currentLocation, std::string currentPosition)
{
	color = newColor;
	value = newValue;
	usage = currentLocation;
	position = currentPosition;
}

std::string Token::getTerminalColor()
{
	switch (color)
	{
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
