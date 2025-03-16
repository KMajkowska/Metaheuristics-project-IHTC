#include "NurseRoomIndividual.h"

std::vector<std::vector<int>> NurseRoomIndividual::getNursesInRooms()
{
    return nurseToRoom;
}

void NurseRoomIndividual::setRoomForNurses(std::vector<std::vector<int>> newNursesInRooms)
{
    nurseToRoom = newNursesInRooms;
}

int NurseRoomIndividual::roomForNurse(int timeslot, int nurse)
{
    return nurseToRoom[timeslot][nurse];
}

void NurseRoomIndividual::setRoomForNurse(int timeslot, int nurse, int room)
{
    nurseToRoom[timeslot][nurse] = room;
}
