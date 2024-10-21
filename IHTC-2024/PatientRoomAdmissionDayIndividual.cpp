#include "PatientRoomAdmissionDayIndividual.h"

PatientRoomAdmissionDayIndividual::PatientRoomAdmissionDayIndividual(int schedulingPeriod, int numberOfPatients)
{
    for (int i = 0; i < schedulingPeriod; i++)
    {
        patientsInRoom.push_back(std::vector<int>(numberOfPatients));
    }
}

void PatientRoomAdmissionDayIndividual::setOccupantsInRooms(int schedulingPeriod, int numberOfOccupants, std::vector<int> lengthOfStay, std::vector<int> rooms)
{
    /*for (int i = 0; i < schedulingPeriod; i++)
    {
        patientsInRoom.push_back(std::vector<int>(numberOfOccupants));
    }

    for (int i = numberOfOccupants - 1; i >= 0; i--)
    {
        for (int j = 0;  j < lengthOfStay[numberOfOccupants - 1]; j++)
        {
            patientsInRoom[j][patientsInRoom.size() - 1 - numberOfOccupants] = rooms[numberOfOccupants - 1];
        }
    }*/
}

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
