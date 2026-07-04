#include "game.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

Game::Game()
{
	setupEntities();
}

void Game::resetToInitialSetup()
{
	m_player.resetArrows();

	m_player.setPos(m_initialPlayerPos);
	m_wumpus.setPos(m_initialWumpusPos);
	m_bat1.  setPos(m_initialBat1Pos);
	m_bat2.  setPos(m_initialBat2Pos);
	m_pit1.  setPos(m_initialPit1Pos);
	m_pit2.  setPos(m_initialPit2Pos);
}

void Game::setupEntities()
{
	std::vector<int> shuffledRooms(20);
	std::iota(shuffledRooms.begin(), shuffledRooms.end(), 1);

	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::shuffle(shuffledRooms.begin(), shuffledRooms.end(), gen);

	m_initialPlayerPos = shuffledRooms[0];
	m_initialWumpusPos = shuffledRooms[1];
	m_initialBat1Pos   = shuffledRooms[2];
	m_initialBat2Pos   = shuffledRooms[3];
	m_initialPit1Pos   = shuffledRooms[4];
	m_initialPit2Pos   = shuffledRooms[5];

	m_player.setPos(m_initialPlayerPos);
	m_wumpus.setPos(m_initialWumpusPos);
	m_bat1.  setPos(m_initialBat1Pos);
	m_bat2.  setPos(m_initialBat2Pos);
	m_pit1.  setPos(m_initialPit1Pos);
	m_pit2.  setPos(m_initialPit2Pos);
}

void Game::askForInstructions()
{
	std::string playerInput;
	while (true)
	{
		std::cout << "Instructions (Y-N)? ";
		std::getline(std::cin, playerInput);

		if (playerInput.length() != 1)
		{
			continue;
		}

		if (tolower(playerInput[0]) == 'y')
		{
			printRules();
			return;
		}

		if (tolower(playerInput[0]) == 'n')
		{
			return;
		}
	}
}

void Game::printRules()
{
	std::cout << "WELCOME TO 'HUNT THE WUMPUS'\n"
		<< "  THE WUMPUS LIVES IN A CAVE OF 20 ROOMS. EACH ROOM\n"
		<< "HAS 3 TUNNELS LEADING TO OTHER ROOMS. (LOOK AT A\n"
		<< "DODECAHEDRON TO SEE HOW THIS WORKS-IF YOU DON'T KNOW\n"
		<< "WHAT A DODECAHEDRON IS, ASK SOMEONE)\n";

	std::cin.ignore();

	std::cout << "\n     HAZARDS:\n"
		<< "BOTTOMLESS PITS - TWO ROOMS HAVE BOTTOMLESS PITS IN THEM\n"
		<< "    IF YOU GO THERE, YOU FALL INTO THE PIT (& LOSE!)\n"
		<< "SUPER BATS - TWO OTHER ROOMS HAVE SUPER BATS. IF YOU\n"
		<< "    GO THERE, A BAT GRABS YOU AND TAKES YOU TO SOME OTHER\n"
		<< "    ROOM AT RANDOM. (WHICH MIGHT BE TROUBLESOME)\n";

	std::cin.ignore();

	std::cout << "\n    WUMPUS:\n"
		<< "THE WUMPUS IS NOT BOTHERED BY THE HAZARDS (HE HAS SUCKER\n"
		<< "FEET AND IS TOO BIG FOR A BAT TO LIFT). USUALLY\n"
		<< "HE IS ASLEEP. TWO THINGS WAKE HIM UP: YOUR ENTERING\n"
		<< "HIS ROOM OR YOUR SHOOTING AN ARROW.\n"
		<< "    IF THE WUMPUS WAKES, HE MOVES (P=.75) ONE ROOM\n"
		<< "OR STAYS STILL (P=.25). AFTER THAT, IF HE IS WHERE YOU\n"
		<< "ARE, HE EATS YOU UP (& YOU LOSE!)\n";

	std::cin.ignore();

	std::cout << "\n    YOU:\n"
		<< "EACH TURN YOU MAY MOVE OR SHOOT AN ARROW\n"
		<< "  MOVING: YOU CAN GO ONE ROOM (THRU ONE TUNNEL)\n"
		<< "  ARROWS: YOU HAVE 5 ARROWS. YOU LOSE WHEN YOU RUN OUT.\n"
		<< "  SHOOTING: YOU CAN ONLY SHOOT INTO A NEIGHBORING ROOM.\n"
		<< "    IF THE ARROW HITS THE WUMPUS, YOU WIN.\n"
		<< "    IF YOU MISS, THE WUMPUS WAKES UP AND MIGHT MOVE\n"
		<< "    INTO YOUR ROOM (& EAT YOU!).\n";

	std::cin.ignore();

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

	for (const int& neighbor : tunnels)
	{
		std::cout << neighbor << ' ';
	}
	std::cout << "\n\n";
}

bool Game::handlePlayerTurn()
{
	std::string playerChoice;
	while (true)
	{
		std::cout << "SHOOT OR MOVE (S-M)? ";
		std::getline(std::cin, playerChoice);

		if (playerChoice.length() != 1)
		{
			continue;
		}

		if (tolower(playerChoice[0]) == 's')
		{
			return m_player.tryShoot(m_gameMap, m_wumpus);
		}

		if (tolower(playerChoice[0]) == 'm')
		{
			m_player.tryMove(m_gameMap);

			return checkHazards();
		}
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

	char playerChoice{};
	do
	{
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

		std::cout << "SAME SET-UP (Y-N)? ";
		std::cin >> playerChoice;
		playerChoice = std::toupper(playerChoice);

		if (playerChoice == 'Y')
		{
			resetToInitialSetup();
		}
		else if (playerChoice == 'N')
		{
			setupEntities();
		}

	} while (playerChoice == 'Y' || playerChoice == 'N');
}
