#include "game.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>

Game::Game()
{
	setupEntities();
}

void Game::setupEntities()
{
	std::vector<int> shuffledRooms(20);
	std::iota(shuffledRooms.begin(), shuffledRooms.end(), 1);

	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::shuffle(shuffledRooms.begin(), shuffledRooms.end(), gen);

	m_player.setPos(shuffledRooms[0]);
	m_wumpus.setPos(shuffledRooms[1]);
	m_bat1.  setPos(shuffledRooms[2]);
	m_bat2.  setPos(shuffledRooms[3]);
	m_pit1.  setPos(shuffledRooms[4]);
	m_pit2.  setPos(shuffledRooms[5]);
}

void Game::help()
{
	char answer = '\0';
	do
	{
		std::cout << "Instructions? Y/N\n";
		std::cin >> answer;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (tolower(answer))
		{
		case 'y':
			printRules();
			break;
		case 'n':
			break;
		default:
			std::cout << "Invalid Response, try again\n";
			break;
		}
	} while (tolower(answer) != 'y' && tolower(answer) != 'n');
}

void Game::printRules()
{
	std::cout << "\nYour goal is to find and kill the Wumpus.\n";
	std::cout << "There are 3 different types of hazards :\n";
	std::cout << "Caves, which cause a draft nearby and kill you if you fall\n";
	std::cout << "Bats, which cause a flapping noise and carry you somewhere random\n";
	std::cout << "And the Wumpus. Smelly, unbathed, dirty, it will give off a terrible smell\n";
	std::cout << "The Wumpus won't fall down the bottomless pit nor will bats be able to move him\n";
	std::cout << "Also, if you try to shoot an arrow and miss, the wumpus will move to a different location\n\n";
}

void Game::run()
{
	help();

	bool isRunning = true;
	while (isRunning)
	{
		int playerPos = m_player.getPos();
		int wumpusPos = m_wumpus.getPos();
		int batPos1 = m_bat1.getPos();
		int batPos2 = m_bat2.getPos();
		int pitPos1 = m_pit1.getPos();
		int pitPos2 = m_pit2.getPos();

		std::cout << "You are in room " << playerPos << "\n";

		isRunning = false;
	}
}
