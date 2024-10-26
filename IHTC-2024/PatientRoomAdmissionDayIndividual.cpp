#include "PatientRoomAdmissionDayIndividual.h"

std::vector<std::vector<int>> PatientRoomAdmissionDayIndividual::getPatientsInRoom()
{
    return patientsInRoom;
}

void PatientRoomAdmissionDayIndividual::setPatientsInRoom(std::vector<std::vector<int>> newPatientsInRoom)
{
    patientsInRoom = newPatientsInRoom;
}

int PatientRoomAdmissionDayIndividual::getRoomForPatient(int timeslot, int patient)
{
    return patientsInRoom[timeslot][patient];
}

void PatientRoomAdmissionDayIndividual::setRoomForPatient(int timeslot, int patient, int room)
{
    patientsInRoom[timeslot][patient] = room;
}
