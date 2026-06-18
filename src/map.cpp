#include "map.h"

Map::Map()
{
	initializeCave();
}

void Map::initializeCave()
{
	m_cave[1]  = {  2,  5,  8 };
	m_cave[2]  = {  1,  3, 10 };
	m_cave[3]  = {  2,  4, 12 };
	m_cave[4]  = {  3,  5, 14 };
	m_cave[5]  = {  1,  4,  6 };
	m_cave[6]  = {  5,  7, 15 };
	m_cave[7]  = {  6,  8, 17 };
	m_cave[8]  = {  1,  7, 11 };
	m_cave[9]  = { 10, 12, 19 };
	m_cave[10] = {  2,  9, 11 };
	m_cave[11] = {  8, 10, 20 };
	m_cave[12] = {  3,  9, 13 };
	m_cave[13] = { 12, 14, 18 };
	m_cave[14] = {  4, 13, 15 };
	m_cave[15] = {  6, 14, 16 };
	m_cave[16] = { 15, 17, 18 };
	m_cave[17] = {  7, 16, 20 };
	m_cave[18] = { 13, 16, 19 };
	m_cave[19] = {  9, 18, 20 };
	m_cave[20] = { 11, 17, 19 };
}

const std::set<int>& Map::getNeighborRooms(int currentRoom)
{
	return m_cave[currentRoom];
}

bool Map::areConnected(int roomFirst, int roomSecond) const
{
	return m_cave.at(roomFirst).contains(roomSecond);
}
