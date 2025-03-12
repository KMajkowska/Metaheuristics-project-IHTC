#pragma once

#include <string>
#include <compare>

/**
 * @brief Class for choosing the best room for given patient. Used in greedy algoritm, when we greedy choose the best rooom for out patient. The best room is this one
 * which have the smallet number for all of this criteria: similar age, the same gender and still have capacity left
*/
class RoomBrokenAgeGender
{
public:
	RoomBrokenAgeGender(int brokenAge, int brokenGender, int brokenCapacity, const std::string& id);
	std::strong_ordering operator<=>(const RoomBrokenAgeGender& other) const;

	//begin :: setters
	void incrementBrokenAge();
	void incrementBrokenGender();
	void incrementBrokenCapacity();
	void setId(const std::string& id);
	//end :: setter

	// begin :: getters
	int brokenAge() const;
	int brokenGender() const;
	int brokenCapacity() const;
	std::string id() const;
	// end :: getters
private:
	int _brokenAge { 0 };
	int _brokenGender { 0 };
	int _brokenCapacity { 0 };

	std::string _id { "" };
};