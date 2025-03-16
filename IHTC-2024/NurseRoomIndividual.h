#pragma once

#include<vector>

/*
* piel�gniarka b�dzie jako macierz timeslot/pokoj 
* piel�gniarka ma ju� odg�rnie przypisany timeslot kiedy jest a kiedy nie
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