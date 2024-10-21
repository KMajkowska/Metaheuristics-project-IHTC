#pragma once
#include<vector>

/*
* piel�gniarka b�dzie jako macierz timeslot/pokoj 
* piel�gniarka ma ju� odg�rnie przypisany timeslot kiedy jest a kiedy nie
*/

class NurseRoomIndividual
{
public:
	std::vector<std::vector<int>> getNursesInRooms();
	void setRoomForNurses(std::vector<std::vector<int>> newNursesInRooms);
	int getRoomForNurse(int timeslot, int nurse);
	void setRoomForNurse(int timeslot, int nurse, int room);
private:
	std::vector<std::vector<int>> nurseToRoom;
};