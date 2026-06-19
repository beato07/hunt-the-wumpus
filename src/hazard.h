#pragma once

class Map;
class Player;

class Hazard
{
public:
	Hazard() : m_hazardPos(0) {}

	int getPos() const { return m_hazardPos; }
	void setPos(int newHazardPos) { m_hazardPos = newHazardPos; }

protected:
	int m_hazardPos;
};

class Wumpus : public Hazard
{
public:
	Wumpus() : Hazard() {}

	void scare(const Map& gameMap);
	bool applyEffect();
};

class Bat : public Hazard
{
public:
	Bat() : Hazard() {}
	bool applyEffect(Player& player);
};

class Pit : public Hazard
{
public:
	Pit() : Hazard() {}
	bool applyEffect();
};
