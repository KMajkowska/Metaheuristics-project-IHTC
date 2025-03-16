#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "Assignment.h"

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" nurse is pretty similar, but we are separating json logic from algorithm logic
 * This class is used to save nurses in json file, after solving the problem
*/
class NurseOutputDTO
{
public:
	NurseOutputDTO() = default;
	NurseOutputDTO(std::string newId, std::vector<Assignment> newAssignments);

	std::string id() const;
	std::vector<Assignment> assignments() const;

	void setId(const std::string& newId);
	void setAssignments(std::vector<Assignment> newAssignments);

private:
	std::string _id;
	std::vector<Assignment> _assignments;
};

void to_json(nlohmann::json& j, const NurseOutputDTO& data);
void from_json(const nlohmann::json& j, NurseOutputDTO& data);
