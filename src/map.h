#pragma once

#include <map>
#include <vector>

class Map
{
public:
	Map();
	const std::vector<int>& getNeighborRooms(int currentRoom) const;
	bool areConnected(int roomFirst, int roomSecond) const;

private:
	std::map<int, std::vector<int>> m_cave;
	void initializeCave();
};
