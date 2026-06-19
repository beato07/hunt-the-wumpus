#pragma once

#include "hazard.h"
#include "map.h"
#include "player.h"

class Game {
public:
	Game();
	void resetToInitialSetup();
	void run();

private:
	Map m_gameMap;
	Player m_player;
	Wumpus m_wumpus;
	Bat m_bat1;
	Bat m_bat2;
	Pit m_pit1;
	Pit m_pit2;

	int m_initialPlayerPos{ 0 };
	int m_initialWumpusPos{ 0 };
	int m_initialBat1Pos{ 0 };
	int m_initialBat2Pos{ 0 };
	int m_initialPit1Pos{ 0 };
	int m_initialPit2Pos{ 0 };

	void setupEntities();
	void askForInstructions();
	void printRules();
	void printWarnings();
	void printRoomInfo();
	bool handlePlayerTurn();
	bool checkHazards();
};
