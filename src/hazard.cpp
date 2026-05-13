#include "hazard.h"
#include "map.h"
#include <iostream>

void Bat::carryPlayer(Map& gameMap, int& playerPos)
{
	playerPos = gameMap.getRandomRoom();
	do
	{
		m_hazardPos = gameMap.getRandomRoom();
	} while (m_hazardPos == playerPos);
}

bool Pit::isFallen()
{
	std::cout << "YYYIIIIEEEE . . . FELL IN PIT\n";
	return true;
}
