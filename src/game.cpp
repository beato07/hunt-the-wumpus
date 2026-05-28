#include "game.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iostream>

#include <string>


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
		std::cout << "Instructions (Y-N)? ";
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
	std::cout << "WELCOME TO 'HUNT THE WUMPUS'\n";
	std::cout << "  THE WUMPUS LIVES IN A CAVE OF 20 ROOMS. EACH ROOM\n";
	std::cout << "HAS 3 TUNNELS LEADING TO OTHER ROOMS. (LOOK AT A\n";
	std::cout << "DODECAHEDRON TO SEE HOW THIS WORKS-IF YOU DON'T KNOW\n";
	std::cout << "WHAT A DODECAHEDRON IS, ASK SOMEONE)\n";

	std::string pass;
	std::getline(std::cin, pass);

	std::cout << '\n';
	std::cout << "     HAZARDS:\n";
	std::cout << "BOTTOMLESS PITS - TWO ROOMS HAVE BOTTOMLESS PITS IN THEM\n";
	std::cout << "    IF YOU GO THERE, YOU FALL INTO THE PIT (& LOSE!)\n";
	std::cout << "SUPER BATS - TWO OTHER ROOMS HAVE SUPER BATS. IF YOU\n";
	std::cout << "    GO THERE, A BAT GRABS YOU AND TAKES YOU TO SOME OTHER\n";
	std::cout << "    ROOM AT RANDOM. (WHICH MIGHT BE TROUBLESOME)\n";

	std::getline(std::cin, pass);

	std::cout << '\n';
	std::cout << "    WUMPUS:\n";
	std::cout << "THE WUMPUS IS NOT BOTHERED BY THE HAZARDS (HE HAS SUCKER\n";
	std::cout << "FEET AND IS TOO BIG FOR A BAT TO LIFT). USUALLY\n";
	std::cout << "HE IS ASLEEP. TWO THINGS WAKE HIM UP: YOUR ENTERING\n";
	std::cout << "HIS ROOM OR YOUR SHOOTING AN ARROW.\n";
	std::cout << "    IF THE WUMPUS WAKES, HE MOVES (P=.75) ONE ROOM\n";
	std::cout << "OR STAYS STILL (P=.25). AFTER THAT, IF HE IS WHERE YOU\n";
	std::cout << "ARE, HE EATS YOU UP (& YOU LOSE!)\n";

	std::getline(std::cin, pass);

	std::cout << '\n';
	std::cout << "    YOU:\n";
	std::cout << "EACH TURN YOU MAY MOVE OR SHOOT A CROOKED ARROW\n";
	std::cout << "  MOVING: YOU CAN GO ONE ROOM (THRU ONE TUNNEL)\n";
	std::cout << "  ARROWS: YOU HAVE 5 ARROWS. YOU LOSE WHEN YOU RUN OUT.\n";
	std::cout << "  EACH ARROW CAN GO FROM 1 TO 5 ROOMS. YOU AIM BY TELLING\n";
	std::cout << "  THE COMPUTER THE ROOM#S YOU WANT THE ARROW TO GO TO.\n";
	std::cout << "  IF THE ARROW CAN'T GO THAT WAY(IE NO TUNNEL) IT MOVES\n";
	std::cout << "  AT RANDOM TO THE NEXT ROOM.\n";
	std::cout << "    IF THE ARROW HITS THE WUMPUS, YOU WIN.\n";
	std::cout << "    IF THE ARROW HITS YOU, YOU LOSE.\n";

	std::getline(std::cin, pass);

	std::cout << '\n';
	std::cout << "    WARNINGS:\n";
	std::cout << "     WHEN YOU ARE ONE ROOM AWAY FROM WUMPUS OR HAZARD,\n";
	std::cout << "    THE COMPUTER SAYS:\n";
	std::cout << " WUMPUS-  'I SMELL A WUMPUS'\n";
	std::cout << " BAT   -  'BATS NEARBY'\n";
	std::cout << " PIT   -  'I FEEL A DRAFT'\n\n";
}

void Game::printRoomInfo(int playerPos, Map& gameMap)
{
	const auto& neighbors = gameMap.getNeighborRooms(playerPos);

	std::cout << "\nYOU ARE IN ROOM  " << playerPos << '\n';
	std::cout << "TUNNELS LEAD TO  ";

	for (int neighbor : neighbors)
	{
		std::cout << neighbor << ' ';
	}
	std::cout << std::endl;
}

void Game::run()
{
	help();

	std::cout << "\nHUNT THE WUMPUS\n";

	bool isRunning = true;
	while (isRunning)
	{
		int playerPos = m_player.getPos();
		int wumpusPos = m_wumpus.getPos();
		int batPos1   = m_bat1.  getPos();
		int batPos2   = m_bat2.  getPos();
		int pitPos1   = m_pit1.  getPos();
		int pitPos2   = m_pit2.  getPos();

		printRoomInfo(playerPos, m_gameMap);

		isRunning = false;
	}
}
