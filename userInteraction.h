#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>

//general constant
const std::string UNAVAILABLE_OPTION_CHOOSED = "Fehlerhafte Eingabe! Bittw waehle eine der drei Optionen!";
const std::string AVAILABLE_OPTIONS = "Deine Optionen:";
const std::string QUIT_GAME = "0:\t Verlassen des Spiels";
const std::string SHOW_MANUAL = "1:\t Spielanleitung anzeigen";
const std::string INSTRUCTION_ENTER_OPTION = "Deine Eingabe: ";

//first select menu constants
const std::string START_GAME = "2:\t Spiel starten";

//player setting constants
const std::string UNAVAILABLE_NUMBER_CHOOSED = "Fehlerhafte Eingabe! Die Anzahl muss zwischen 0 und 3 liegen!";
const std::string NOT_ENOUGH_OPPONENTS_CHOOSED = "-> Fehlerhafte Eingabe! Du brauchst MINDESTENS 1nen Gegegnspieler!";
const std::string TOO_MANY_OPPONENTS_CHOOSED = "-> Fehlerhafte Eingabe! Du kannst gegen MAXIMAL 3 Gegenspieler antreten!";
const std::string INSTRUCTION_NUMBER_OF_HUMAN_OPPONENTS = "Gebe deine favorisierte Anzahl an menschlichen Gegenspielern ein (0-3): ";
const std::string INSTRUCTION_NUMBER_OF_PC_OPPONENTS = "Gebe deine favorisierte Anzahl an PC-basierten Gegenspielern ein (0-3): ";
const std::string ENTER_NAME = "Name: ";

//move menu constants
const std::string SHOW_COMMANDS = "2:\t Befehlssatz anzeigen";
const std::string DRAW_TOKEN = "3:\t Spielstein ziehen";
const std::string CONTINUE = "4:\t Spielzug beenden";
const std::string REPAIR_PLAYGROUND = "5:\t Spielfeld zuruecksetzen";
const std::string MOVE_TOKEN = "ODER gebe einen Befehl zum Verschieben eines Spielsteins an";

int showFirstSelectMenu();

std::string requestNameOfPlayer();
void requestNumberOfOpponents(int& numberOfHumanOpponents, int& numberOfPcOpponents);

void requestNumberOfHumanOpponents(int& numberOfHumanOpponents);

void requestNumberOfPcOpponents(int& numberOfPcOpponents);

bool validateInputNumberOfOpponents(std::string& numberOfOpponents);

std::string showSelectMenuMove();

void showCommandSet();

void showGameManual();


