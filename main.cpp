#include "main.h"

int main()
{
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	Token joker2(Token::Color::JOKER_WHITE, VALUE_OF_JOKER, Token::Usage::Stock, "");
	setStartingCondition(tokens, joker1, joker2);
	printMemoryStructure(tokens, joker1, joker2);
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
                    for(std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++it){
                        if (repeated[iter->second]==it->first) //gleiche Farbe
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