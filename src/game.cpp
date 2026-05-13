#include "game.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

Game::Game()
{
	setupEntities();
}

void Game::setupEntities()
{
	std::vector<int> rooms(20);
	std::iota(rooms.begin(), rooms.end(), 1);

	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::shuffle(rooms.begin(), rooms.end(), gen);

	m_player.setPos(rooms.at(0));
	m_bat1.setPos(rooms.at(1));
	m_bat2.setPos(rooms.at(2));
	m_pit1.setPos(rooms.at(3));
	m_pit2.setPos(rooms.at(4));
}
