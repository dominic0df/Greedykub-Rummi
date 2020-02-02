#pragma once
#include <iostream>
#include "computerOpponent.h"

void setStartingCondition(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);
void printResult(std::vector<std::vector<Token>>& result, bool pcOpponentSuccessfull);

void testFindAGroupOfDifferentValidUsages(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);
void testFindRowsWithoutShift(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);
void testFindRowsByShiftingBetweenTwoRowsOfSameColor(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);
void testFindRowsByShiftingBetweenTwoRowsOfSameColorWithJoker(std::vector<std::vector<Token>>& tokens, Token& joker1, Token& joker2);