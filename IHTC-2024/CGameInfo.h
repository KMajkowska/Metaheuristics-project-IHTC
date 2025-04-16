#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "AllGameParameters.h"
#include "enumOperations.h"

/**
 * @brief This class is used as a DTO to pass and receive information about a game through network.
 */
class CGameInfo : public AllGameParameters
{
public:
	CGameInfo() = default;
	
	void setUUID(const std::string uuid);
	void setPostPort(short postPort);
	void setReceivePort(short receivePort);
	void setLastUpdated(std::chrono::steady_clock::time_point lastUpdated);

	std::string uuid() const;
	short postPort() const;
	short receivePort() const;
	std::chrono::steady_clock::time_point lastUpdated() const;

private:
	std::string _uuid { boost::uuids::to_string(boost::uuids::random_generator()()) };

	short _postPort{ 0 };
	short _receivePort{ 0 };

	std::chrono::steady_clock::time_point _lastUpdated;
};


void to_json(nlohmann::json& j, const CGameInfo& obj);
void from_json(const nlohmann::json& j, CGameInfo& obj);