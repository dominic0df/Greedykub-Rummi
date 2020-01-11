#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include "shared.h"

void firstUserInteraction();

void setPlayerInformation(std::vector<scoreEntry>& score, std::string& nameOfHumanPlayer);

void makeMovePlayer(Token::Usage player, std::vector<std::vector<Token>>& currentPlayground, bool& gameOn);

bool isNumber(const std::string& s);