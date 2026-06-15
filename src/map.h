#pragma once
#include <map>
#include <set>

class Map
{
public:
	Map();
	const std::set<int>& getNeighborRooms(int currentRoom);
	bool areConnected(int roomFirst, int roomSecond);

private:
	std::map<int, std::set<int>> m_cave;
	void initializeCave();
};
