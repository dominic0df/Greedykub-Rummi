#include "computerOpponent.h"

//umbedingt searchForRows

bool searchForGroupsAndRows(std::vector<std::vector<Token>>& tokens, std::vector<std::vector<Token>>& result) {
	std::vector<Token::Usage> usageConditions = { Token::Usage::Playground, Token::Usage::Player1 };
	std::vector<std::vector<std::map < Token::Color, int >>> groups;
	std::vector<std::vector<bool>> processed(
		NUMBER_OF_ROWS,
		std::vector<bool>(NUMBER_OF_COLUMNS, false));
	std::vector<std::vector<std::vector<Token>>> rows;

	bool allTokensInAGroup = searchForGroups(tokens, groups, usageConditions);
	bool allTokensInARow = searchForRows(tokens, processed, rows, usageConditions);

	bool collisionSolved;
	if (allTokensInAGroup && allTokensInARow)
	{
		collisionSolved = handlingOfCollisionsBetweenGroupsAndRows(processed, groups, tokens, rows);
		if (collisionSolved)
		{
			concatinateResultsToASingleStructure(rows, result, groups, tokens);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		collisionSolved = handlingOfCollisionsBetweenGroupsAndRows(processed, groups, tokens, rows);
		if (collisionSolved)
		{
			concatinateResultsToASingleStructure(rows, result, groups, tokens);
			return true;
		}
		else
		{
			//if (true)
			//{
			//es existiert für jedes nicht enthaltene Element ein anderes Element, dass hinzugefügt werden kann
			//}
			return false;
		}
	}
}

void concatinateResultsToASingleStructure(std::vector<std::vector<std::vector<Token>>>& rows, std::vector<std::vector<Token>>& result, std::vector<std::vector<std::map<Token::Color, int>>>& groups, std::vector<std::vector<Token>>& tokens)
{
	//wird kopiert, kann man das ändern?
	//add rows to result
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		for (int j = 0; j < rows[i].size(); j++) {
			result.push_back(rows[i][j]);
		}
	}
	//add groups to result
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		for (int j = 0; j < groups[i].size(); j++) {
			std::vector<Token> group;
			for (std::map<Token::Color, int>::iterator iter = groups[i][j].begin(); iter != groups[i][j].end(); ++iter)
			{
				group.push_back(tokens[i][iter->second]);
			}
			result.push_back(group);
		}
	}
}

bool handlingOfCollisionsBetweenGroupsAndRows(std::vector<std::vector<bool>>& processed, std::vector<std::vector<std::map<Token::Color, int>>>& groups, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<std::vector<Token>>>& rows)
{
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++) {
		for (int j = 0; j < NUMBER_OF_ROWS; j++) {
			if (processed[j][i])
			{
				for (int groupsOfColumn = 0; groupsOfColumn < groups[i].size(); groupsOfColumn++)
				{
					std::map < Token::Color, int >::iterator it = groups[i][groupsOfColumn].find(tokens[j][i].getColor());
					if (it != groups[i][groupsOfColumn].end())
					{
						if (groups[i][groupsOfColumn].size() == 4)
						{
							groups[i][groupsOfColumn].erase(it);
						}
						else
						{
							for (int row = 0; row < rows[j].size(); row++)
							{
								for (int rowElement = 0; rowElement < rows[j][row].size(); rowElement++)
								{
									if (rows[j][row][rowElement].getValue() == j + 1)//processed again?
									{
										if (rows[j][row].size() > 3)
										{
											if (rowElement == rows[j][row].size() - 1)
											{
												rows[j][row].pop_back();
											}
											else
											{
												if (rowElement == 0 && !rows[j][row].empty())
												{
													//std::swap(rows[j][row][rowElement], rows[j][row][rowElement]);
													//rows[j][row].pop_back();
													//rows[j][row].erase(rows[j][row].begin());
													return false;
												}
												else
												{
													return false;
													//Kollisionsbehandlung schwieriger Fall
													//aus refactoreden Methoden bedienen falls noch Zeit bleibt
												}
											}
										}
										else
										{
											return false;
										}
									}
									else
										return false;
								}
							}
						}
					}
				}
			}
		}

	}
	return true;
}


