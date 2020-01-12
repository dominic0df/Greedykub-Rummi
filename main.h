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

const std::string ERROR_OCCURRED = "Ein Fehler im Programm ist aufgetreten!";
const std::string WELCOME = "Herzlich Willkommen bei Rummikub!";
const std::string MESSAGE_PLAYER_TO_START = "Folgender Spieler darf das Spiel beginnen: ";
const std::string BOARD_FILLED = "Dein Brett ist voll -> du kannst keine neuen Spielsteine mehr aufnehmen. Lege Spielsteine auf dem Spielfeld ab!";

const int VALUE_OF_JOKER = 30;
const int TOTAL_AMOUNT_OF_TOKEN = 106;
const int AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING = 14;

int main();

//void startGame();

void startGame();

void dealTokens(std::vector<scoreEntry>& score, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

int determineIndexPlayerToStart(std::vector<scoreEntry>& score);

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

std::vector<Token> getTokensOfPlayer(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage player);

void showTokensOfPlayer(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage player);

void drawTokenRandomlyFromStock(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2,
	Token::Usage drawingPlayer, int amountOfTokens);

void printMemoryStructure(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void printToken(Token token);

std::vector<std::vector<std::map < Token::Color, int >>> searchForGroups(std::vector<std::vector<Token>>& tokens);

void testSearchForGroups(std::vector<std::vector<int>>& x, std::vector<std::vector<Token>>& tokens);

void regexTester();

void processCommandInput(std::string& command, Token::Usage player, std::vector<std::vector<Token>>& currentPlayground,
	std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void splitCommandMoveSingleToken(std::string& command, int& fromRow, int& fromColumn, int& toRow, int& toColumn);

void getRowAndColumnOfCommandEntry(std::string& commandEntry, int& row, int& column);

void moveToken(int& fromRow, int& fromColumn, int& toRow, int& toColumn);

std::vector<std::vector<Token>> getPlaygroundToDisplay();