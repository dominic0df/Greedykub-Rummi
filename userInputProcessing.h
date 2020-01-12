#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include "shared.h"

void firstUserInteraction();

void setPlayerInformation(std::vector<scoreEntry>& score, std::string& nameOfHumanPlayer);

void makeMovePlayer(Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, bool& gameOn,
	std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);

bool isNumber(const std::string& s);