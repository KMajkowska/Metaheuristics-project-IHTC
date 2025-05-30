#include "ICIndividualCSVLogger.h"

ICIndividualCSVLogger::ICIndividualCSVLogger(const std::string& filename) :
	_logFile(filename, std::ios::app) 
{
	_buffer.reserve(MAX_BUFFER_SIZE);
	
	if (!_logFile.is_open()) 
	{
		throw std::runtime_error("Failed to open log file: " + filename);
	}
}

ICIndividualCSVLogger::~ICIndividualCSVLogger()
{
	flushToFile();

	_logFile.close();
}

void ICIndividualCSVLogger::consume(const CIndividual& current, const CIndividual& best, double temperature)
{
	_buffer.push_back(createLog(current, best, temperature));

	if (_buffer.size() >= MAX_BUFFER_SIZE)
	{
		flushToFile();
	}
}

void ICIndividualCSVLogger::flushToFile()
{
	std::lock_guard<std::mutex> lock(_mutex);

	for (const auto& msg : _buffer) 
	{
		_logFile << msg << std::endl;
	}

	_buffer.clear();
	_logFile.flush();
}

std::string ICIndividualCSVLogger::createLog(const CIndividual& current, const CIndividual& best, double temperature)
{
	return current.fitness().second.getCSVData() + "," + std::to_string(current.fitness().first) + "," +
		best.fitness().second.getCSVData() + "," + std::to_string(best.fitness().first) + "," +
		std::to_string(temperature);
}
