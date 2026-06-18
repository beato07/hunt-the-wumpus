#pragma once
#include "map.h"
#include "player.h"
#include "hazard.h"

class Game {
public:
	Game();
	void run();

private:
	Map m_gameMap;
	Player m_player;
	Wumpus m_wumpus;
	Bat m_bat1;
	Bat m_bat2;
	Pit m_pit1;
	Pit m_pit2;

	void setupEntities();
	void askForInstructions();
	void printRules();
	void printWarnings();
	void printRoomInfo();
	bool handlePlayerTurn();
};
