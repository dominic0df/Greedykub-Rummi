#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <map>

//general constant
const std::string UNAVAILABLE_OPTION_CHOOSED = "Fehlerhafte Eingabe! Bitte waehlen sie eine der drei Optionen!";
const std::string AVAILABLE_OPTIONS = "Deine Optionen:";
const std::string QUIT_GAME = "0:\t Verlassen des Spiels";
const std::string SHOW_MANUAL = "1:\t Spielanleitung anzeigen";
const std::string INSTRUCTION_ENTER_OPTION = "Deine Eingabe: ";

//first select menu constants
const std::string START_GAME = "2:\t Spiel starten";

//player setting constants
const std::string INSTRUCTION_NUMBER_OF_OPPONENTS = "Gebe deine favorisierte Anzahl an Gegenspielern ein (1-3): ";
const std::string INSTRUCTION_ENTER_NAME = "Gebe deinen Namen ein: ";

//move menu constants
const std::string SHOW_COMMANDS = "2:\t Befehlssatz anzeigen";
const std::string DRAW_TOKEN = "3:\t Spielstein ziehen";
const std::string CONTINUE = "4:\t Spielzug beenden";
const std::string REPAIR_PLAYGROUND = "5:\t Spielfeld zuruecksetzen";
const std::string MOVE_TOKEN = "ODER gebe einen Befehl zum Verschieben einer Karte an";

int showFirstSelectMenu();

std::string requestNameOfPlayer();
int requestNumberOfOpponents();

std::string showSelectMenuMove();



