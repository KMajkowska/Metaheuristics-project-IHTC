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

void Logger::log(const std::string& logStr)
{
	buffer.push_back(logStr);

	if (buffer.size() >= MAX_BUFFER_SIZE) 
	{
		std::cout << logStr << std::endl;

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
