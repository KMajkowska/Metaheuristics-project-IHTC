#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "AllGameParameters.h"
#include "enumOperations.h"
#include "solverBuilderUtils.h"

/**
 * @brief This class is used as a DTO to pass and receive information about a game through network.
 */
class CGameInfo : public AllGameParameters
{
public:
	CGameInfo() = default;
	CGameInfo(const AllGameParameters& other);
	CGameInfo(const CGameInfo& other) = default;
	
	void setUUID(const std::string uuid);
	void setPost(int port);
	void setLastUpdated(std::chrono::steady_clock::time_point lastUpdated);

	std::string uuid() const;
	int port() const;
	std::chrono::steady_clock::time_point lastUpdated() const;

private:
	std::string _uuid { boost::uuids::to_string(boost::uuids::random_generator()()) };

	int _port{ 0 };

	std::chrono::steady_clock::time_point _lastUpdated{ std::chrono::steady_clock::now() };
};


void to_json(nlohmann::json& j, const CGameInfo& obj);
void from_json(const nlohmann::json& j, CGameInfo& obj);