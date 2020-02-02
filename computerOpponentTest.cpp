#include "computerOpponentTest.h"

int main()
{
    //initialize test values
	std::vector<std::vector<Token>> tokens;
	Token joker1(Token::Color::JOKER_WHITE, 1, Token::Usage::Stock, -1, -1, -1, -1, -1);
	Token joker2(Token::Color::JOKER_WHITE, 2, Token::Usage::Stock, -1, -1, -1, -1, -1);
	std::vector<std::vector<Token>> result;
	setStartingCondition(tokens, joker1, joker2);
	std::vector<Token::Usage> usageConditions;
	usageConditions.push_back(Token::Usage::Playground);
	usageConditions.push_back(Token::Usage::PC_Player_1);

	// please comment and uncomment the test cases, the result is print to the command line

	//testFindRowsWithoutShift(tokens, joker1, joker2);
	//testFindRowsByShiftingBetweenTwoRowsOfSameColor(tokens, joker1, joker2);
	//testFindAGroupOfDifferentValidUsages(tokens, joker1, joker2);
	testFindRowsByShiftingBetweenTwoRowsOfSameColorWithJoker(tokens, joker1, joker2);

	bool pcOpponentSuccessfull = makeAMoveComputerOpponent(tokens, result, usageConditions, joker1, joker2);
	printResult(result, pcOpponentSuccessfull);
}

// Result: values 2,4,6 with different colors
void testFindAGroupOfDifferentValidUsages(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {
	tokens[1][11].setUsage(Token::Usage::PC_Player_1);
	tokens[3][11].setUsage(Token::Usage::Playground);
	tokens[5][11].setUsage(Token::Usage::PC_Player_1);
}

// Result: values 10,11,12,13 with same color
void testFindRowsWithoutShift(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {
	tokens[0][9].setUsage(Token::Usage::PC_Player_1);
	tokens[0][10].setUsage(Token::Usage::Playground);
	tokens[0][11].setUsage(Token::Usage::Playground);
	tokens[0][12].setUsage(Token::Usage::PC_Player_1);
}

// Result: values 10,11,12,13 with same color
// Test indicates also that the value 8 is not included
void testFindRowsByShiftingBetweenTwoRowsOfSameColor(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {
	tokens[4][7].setUsage(Token::Usage::PC_Player_1);

	tokens[4][9].setUsage(Token::Usage::PC_Player_1);
	tokens[5][10].setUsage(Token::Usage::Playground);
	tokens[4][11].setUsage(Token::Usage::Playground);
	tokens[4][12].setUsage(Token::Usage::PC_Player_1);
}

// Result: values 10,11,12, a value that needs not to be 13
// the value of jokers will be changed after validation
void testFindRowsByShiftingBetweenTwoRowsOfSameColorWithJoker(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2) {
	tokens[4][9].setUsage(Token::Usage::PC_Player_1);
	tokens[5][10].setUsage(Token::Usage::Playground);
	tokens[4][11].setUsage(Token::Usage::Playground);
	joker1.setUsage(Token::Usage::Playground);
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

void printResult(std::vector<std::vector<Token>>& result, bool pcOpponentSuccessfull) {
	for (int groupOrRow = 0; groupOrRow < result.size(); groupOrRow++)
	{
		std::cout << "Gefundene Kombination (Gruppe oder Reihe): " << std::endl;
		for (int groupOrRowElement = 0; groupOrRowElement < result[groupOrRow].size(); groupOrRowElement++)
		{
			std::cout << "Row: " << result[groupOrRow][groupOrRowElement].getRow()
				<< ", Column: " << result[groupOrRow][groupOrRowElement].getColumn()
				<< ", Value: " << result[groupOrRow][groupOrRowElement].getValue()
				<< ", Color: " << (Token::Color) result[groupOrRow][groupOrRowElement].getColor() << std::endl;
		}
	}
	std::cout << "Resultat ausgegeben, Spielfeld wieder komplett zusammengefuegt: " 
		<< pcOpponentSuccessfull << '\n' 
		<< "Bei false wird Ergebnis verworfen und der PC-Gegner muss ziehen, bei true wird die aktuelle Aufstellung verwendet, falls auch die Validierung erfolgreich ist." << std::endl;
}
