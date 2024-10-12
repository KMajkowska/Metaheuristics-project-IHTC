#pragma once
#include "Patient.h"
#include<string>

class Occupant : public Patient
{

public:
	std::string getRoomId() const;

private:
	std::string room_id;
};