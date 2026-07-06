#include "player.h"

#include "map.h"
#include "hazard.h"

#include <iostream>
#include<limits>

bool Player::tryShoot(const Map& gameMap, Wumpus& wumpus)
{
	int roomNumber = 0;
	while (true)
	{
		std::cout << "ROOM #? ";
		std::cin >> roomNumber;
		
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (gameMap.areConnected(m_playerPos, roomNumber))
		{
			break;
		}
	}

	--m_arrowsCount;
	
	if (roomNumber == wumpus.getPos())
	{
		std::cout << "AHA! YOU GOT THE WUMPUS!\n";
		return false;
	}
	
	if (gameMap.areConnected(roomNumber, wumpus.getPos()))
	{
		std::cout << "MISSED\n";
		wumpus.scare(gameMap);
	}
	else
	{
		std::cout << "MISSED\n";
	}

	if (m_playerPos == wumpus.getPos())
	{
		std::cout << "TSK TSK TSK- WUMPUS GOT YOU!\n";
		return false;
	}

	if (m_arrowsCount == 0)
	{
		std::cout << "HA HA HA - YOU LOSE!\n";
		return false;
	}

	return true;
}

bool Player::tryMove(const Map& gameMap)
{
	int roomNumber = 0;
	while (true)
	{
		std::cout << "WHERE TO? ";
		std::cin >> roomNumber;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (gameMap.areConnected(m_playerPos, roomNumber))
		{
			break;
		}
	}

	m_playerPos = roomNumber;

	return true;
}