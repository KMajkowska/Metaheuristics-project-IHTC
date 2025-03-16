#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>

#include "ICIndividualConsumer.h"

class Logger : public ICIndividualConsumer
{
public:
	Logger(const std::string& filename);
	Logger(const Logger& other) = default;
	~Logger();

	void consume(const CIndividual& current, const CIndividual& best, double temperature) override;

	void flushToFile();

private:
	std::ofstream logFile;
	std::vector<std::string> buffer;
	std::mutex mutex;

	static constexpr size_t MAX_BUFFER_SIZE = 16384;

	std::string createLog(const CIndividual& current, const CIndividual& best, double temperature);

};