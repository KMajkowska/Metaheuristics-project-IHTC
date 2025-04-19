#include "CGameInfo.h"

CGameInfo::CGameInfo(const AllGameParameters& other) : AllGameParameters(other)
{
	auto ports{ getRandomPorts(2) };

	if (ports.size() != 2)
	{
		throw std::invalid_argument("GameInfo ports weren't generated properly");
	}

	setPostPort(*(ports.begin()));
	ports.erase(ports.begin());
	setReceivePort(*(ports.begin()));
}

void CGameInfo::setUUID(const std::string uuid)
{
	_uuid = uuid;
}

void CGameInfo::setPostPort(int postPort)
{
	_postPort = postPort;
}

void CGameInfo::setReceivePort(int receivePort)
{
	_receivePort = receivePort;
}

void CGameInfo::setLastUpdated(std::chrono::steady_clock::time_point lastUpdated)
{
	_lastUpdated = lastUpdated;
}

std::string CGameInfo::uuid() const
{
	return _uuid;
}

int CGameInfo::postPort() const
{
	return _postPort;
}

int CGameInfo::receivePort() const
{
	return _receivePort;
}

std::chrono::steady_clock::time_point CGameInfo::lastUpdated() const
{
	return _lastUpdated;
}

void to_json(nlohmann::json& j, const CGameInfo& obj)
{
	j = nlohmann::json
	{
		{"uuid", obj.uuid()},
		{"postPort", obj.postPort()},
		{"receivePort", obj.receivePort()},
		{"name", obj.name()},
		{"gameTime", obj.gameTime()},
		{"gameLevel", enumToString<GameLevel>(obj.gameLevel())},
		{"winningMode", enumToString<WinnerJudgeType>(obj.judgeType())},
		{"maxIteration", obj.maxIteration()},
		{"genderGroupIter", obj.genderGroupIter()},
		{"neighbourSize", obj.neighbourSize()},
		{"neighbourGenerator", enumToString<NeighbourGeneratorType>(obj.neighbourGenerator())},
		{"increaseTempIters", obj.increaseTempIters()},
		{"initSolver", enumToString<SolverType>(obj.initSolver())},
		{"startingTemperature", obj.startingTemperature()},
		{"stopTemperature", obj.stopTemperature()},
		{"prizeSize", obj.prizeSize()},
		{"coolingMultiplier", obj.coolingMultiplier()},
		{"roundNumber", obj.roundNumber()}
	};
}

void from_json(const nlohmann::json& j, CGameInfo& obj)
{
	obj.setUUID(j.at("uuid").get<std::string>());
	obj.setPostPort(j.at("postPort").get<int>());
	obj.setReceivePort(j.at("receivePort").get<int>());
	obj.setJudgeType(stringToEnum<WinnerJudgeType>(j.at("winningMode").get<std::string>()));
	obj.setRoundNumber(j.at("roundNumber").get<int>());
	obj.setName(j.at("name").get<std::string>());
	obj.setGameTime(j.at("gameTime").get<int>());
	obj.setGameLevel(stringToEnum<GameLevel>(j.at("gameLevel").get<std::string>()));
	obj.setMaxIteration(j.at("maxIteration").get<int>());
	obj.setGenderGroupIter(j.at("genderGroupIter").get<int>());
	obj.setNeighbourSize(j.at("neighbourSize").get<int>());
	obj.setNeighbourGenerator(stringToEnum<NeighbourGeneratorType>(j.at("neighbourGenerator").get<std::string>()));
	obj.setIncreaseTempIters(j.at("increaseTempIters").get<int>());
	obj.setInitSolver(stringToEnum<SolverType>(j.at("initSolver").get<std::string>()));
	obj.setStartingTemperature(j.at("startingTemperature").get<int>());
	obj.setStopTemperature(j.at("stopTemperature").get<int>());
	obj.setPrizeSize(j.at("prizeSize").get<int>());
	obj.setCoolingMultiplier(j.at("coolingMultiplier").get<int>());
	obj.setRoundNumber(j.at("roundNumber").get<int>());
}
