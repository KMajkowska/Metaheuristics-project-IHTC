#pragma once
#include<vector>

/*
* pielêgniarka bêdzie jako macierz timeslot/pokoj 
* pielêgniarka ma ju¿ odgórnie przypisany timeslot kiedy jest a kiedy nie
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