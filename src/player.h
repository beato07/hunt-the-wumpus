#pragma once
#include "map.h"
#include "hazard.h"

class Player
{
public:
	int getPos() { return m_playerPos; }
	void setPos(int newPlayerPos) { m_playerPos = newPlayerPos; }
	bool tryShoot();
	bool tryMove();

private:
	Map m_gameMap;
	Wumpus m_wumpus;
	int m_playerPos{ 0 };
	int m_arrowsCount{ 5 };
};
