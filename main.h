#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <set>
#include <time.h>
#include <algorithm>
#include <regex>
#include "shared.h"

int main();

void startGame();

void dealTokens(std::vector<playerAdministration>& score, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

int determineIndexPlayerToStart(std::vector<playerAdministration>& score);

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

std::vector<Token>& getTokensOfPlayer(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage player);

void showTokensOfPlayer(std::vector<Token> tokensOfPlayer, std::string nameOfHumanPlayer);

void drawTokenRandomlyFromStock(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2,
	Token::Usage drawingPlayer, int amountOfTokens);

void printMemoryStructure(std::vector<std::vector<Token>>& currentPlayground);

void printToken(Token token);

bool validateGameLineUp(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, Token::Usage player, std::vector<Token>& tokensOfPlayerBeforeManipulations);

void saveGameLineUp(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2,
	std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, Token::Usage player);

void saveCurrentPlayground(std::vector<std::vector<Token>>& currentPlayground, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void saveTokensOfPlayer(std::vector<Token>& tokensOfPlayer, std::vector<std::vector<Token>>& tokens, Token::Usage player, Token& joker1, Token& joker2);

void regexTester();

void processCommandInput(std::string& command, Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer,
	std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void splitCommandMoveSingleToken(std::string& command, int& fromRow, int& fromColumn, int& toRow, int& toColumn);

void getRowAndColumnOfCommandEntry(std::string& commandEntry, int& row, int& column);

void moveToken(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toRow, int& toColumn);

bool basicValidationOfRowAndColumn(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toRow, int& toColumn);

void moveTokenOnBoard(std::vector<Token>& tokensOfPlayer, int& fromColumn, int& toColumn);

void moveTokenPlaygroundToBoard(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromRow, int& fromColumn, int& toColumn);

void moveTokenBoardToPlayground(std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer, int& fromColumn, int& toRow, int& toColumn);

void moveTokenOnPlayground(std::vector<std::vector<Token>>& currentPlayground, int& fromRow, int& fromColumn, int& toRow, int& toColumn);

//void deleteTokenAndMoveElementsLeft(std::vector<Token>& tokensOfPlayer, int& columnOfElementToDelete);

void insertTokenAndMoveElementsRight(std::vector<Token>& tokensOfPlayer, int columnOfElementToInsert, int toColumn);

void insertTokenAndMoveElementsLeft(std::vector<Token>& tokensOfPlayer, int columnOfElementToInsert, int toColumn);

void setValuesOfAnotherToken(Token& toBeModified, Token& toBeCopied);

void swapValuesOfTwoTokens(Token& token1, Token& token2);

std::vector<std::vector<Token>> getPlaygroundToDisplay();