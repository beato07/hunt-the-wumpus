#include "player.h"

#include "map.h"
#include "hazard.h"

#include <iostream>

bool Player::tryShoot(const Map& gameMap, Wumpus& wumpus)
{
	int roomId = 0;
	do
	{
		std::cout << "ROOM #? ";
		std::cin >> roomId;
	} while (!gameMap.areConnected(m_playerPos, roomId));

	if (m_arrowsCount == 0)
	{
		std::cout << "HA HA HA - YOU LOSE!\n";
		return false;
	}

	--m_arrowsCount;
	
	if (roomId == wumpus.getPos())
	{
		std::cout << "AHA! YOU GOT THE WUMPUS!\n";
		return false;
	}
	else
	{
		std::cout << "MISSED\n";
		wumpus.scare(gameMap);

		if (m_playerPos == wumpus.getPos())
		{
			std::cout << "TSK TSK TSK- WUMPUS GOT YOU!";
			return false;
		}

		return true;
	}
}

bool Player::tryMove(const Map& gameMap)
{
	int roomId = 0;
	do
	{
		std::cout << "WHERE TO? ";
		std::cin >> roomId;
	} while (!gameMap.areConnected(m_playerPos, roomId));

	m_playerPos = roomId;

	return true;
}