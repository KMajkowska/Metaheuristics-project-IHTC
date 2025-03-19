#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>

#include "ICIndividualConsumer.h"

/**
 * @brief Logging individual and their values on the console and write to file.
*/
class ICIndividualCSVLogger : public ICIndividualConsumer
{
public:
	ICIndividualCSVLogger(const std::string& filename);
	ICIndividualCSVLogger(const ICIndividualCSVLogger& other) = default;
	~ICIndividualCSVLogger();

	void consume(const CIndividual& current, const CIndividual& best, double temperature) override;

	void flushToFile();

private:
	std::ofstream _logFile;
	std::vector<std::string> _buffer;
	std::mutex _mutex;

	static constexpr size_t MAX_BUFFER_SIZE = 16384;

	std::string createLog(const CIndividual& current, const CIndividual& best, double temperature);

};