bool searchForGroups(std::vector<std::vector<Token>>& tokens, std::vector<std::vector<std::map < Token::Color, int >>>& foundGroupsAllColumns, std::vector<Token::Usage>& usageConditions)
{
	int remainingTokens = 0;
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		std::vector<std::map<Token::Color, int>>foundGroups;
		std::map<int, Token::Color> indexWithColor;
		std::map<Token::Color, int> numberOfEachColor;
		std::set<int> processed;
		identifyColorByIndexWithCorrectUsageOneColumn(usageConditions, tokens, i, indexWithColor);
		for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
		{
			numberOfEachColor[iter->second] = numberOfEachColor[iter->second] + 1;
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
				int size = getSizeOfNewGroup(newGroup, size);
				if (foundGroups.size() == 1)
				{
					newGroup = nextGroup;
				}
				int sufficientColors = numberOfRemainingColors + size;
				if (sufficientColors > 2)
				{
					if (numberOfRemainingColors == indexWithColor.size())
					{
						addColorsToGroupThatExistTwice(numberOfEachColor, newGroup, nextGroup, indexWithColor, processed, numberOfRemainingColors, foundGroups);
					}
					for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
					{
						if (newGroup->size() == 0 && nextGroup->size() > 0)
						{
							newGroup = nextGroup;
						}
						bool colorWithIndexProcessed = processed.find(iter->first) != processed.end();
						if (!colorWithIndexProcessed) {
							if (newGroup->size() != 0 && newGroup->size() < 3) {
								addColorToGroupIfNotProcessed(newGroup, iter, processed, numberOfRemainingColors, foundGroups, nextGroup);
							}
							else {
								size = getSizeOfNewGroup(newGroup, size);
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
				notEqual = checkIfOnlyRepeatedElementsAreRemaining(indexWithColor, notEqual);
			}
		}
		addColorsToGroupsOfSize3(numberOfRemainingColors, foundGroups, indexWithColor, processed);
		remainingTokens = remainingTokens + numberOfRemainingColors;
		foundGroupsAllColumns.push_back(foundGroups);
	}
	if (remainingTokens == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void addColorsToGroupThatExistTwice(std::map<Token::Color, int>& numberOfEachColor, std::shared_ptr<std::map<Token::Color, int>>& newGroup, std::shared_ptr<std::map<Token::Color, int>>& nextGroup, std::map<int, Token::Color>& indexWithColor, std::set<int>& processed, int& numberOfRemainingColors, std::vector<std::map<Token::Color, int>>& foundGroups)
{
	for (std::map<Token::Color, int>::iterator color = numberOfEachColor.begin(); color != numberOfEachColor.end(); ++color)
	{
		if (newGroup->size() == 0 && nextGroup->size() > 0)
		{
			newGroup = nextGroup;
		}
		if (color->second > 1) {
			std::map<int, Token::Color>::iterator valueToAdd = indexWithColor.find(color->first);
			if (valueToAdd != indexWithColor.end()) {
				bool colorWithIndexProcessed = processed.find(valueToAdd->first) != processed.end();
				if (!colorWithIndexProcessed) {
					addColorToGroupIfNotProcessed(newGroup, valueToAdd, processed, numberOfRemainingColors, foundGroups, nextGroup);
				}
			}
		}
	}
}

void addColorsToGroupsOfSize3(int& numberOfRemainingColors, std::vector<std::map<Token::Color, int>>& foundGroups, std::map<int, Token::Color>& indexWithColor, std::set<int>& processed)
{
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
}

bool& checkIfOnlyRepeatedElementsAreRemaining(std::map<int, Token::Color>& indexWithColor, bool& notEqual)
{
	std::map<Token::Color, int> repeated;
	for (std::map<int, Token::Color>::iterator iter = indexWithColor.begin(); iter != indexWithColor.end(); ++iter)
	{
		repeated[iter->second] = repeated[iter->second]++;
	}
	if (repeated.size() < 3) {
		notEqual = false;
	}
	return notEqual;
}

void addColorToGroupIfNotProcessed(std::shared_ptr<std::map<Token::Color, int>>& newGroup, std::map<int, Token::Color>::iterator& iter, std::set<int>& processed, int& numberOfRemainingColors, std::vector<std::map<Token::Color, int>>& foundGroups, std::shared_ptr<std::map<Token::Color, int>>& nextGroup)
{
	bool colorInNewGroup = newGroup->find(iter->second) != newGroup->end();
	if (!colorInNewGroup)
	{
		processed.insert(iter->first);
		newGroup->insert(std::pair<Token::Color, int>(iter->second, iter->first));
		numberOfRemainingColors--;
		if (newGroup->size() > 2)
		{
			foundGroups.push_back(*newGroup);
			if (numberOfRemainingColors > 2)
			{
				newGroup = nextGroup;
			}
		}
	}
}

int& getSizeOfNewGroup(std::shared_ptr<std::map<Token::Color, int>>& newGroup, int& size)
{
	if (newGroup == nullptr)
	{
		size = 0;
	}
	else {
		size = newGroup->size();
	}
	return size;
}

void identifyColorByIndexWithCorrectUsageOneColumn(std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, int i, std::map<int, Token::Color>& indexWithColor)
{
	for (int j = 0; j < NUMBER_OF_ROWS; j++)
	{
		for (int condition = 0; condition < usageConditions.size(); condition++)
		{
			if (tokens[j][i].getUsage() == usageConditions[condition]) //|| (field[i][j].location == "HandToPlayground"))
			{
				indexWithColor[j] = (Token::Color) tokens[j][i].getColor();
			}
		}
	}
}

//Input: tokens and references for the output. Return value
//Input: tokens and the usage conditions, references for the output. Return value is a success message
bool searchForRows(std::vector<std::vector<Token>>& tokens,
	std::vector<std::vector<bool>>& processed,
	std::vector<std::vector<std::vector<Token>>>& foundRowsAllColors,
	std::vector<Token::Usage>& usageConditions)
{
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		std::vector<std::vector<Token>>foundRows;
		std::shared_ptr<std::vector<Token>> row(new std::vector<Token>());
		std::shared_ptr<std::vector<Token>> firstRow(new std::vector<Token>());
		row = firstRow;
		int shift = getValueToShiftBetweenTwoRows(i, shift);
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			int size = getSizeOfRow(row, size);
			for (int condition = 0; condition < usageConditions.size(); condition++)
			{
				if (!pushTokenToRowUntilRowSize3(tokens, i, 0, j, usageConditions, condition, processed, size, row, foundRows)) {
					pushTokenToRowUntilRowSize3(tokens, i, shift, j, usageConditions, condition, processed, size, row, foundRows);
				}
			}

		}
		correctFalseInputToProcessedAndPush(row, processed, i, foundRows);
		findRemainingTokensToAddWithoutShift(processed, i, usageConditions, tokens, foundRows);
		foundRowsAllColors.push_back(foundRows);
	}
	findRemainingTokensToAddShift(usageConditions, tokens, processed, foundRowsAllColors);
	return checkSuccessOfSearchForRowsByUsage(usageConditions, tokens, processed);
}

void correctFalseInputToProcessedAndPush(std::shared_ptr<std::vector<Token>>& row, std::vector<std::vector<bool>>& processed, int i, std::vector<std::vector<Token>>& foundRows)
{
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
}

void findRemainingTokensToAddWithoutShift(std::vector<std::vector<bool>>& processed, int i, std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<Token>>& foundRows)
{
	int indexOfFoundRow = 0;
	for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
	{
		if (!processed[i][column])
		{
			for (int condition = 0; condition < usageConditions.size(); condition++)
			{
				if (tokens[i][column].getUsage() == usageConditions[condition])
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
	}
}

void findRemainingTokensToAddShift(std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<bool>>& processed, std::vector<std::vector<std::vector<Token>>>& foundRowsAllColors)
{
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		int shift = getValueToShiftBetweenTwoRows(i, shift);
		for (int column = 0; column < NUMBER_OF_COLUMNS; column++) {
			for (int condition = 0; condition < usageConditions.size(); condition++)
			{
				if (tokens[i][column].getUsage() == usageConditions[condition] && !processed[i + shift][column]) {
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
	}
}

bool pushTokenToRowUntilRowSize3(std::vector<std::vector<Token>>& tokens, int i, int shift, int j, std::vector<Token::Usage>& usageConditions, int condition, std::vector<std::vector<bool>>& processed, int size, std::shared_ptr<std::vector<Token>>& row, std::vector<std::vector<Token>>& foundRows)
{
	bool tokenFullfillsCondition = tokens[i + shift][j].getUsage() == usageConditions[condition] && !processed[i + shift][j];
	if (tokenFullfillsCondition) {
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
				else
				{
					if (row->size() == 2)
					{
						processed[i + shift][j - 2] = false;
						processed[i + shift][j - 3] = false;
					}
					else
					{
						if (row->size() == 1)
						{
							processed[i + shift][j - 2] = false;
						}
					}
				}
				std::shared_ptr<std::vector<Token>> nextRow(new std::vector<Token>());
				row = nextRow;
				row->push_back(tokens[i + shift][j]);
				processed[i + shift][j] = true;
			}
		}
		return true;
	}
	return false;
}

int& getSizeOfRow(std::shared_ptr<std::vector<Token>>& row, int& size)
{
	if (row == nullptr)
	{
		size = 0;
	}
	else {
		size = row->size();
	}
	return size;
}

bool checkSuccessOfSearchForRowsByUsage(std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<bool>>& processed)
{
	for (int i = 0; i < NUMBER_OF_ROWS; i++) {
		for (int j = 0; j < NUMBER_OF_COLUMNS; j++) {
			for (int condition = 0; condition < usageConditions.size(); condition++)
			{
				if (tokens[i][j].getUsage() == usageConditions[condition] && !processed[i][j]) {
					return false;
				}
			}
		}
	}
	return true;
}

int& getValueToShiftBetweenTwoRows(int i, int& shift)
{
	if (i % 2 == 0) {
		shift = 1;
	}
	else
	{
		shift = -1;
	}
	return shift;
}