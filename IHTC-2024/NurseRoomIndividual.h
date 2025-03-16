#pragma once

#include<vector>

/*
* pielêgniarka bêdzie jako macierz timeslot/pokoj 
* pielêgniarka ma ju¿ odgórnie przypisany timeslot kiedy jest a kiedy nie
*/

/**
 * @brief Helper Individual where we store room assigned for nurse on given day and shift 
*/

class NurseRoomIndividual
{
public:
	std::vector<std::vector<int>> getNursesInRooms();
	void setRoomForNurses(std::vector<std::vector<int>> newNursesInRooms);
	void setRoomForNurse(int timeslot, int nurse, int room);

	int roomForNurse(int timeslot, int nurse);

private:
	std::vector<std::vector<int>> nurseToRoom;
};