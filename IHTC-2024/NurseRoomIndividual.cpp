#include "NurseRoomIndividual.h"

std::vector<std::vector<int>> NurseRoomIndividual::getNursesInRooms()
{
    return _nurseToRoom;
}

void NurseRoomIndividual::setRoomForNurses(std::vector<std::vector<int>> newNursesInRooms)
{
    _nurseToRoom = newNursesInRooms;
}

int NurseRoomIndividual::roomForNurse(int timeslot, int nurse)
{
    return _nurseToRoom[timeslot][nurse];
}

void NurseRoomIndividual::setRoomForNurse(int timeslot, int nurse, int room)
{
    _nurseToRoom[timeslot][nurse] = room;
}
