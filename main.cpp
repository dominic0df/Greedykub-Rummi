#include "main.h"

int main()
{
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	setStartingCondition(tokens, joker1, joker2);
	printMemoryStructure(tokens, joker1, joker2);
	std::vector<std::vector<std::vector<int>>> x = searchForGroups(tokens);
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

void testSearchForGroups(std::vector<std::vector<std::vector<int>>> x, std::vector<std::vector<Token>> tokens)
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

std::vector<std::vector<std::vector<int>>> searchForGroups(std::vector<std::vector<Token>>& tokens)
{
	Token::Color color;
	std::vector<std::vector<std::vector<int>>> foundedGroupsAllColumns;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		std::vector<std::vector<int>> foundedGroups;
		std::map<int, Token::Color> indexWithColor;
		for (int j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if (tokens[j][i].getUsage() == Token::Usage::Playground) //|| (field[i][j].location == "HandToPlayground"))
			{
				indexWithColor[j] = (Token::Color) tokens[j][i].getColor(); //increase number of fields with same color
			}
		}

		//speichere alle sich wiederholenden Farben der Spalte ab
		int numberOfRemainingColors = indexWithColor.size();
		bool notEqual = true;
		while (numberOfRemainingColors > 2 && notEqual)
		{
			std::vector<int>* newGroup;
			std::vector<int> group;
			newGroup = &group;
			//find out repeated keys to add
			for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
			{
				if (newGroup->size()!=0) {
					for (int groupElement = 0; groupElement < newGroup->size(); ++groupElement)
					{
						if (indexWithColor[iter->first] != indexWithColor[groupElement]) //gleiche Farbe
						{
							newGroup->push_back(iter->first);
							numberOfRemainingColors--;
							indexWithColor.erase(iter);
							if (newGroup->size() == 3)
							{
								foundedGroups.push_back(*newGroup);
								std::vector<int> nextGroup;
								newGroup = &nextGroup;
							}
						}
					}
				}
				else {
					newGroup->push_back(iter->first);
					numberOfRemainingColors--;
					//indexWithColor.erase(iter);
				}
			}
			//delete newGroup;
			if (numberOfRemainingColors < 5)
			{
				std::map<Token::Color, int> repeated;
				for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
				{
					repeated[iter->second] = repeated[iter->second]++;

				}
				if (repeated.size() < 3)
				{
					notEqual = false;
				}
			}

		}
		/*int indexOfFoundedGroups = foundedGroups.size() - 1;
		while (numberOfRemainingColors != 0 && indexOfFoundedGroups >= 0)
		{
			for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
			{
				for (int color = 0; color < foundedGroups[indexOfFoundedGroups].size(); color++)
				{

					//for (std::vector<int>::iterator color = foundedGroups[indexOfFoundedGroups].begin(); color != foundedGroups[indexOfFoundedGroups].end(); ++color){

					if (indexWithColor[iter->second] != tokens[color][i].getColor())
					{
						foundedGroups[indexOfFoundedGroups].push_back(color);
						indexWithColor.erase(iter);
						--numberOfRemainingColors;
					}
				}
			}
			++indexOfFoundedGroups;
		}*/
		foundedGroupsAllColumns.push_back(foundedGroups);
	}
	return foundedGroupsAllColumns;
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
