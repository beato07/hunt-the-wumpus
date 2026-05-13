#pragma once

class Player
{
public:
	Player() : m_playerPos(0), m_arrows(5) {}

	int getPos() const { return m_playerPos; }
	int getArrows() const { return m_arrows; }

	void setPos(int newPos) { m_playerPos = newPos; }
	void useArrow();

private:
	int m_playerPos;
	int m_arrows;
};
