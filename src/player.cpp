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
		std::cout << "There is nothing here...\n";
		return true;
	}

	//std::cout << "TSK TSK TSK- WUMPUS GOT YOU!";
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