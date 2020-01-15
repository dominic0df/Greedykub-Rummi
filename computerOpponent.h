#include "shared.h"
#include "main.h"
#include <vector>
#include <memory>
#include <map>
#include <set>


void addColorsToGroupThatExistTwice(std::map<Token::Color, int>& numberOfEachColor, std::shared_ptr<std::map<Token::Color, int>>& newGroup, std::shared_ptr<std::map<Token::Color, int>>& nextGroup, std::map<int, Token::Color>& indexWithColor, std::set<int>& processed, int& numberOfRemainingColors, std::vector<std::map<Token::Color, int>>& foundGroups);
void addColorsToGroupsOfSize3(int& numberOfRemainingColors, std::vector<std::map<Token::Color, int>>& foundGroups, std::map<int, Token::Color>& indexWithColor, std::set<int>& processed);
bool& checkIfOnlyRepeatedElementsAreRemaining(std::map<int, Token::Color>& indexWithColor, bool& notEqual);
void addColorToGroupIfNotProcessed(std::shared_ptr<std::map<Token::Color, int>>& newGroup, std::map<int, Token::Color>::iterator& iter, std::set<int>& processed, int& numberOfRemainingColors, std::vector<std::map<Token::Color, int>>& foundGroups, std::shared_ptr<std::map<Token::Color, int>>& nextGroup);
int& getSizeOfNewGroup(std::shared_ptr<std::map<Token::Color, int>>& newGroup, int& size);
void identifyColorByIndexWithCorrectUsageOneColumn(std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, int i, std::map<int, Token::Color>& indexWithColor);
bool searchForGroups(std::vector<std::vector<Token>>& tokens, std::vector<std::vector<std::map < Token::Color, int >>>& foundGroupsAllColumns, std::vector<Token::Usage>& usageConditions);

int& getValueToShiftBetweenTwoRows(int i, int& shift);
bool checkSuccessOfSearchForRowsByUsage(std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<bool>>& processed);
int& getSizeOfRow(std::shared_ptr<std::vector<Token>>& row, int& size);
bool pushTokenToRowUntilRowSize3(std::vector<std::vector<Token>>& tokens, int i, int shift, int j, std::vector<Token::Usage>& usageConditions, int condition, std::vector<std::vector<bool>>& processed, int size, std::shared_ptr<std::vector<Token>>& row, std::vector<std::vector<Token>>& foundRows);
void findRemainingTokensToAddShift(std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<bool>>& processed, std::vector<std::vector<std::vector<Token>>>& foundRowsAllColors);
void findRemainingTokensToAddWithoutShift(std::vector<std::vector<bool>>& processed, int i, std::vector<Token::Usage>& usageConditions, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<Token>>& foundRows);
void correctFalseInputToProcessedAndPush(std::shared_ptr<std::vector<Token>>& row, std::vector<std::vector<bool>>& processed, int i, std::vector<std::vector<Token>>& foundRows);
bool searchForRows(std::vector<std::vector<Token>>& tokens, std::vector<std::vector<bool>>& processed, std::vector<std::vector<std::vector<Token>>>& foundRowsAllColors, std::vector<Token::Usage>& usageConditions);

bool searchForGroupsAndRows(std::vector<std::vector<Token>>& tokens, std::vector<std::vector<Token>>& result, std::vector<Token::Usage>& usageConditions, Token& joker1, Token& joker2);

void concatinateResultsToASingleStructure(std::vector<std::vector<std::vector<Token>>>& rows, std::vector<std::vector<Token>>& result, std::vector<std::vector<std::map<Token::Color, int>>>& groups, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, std::vector<Token::Usage>& usageConditions);

bool handlingOfCollisionsBetweenGroupsAndRows(std::vector<std::vector<bool>>& processed, std::vector<std::vector<std::map<Token::Color, int>>>& groups, std::vector<std::vector<Token>>& tokens, std::vector<std::vector<std::vector<Token>>>& rows);

bool makeAMoveComputerOpponent(std::vector<std::vector<Token>>& tokens, std::vector<std::vector<Token>>& result, std::vector<Token::Usage>& usageConditions, Token& joker1, Token& joker2);
