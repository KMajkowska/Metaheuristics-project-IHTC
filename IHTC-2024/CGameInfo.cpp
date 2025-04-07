#include "CGameInfo.h"

void CGameInfo::setUUID(const std::string uuid)
{
	_uuid = uuid;
}

void CGameInfo::setPostPort(short postPort)
{
	_postPort = postPort;
}

void CGameInfo::setReceivePort(short receivePort)
{
	_receivePort = receivePort;
}

void CGameInfo::setPlayerName(const std::string& playerName)
{
	_playerName = playerName;
}

void CGameInfo::setJudgeType(WinnerJudgeType judgeType)
{
	_judgeType = judgeType;
}

void CGameInfo::setRounds(int rounds)
{
	_rounds = rounds;
}

std::string CGameInfo::uuid() const
{
	return _uuid;
}

short CGameInfo::postPort() const
{
	return _postPort;
}

short CGameInfo::receivePort() const
{
	return _receivePort;
}

std::string CGameInfo::playerName() const
{
	return _playerName;
}

WinnerJudgeType CGameInfo::judgeType() const
{
	return _judgeType;
}

int CGameInfo::rounds() const
{
	return _rounds;
}

void to_json(nlohmann::json& j, const CGameInfo& obj)
{
	j = nlohmann::json
	{
		{"uuid", obj.uuid()},
		{"postPort", obj.postPort()},
		{"receivePort", obj.receivePort()},
		{"playerName", obj.playerName()},
		{"judgeType", enumToString<WinnerJudgeType>(obj.judgeType())},
		{"rounds", obj.rounds()}
	};
}

void from_json(const nlohmann::json& j, CGameInfo& obj)
{
	obj.setUUID(j.at("uuid").get<std::string>());
	obj.setPostPort(j.at("postPort").get<short>());
	obj.setReceivePort(j.at("receivePort").get<short>());
	obj.setPlayerName(j.at("playerName").get<std::string>());
	obj.setJudgeType(stringToEnum<WinnerJudgeType>(j.at("judgeType").get<std::string>()));
	obj.setRounds(j.at("rounds").get<int>());
}
