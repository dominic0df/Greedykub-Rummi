#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>

//general constant
const std::string UNAVAILABLE_OPTION_CHOOSED = "Fehlerhafte Eingabe! Bitte waehlen sie eine der drei Optionen!";
const std::string AVAILABLE_OPTIONS = "Deine Optionen:";
const std::string QUIT_GAME = "0:\t Verlassen des Spiels";
const std::string SHOW_MANUAL = "1:\t Spielanleitung einsehen";

//first select menu constants
const std::string START_GAME = "2:\t Spiel starten";

//player setting constants
const std::string INSTRUCTION_NUMBER_OF_OPPONENTS = "Gebe deine favorisierte Anzahl an Gegenspielern ein (1-3): ";
const std::string INSTRUCTION_ENTER_NAME = "Gebe deinen Namen ein: ";

int showFirstSelectMenu();

std::string requestNameOfPlayer();
int requestNumberOfOpponents();