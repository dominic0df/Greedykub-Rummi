#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include "shared.h"

void firstUserInteraction();

void setPlayerInformation(std::vector<playerAdministration>& score);

void addPlayer(std::vector<playerAdministration>& playerMemory, Token::Usage player, std::string nameOfHumanPlayer);

void makeMovePlayer(Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, std::vector<Token>& tokensOfPlayer,
	bool& gameOn, bool& roundOn, std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2, bool& tokenDrawn);

bool isNumber(const std::string& s);

void showCommandSet();