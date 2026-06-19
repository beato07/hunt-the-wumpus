#pragma once

class Map;
class Wumpus;

class Player
{
public:
	int getPos() { return m_playerPos; }
	void setPos(int newPlayerPos) { m_playerPos = newPlayerPos; }

	bool tryShoot(const Map& gameMap, Wumpus& wumpus);
	bool tryMove(const Map& gameMap);

private:
	int m_playerPos{ 0 };
	int m_arrowsCount{ 5 };
};
