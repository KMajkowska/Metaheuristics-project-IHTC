#pragma once
#include<vector>
 /*
	macierz timeslot/pacjent
	poczatkowo bedzie jakas lista kiedy jaki pacjent przyjety (miedzy release day i opcjonalnym due date)
	potem bedzie heurystycznie sprawdzane, czy da si� go w ten dany dzien przypisac w odpowiedni dzien
 */

class PatientRoomAdmissionDayIndividual
{
public:
	std::vector<std::vector<int>> getPatientsInRoom();
	void setPatientsInRoom(std::vector<std::vector<int>> newPatientsInRoom);
	int getRoomForPatient(int timeslot, int patient);
	void setRoomForPatient(int timeslot, int patient, int room);
private:
	std::vector<std::vector<int>> patientsInRoom;
};