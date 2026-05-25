#pragma once

// Опережающее объявление
class Map;

class Hazard
{
public:
	Hazard() : m_hazardPos(0) {}

	int getPos() const { return m_hazardPos; }
	void setPos(int newPos) { m_hazardPos = newPos; }

protected:
	int m_hazardPos;
};

class Wumpus : public Hazard
{
public:
	Wumpus() : Hazard() {}
};

class Bat : public Hazard
{
public:
	Bat() : Hazard() {}

	void carryPlayer(Map& gameMap, int& playerPos);
};

class Pit : public Hazard
{
public:
	Pit() : Hazard() {}

	bool isFallen();
};
