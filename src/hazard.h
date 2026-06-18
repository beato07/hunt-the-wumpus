#pragma once

class Hazard
{
public:
	Hazard() : m_hazardPos(0) {}

	int getPos() const { return m_hazardPos; }
	void setPos(int newHazardPos) { m_hazardPos = newHazardPos; }
	void setupWumpusBehavior();

private:
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
};

class Pit : public Hazard
{
public:
	Pit() : Hazard() {}
};
