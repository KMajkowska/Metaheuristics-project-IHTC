#include "Logger.h"


Logger::Logger(const std::string& filename) :
	logFile(filename, std::ios::app) 
{
	buffer.reserve(MAX_BUFFER_SIZE);
	
	if (!logFile.is_open()) 
	{
		throw std::runtime_error("Failed to open log file: " + filename);
	}
	else
	{
		std::cout << "Opened log file: " << filename << std::endl;
	}
}

Logger::~Logger()
{
	flushToFile();

	logFile.close();
}

void Logger::consume(const CIndividual& current, const CIndividual& best, double temperature)
{
	buffer.push_back(createLog(current, best, temperature));

	if (buffer.size() >= MAX_BUFFER_SIZE)
	{
		flushToFile();
	}
}

void Logger::flushToFile()
{
	std::lock_guard<std::mutex> lock(mutex);

	for (const auto& msg : buffer) 
	{
		logFile << msg << std::endl;
	}

	buffer.clear();
	logFile.flush();
}

std::string Logger::createLog(const CIndividual& current, const CIndividual& best, double temperature)
{
	return current.fitness().second.getCSVData() + "," + std::to_string(current.fitness().first) + "," +
		best.fitness().second.getCSVData() + "," + std::to_string(best.fitness().first) + "," +
		std::to_string(temperature);
}
