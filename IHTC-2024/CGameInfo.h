#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "WinnerJudgeType.h"
#include "enumOperations.h"

/**
 * @brief This class is used as a DTO to pass and receive information about a game through network.
 */
class CGameInfo
{
public:
	CGameInfo() = default;
	
	void setUUID(const std::string uuid);
	void setPostPort(short postPort);
	void setReceivePort(short receivePort);
	void setPlayerName(const std::string& playerName);
	void setJudgeType(WinnerJudgeType judgeType);
	void setRounds(int rounds);

	std::string uuid() const;
	short postPort() const;
	short receivePort() const;
	std::string playerName() const;
	WinnerJudgeType judgeType() const;
	int rounds() const;

private:
	std::string _uuid { boost::uuids::to_string(boost::uuids::random_generator()()) };

	short _postPort{ 0 };
	short _receivePort{ 0 };

	std::string _playerName { "" };
	WinnerJudgeType _judgeType { WinnerJudgeType::BEST_OF_N };
	int _rounds { 1 };
};


void to_json(nlohmann::json& j, const CGameInfo& obj);
void from_json(const nlohmann::json& j, CGameInfo& obj);