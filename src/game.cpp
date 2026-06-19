#include "game.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

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

void Game::askForInstructions()
{
	char answer{};
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
	std::cout << "WELCOME TO 'HUNT THE WUMPUS'\n"
		<< "  THE WUMPUS LIVES IN A CAVE OF 20 ROOMS. EACH ROOM\n"
		<< "HAS 3 TUNNELS LEADING TO OTHER ROOMS. (LOOK AT A\n"
		<< "DODECAHEDRON TO SEE HOW THIS WORKS-IF YOU DON'T KNOW\n"
		<< "WHAT A DODECAHEDRON IS, ASK SOMEONE)\n";

	std::string pass;
	std::getline(std::cin, pass);

	std::cout << "\n     HAZARDS:\n"
		<< "BOTTOMLESS PITS - TWO ROOMS HAVE BOTTOMLESS PITS IN THEM\n"
		<< "    IF YOU GO THERE, YOU FALL INTO THE PIT (& LOSE!)\n"
		<< "SUPER BATS - TWO OTHER ROOMS HAVE SUPER BATS. IF YOU\n"
		<< "    GO THERE, A BAT GRABS YOU AND TAKES YOU TO SOME OTHER\n"
		<< "    ROOM AT RANDOM. (WHICH MIGHT BE TROUBLESOME)\n";

	std::getline(std::cin, pass);

	std::cout << "\n    WUMPUS:\n"
		<< "THE WUMPUS IS NOT BOTHERED BY THE HAZARDS (HE HAS SUCKER\n"
		<< "FEET AND IS TOO BIG FOR A BAT TO LIFT). USUALLY\n"
		<< "HE IS ASLEEP. TWO THINGS WAKE HIM UP: YOUR ENTERING\n"
		<< "HIS ROOM OR YOUR SHOOTING AN ARROW.\n"
		<< "    IF THE WUMPUS WAKES, HE MOVES (P=.75) ONE ROOM\n"
		<< "OR STAYS STILL (P=.25). AFTER THAT, IF HE IS WHERE YOU\n"
		<< "ARE, HE EATS YOU UP (& YOU LOSE!)\n";

	std::getline(std::cin, pass);

	std::cout << "\n    YOU:\n"
		<< "EACH TURN YOU MAY MOVE OR SHOOT AN ARROW\n"
		<< "  MOVING: YOU CAN GO ONE ROOM (THRU ONE TUNNEL)\n"
		<< "  ARROWS: YOU HAVE 5 ARROWS. YOU LOSE WHEN YOU RUN OUT.\n"
		<< "  SHOOTING: YOU CAN ONLY SHOOT INTO A NEIGHBORING ROOM.\n"
		<< "    IF THE ARROW HITS THE WUMPUS, YOU WIN.\n"
		<< "    IF YOU MISS, THE WUMPUS WAKES UP AND MIGHT MOVE\n"
		<< "    INTO YOUR ROOM (& EAT YOU!).\n";

	std::getline(std::cin, pass);

	std::cout << "\n    WARNINGS:\n"
		<< "     WHEN YOU ARE ONE ROOM AWAY FROM WUMPUS OR HAZARD,\n"
		<< "    THE COMPUTER SAYS:\n"
		<< " WUMPUS-  'I SMELL A WUMPUS'\n"
		<< " BAT   -  'BATS NEARBY'\n"
		<< " PIT   -  'I FEEL A DRAFT'\n";
}

void Game::printWarnings()
{
	int playerPos = m_player.getPos();

	if (m_gameMap.areConnected(playerPos, m_wumpus.getPos()))
		std::cout << "\nI SMELL A WUMPUS";

	if (m_gameMap.areConnected(playerPos, m_bat1.getPos()) ||
		m_gameMap.areConnected(playerPos, m_bat2.getPos()))
		std::cout << "\nBATS NEARBY";

	if (m_gameMap.areConnected(playerPos, m_pit1.getPos()) ||
		m_gameMap.areConnected(playerPos, m_pit2.getPos()))
		std::cout << "\nI FEEL A DRAFT";
}

void Game::printRoomInfo()
{
	const int currentRoom = m_player.getPos();
	const auto& tunnels = m_gameMap.getNeighborRooms(currentRoom);

	std::cout << "\nYOU ARE IN ROOM  " << m_player.getPos() << '\n'
			  << "TUNNELS LEAD TO  ";

	for (int neighbor : tunnels)
	{
		std::cout << neighbor << ' ';
	}
	std::cout << '\n';
}

bool Game::handlePlayerTurn()
{
	char playerChoice{};
	do
	{
		std::cout << "\nSHOOT OR MOVE (S-M)? ";
		std::cin >> playerChoice;
		playerChoice = std::toupper(playerChoice);
	} while (playerChoice != 'S' && playerChoice != 'M');

	if (playerChoice == 'S' || playerChoice == 's')
	{
		return m_player.tryShoot(m_gameMap, m_wumpus);
	} 
	else if (playerChoice == 'M' || playerChoice == 'm')
	{
		m_player.tryMove(m_gameMap);

		bool keepPlaying = checkHazards();
		return keepPlaying;
	}

	return false;
}

bool Game::checkHazards()
{
	bool processingHazards = true;
	while (processingHazards)
	{
		int currentRoom = m_player.getPos();

		if (currentRoom == m_wumpus.getPos())
		{
			return m_wumpus.applyEffect();
		}

		if (currentRoom == m_bat1.getPos() || currentRoom == m_bat2.getPos())
		{
			if (currentRoom == m_bat1.getPos()) m_bat1.applyEffect(m_player);
			else m_bat2.applyEffect(m_player);

			continue;
		}

		if (currentRoom == m_pit1.getPos() || currentRoom == m_pit2.getPos())
		{
			return m_pit1.applyEffect();
		}
		processingHazards = false;
	}
	return true;
}

void Game::run()
{
	askForInstructions();

	std::cout << "\nHUNT THE WUMPUS\n";

	bool isRunning = true;
	while (isRunning)
	{
		printWarnings();
		printRoomInfo();
		if (!handlePlayerTurn())
		{
			isRunning = false;
		}
	}
}
