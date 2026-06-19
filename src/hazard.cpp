#include "hazard.h"

#include "map.h"
#include "player.h"

#include <iostream>
#include <random>

void Wumpus::scare(const Map& gameMap)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> chance_dist(1, 100);

	int roll = chance_dist(gen);

	if (roll <= 75)
	{
		const auto& neighbors = gameMap.getNeighborRooms(m_hazardPos);
		std::uniform_int_distribution<int> neighbor_dist(0, neighbors.size() - 1);
		int randomRoom = neighbor_dist(gen);
		m_hazardPos = neighbors[randomRoom];
	}
}

bool Wumpus::applyEffect()
{
	std::cout << "TSK TSK TSK - WUMPUS GOT YOU!\n";
	std::cout << "HA HA HA - YOU LOSE!\n";
	return false;

}

bool Bat::applyEffect(Player& player)
{
	std::cout << "ZAP! SUPER BATS SNATCH YOU AWAY TO A NEW ROOM!\n";

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 20);

	int randomRoom = dist(gen);
	player.setPos(randomRoom);

	return true;
}

bool Pit::applyEffect()
{
	std::cout << "YYYIIIIEEEE... YOU FELL INTO A PIT! GAME OVER.\n";
	std::cout << "HA HA HA - YOU LOSE!\n";
	return false;
}
