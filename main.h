#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <time.h>
#include "shared.h";

const std::string ERROR_OCCURRED = "Ein Fehler im Programm ist aufgetreten!";
const std::string WELCOME = "Herzlich Willkommen bei Rummikub!";
const std::string MESSAGE_PLAYER_TO_START = "Folgender Spieler darf das Spiel beginnen: ";

const int NUMBER_OF_ROWS = 8;
const int NUMBER_OF_COLUMNS = 13;
const int VALUE_OF_JOKER = 30;
const int TOTAL_AMOUNT_OF_TOKEN = 106;
const int AMOUNT_OF_TOKENS_TO_DRAW_BEGINNING = 14;
const std::string RESET_TERMINAL_COL = "\033[0m";

int main();

//void startGame();

void startGame();

int determineIndexPlayerToStart(std::vector<scoreEntry>& score);

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void drawTokenRandomlyFromStock(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, Token::Usage drawingPlayer, int amountOfTokens);

void printMemoryStructure(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

void printToken(Token token);

void searchForGroups(std::vector<std::vector<Token>>& tokens);