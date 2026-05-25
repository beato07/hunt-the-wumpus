#pragma once
#include <map>
#include <vector>

class Map
{
public:
	Map();

	void initializeCave();

	const std::vector<int>& getNeighborRooms(int room);

	int getRandomRoom() const;

private:
	std::map<int, std::vector<int>> m_cave;
};
