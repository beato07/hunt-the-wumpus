#pragma once
#include "map.h"
#include "player.h"
#include "hazard.h"

class Game
{
public:
	Game();

private:
	Map m_gameMap;

	Player m_player;

	Bat m_bat1;
	Bat m_bat2;
	Pit m_pit1;
	Pit m_pit2;

	void setupEntities();
};
