#include "Logger.h"


Logger::Logger(const std::string& filename) :
	filename(filename)
{
}

Logger::~Logger()
{
	flushToFile();
}

void Logger::log(const std::string& logStr)
{
	std::cout << logStr << std::endl;

	std::lock_guard<std::mutex> lock(mutex);
	buffer.push_back(logStr);
}

std::vector<std::string> Logger::getLogs() const
{
	return buffer;
}

void Logger::flushToFile()
{
	std::lock_guard<std::mutex> lock(mutex);
	std::ofstream file(filename, std::ios::trunc);

	if (!file.is_open())
	{
		file.close();

		std::cerr << "Failed to open log file: " << filename << std::endl;

		return;
	}


	for (const auto& message : buffer)
	{
		file << message << std::endl;
	}

	buffer.clear();

	file.close();
}
