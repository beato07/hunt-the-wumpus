#include "player.h"
#include <iostream>

bool Player::tryShoot()
{
	int roomId = 0;
	do
	{
		std::cout << "ROOM #? ";
		std::cin >> roomId;
	} while (!m_gameMap.areConnected(m_playerPos, roomId));

	if (m_arrowsCount == 0)
	{
		std::cout << "HA HA HA - YOU LOSE!\n";
		return false;
	}

	--m_arrowsCount;

	if (roomId == m_wumpus.getPos())
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

bool Player::tryMove()
{
	return false;
}