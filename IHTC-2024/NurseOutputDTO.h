#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "Assignment.h"

class NurseOutputDTO
{
public:
	NurseOutputDTO() = default;
	NurseOutputDTO(std::string newId, std::vector<Assignment> newAssignments);

	std::string getId() const;
	std::vector<Assignment> getAssignments() const;

	void setId(const std::string& newId);
	void setAssignments(std::vector<Assignment> newAssignments);

private:
	std::string id;
	std::vector<Assignment> assignments;
};

void to_json(nlohmann::json& j, const NurseOutputDTO& data);
void from_json(const nlohmann::json& j, NurseOutputDTO& data);
